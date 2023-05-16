#include "managedatabysql.h"
#include "qmessagebox.h"
#include "tablemanager.h"
#include "privilegemanager.h"
#include "dataoperation.h"
#include "QFileDialog"
#include "qdebug.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTimer"
#include "QDateTime"
using namespace std;

ManageDataBySql::ManageDataBySql()
{
    initDir();
}

/*
 * @Brief:  初始化文件路径
 * @Return: NULL
 */
void ManageDataBySql::initDir()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "initDir文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    qDebug() << "用户信息" + str;

    list = str.split(",");

    userName = list[0];
    dbName = list[1];
    dirPath = dir->path() + "/data/" + list[1];
    file.close();
}

int ManageDataBySql::countfield(QString tablename){
    //字段数
    QString tableP = dirPath + "/table/" + tablename + "/" + tablename + ".tdf";
    qDebug() << tableP;
    QFile tablef(tableP);
    if (!tablef.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readt(&tablef);
    QString     readi;
    int n=0;
    while (!readt.atEnd()) {
        readi = readt.readLine();
        n++;
    }
    tablef.close();
    return n;
}

void ManageDataBySql::insertData(QStringList keywordList) {
    Privilegemanager ifmdt;

    if (ifmdt.adt(keywordList[2], userName)) {
        if ((keywordList[1] == "") ||
            (keywordList[2] == "") ||
            (keywordList[3] == "")) {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }

        tablePath = dirPath + "/table/" + keywordList[2] + "/" +
                    keywordList[2] + ".trd";
        qDebug() << "当前表的路径为：" + tablePath;
        QFile file(tablePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text |
                       QIODevice::Append)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&file);
        QString     insertInfo = "";

        QString data;
        QStringList datalist;
        data=keywordList[3];
        datalist=data.split(",");
        data="";
        for(int i=0;i<datalist.size();i++){
            if(datalist[i]=="null"){
                datalist[i]="";
            }
            if(i<datalist.size()-1){
                data=data+datalist[i]+",";
            }
            else if(i==datalist.size()-1){
                data=data+datalist[i];
            }
        }
        qDebug()<<"data="<<data;
        if(datalist.size()==countfield(keywordList[2])){
            //约束
            dataoperation dto;
            QString tablePath=dirPath+"/table/"+keywordList[2]+"/"+keywordList[2]+".tdf";
            qDebug()<<"tablePath="<<tablePath;
            QFile tablefile(tablePath);
            if(!tablefile.open(QIODevice::ReadOnly|QIODevice::Text)){
                qDebug()<<"文件打开失败！";
            }
            QTextStream readcon(&tablefile);
            QStringList conlist;
            QString readinfo;
            int flag=0;
            for (int j=0;j<datalist.size();j++){
                readinfo = readcon.readLine();
                conlist = readinfo.split(",");
                if(conlist[1]=="number" && !dto.isDigitString(datalist[j]) ){
                    flag=1;
                }

                else if(conlist[1]=="date" && !dto.isDateString(datalist[j]) ){
                    flag=1;
                }
                else if(conlist[3]=="非空" && datalist[j]==NULL ){
                    flag=3;
                }
                else if(conlist[2]=="主键" && hassame(j,datalist[j])){
                    flag=2;
                }
            }
            qDebug()<<"flag="<<flag;
            if(flag==0){
                insertInfo += data + "\n";
                write << insertInfo;
                writeintoLOG(0, keywordList);
            }
            else if(flag==1){
                QMessageBox::critical(0, "critical", "请检查数据类型！",
                                      QMessageBox::Yes, QMessageBox::Yes);
            }
            else if(flag==2){
                QMessageBox::critical(0, "critical", "请检查主键是否有重复数据！",
                                      QMessageBox::Yes, QMessageBox::Yes);
            }
            else if(flag==3){
                QMessageBox::critical(0, "critical", "请检查非空字段是否有空数据！",
                                      QMessageBox::Yes, QMessageBox::Yes);
            }
            //

        }
        else{
            QMessageBox::critical(0, "错误", "请检查插入数据个数！",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
        }



        file.close();
    }
    else {
        QMessageBox::critical(0, "错误", "无插入数据权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void ManageDataBySql::deleteData(QStringList keywordList) {
    Privilegemanager ifmdt;

    if (ifmdt.ddt(keywordList[1], userName)) {
        if ((keywordList[1] == "") ||
            (keywordList[2] == "")) {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }


        QString fieldPath = dirPath + "/table/" + keywordList[1] + "/" +
                            keywordList[1] + ".tdf";
        tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                    keywordList[1] + ".trd";
        qDebug() << "当前字段的路径为：" + fieldPath;
        qDebug() << "当前数据的路径为：" + tablePath;
        QFile readFile(tablePath);
        QFile fieldFile(fieldPath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&readFile);
        QTextStream readfield(&fieldFile);

        QString afterDelPath = dirPath + "/table/" + keywordList[1] +
                               "/del.trd";
        QFile writeFile(afterDelPath);

        if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&writeFile);
        QStringList list, datalist, delline;
        QString     str, delfield, data, delInfo;

        delfield = keywordList[2];

        // 要删除的那一列的列号
        int deleColId = 0;

        while (!readfield.atEnd()) {
            str = readfield.readLine();
            list = str.split(",");

            if (list[0] == delfield) {
                qDebug() << "delecolid=" << deleColId;

                while (!read.atEnd()) {
                    data = read.readLine();
                    datalist = data.split(",");

                    if (datalist[deleColId] == keywordList[4]) {
                        delline = datalist;

                        for (int i = 0; i < delline.size(); i++) {
                            if (i < delline.size() - 1) {
                                delInfo = delline[i] + ",";
                            }
                            else if (i == delline.size() - 1) {
                                delInfo = delline[i];
                            }
                        }
                    }

                    else {
                        write << data + "\n";
                    }
                }
            }
            else {
                deleColId++;
            }
        }
        writeintoLOG(1, keywordList);
        fieldFile.close();
        readFile.close();
        readFile.remove();
        writeFile.close();
        writeFile.rename(tablePath);
    }
    else {
        QMessageBox::critical(0, "错误", "无删除数据权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void ManageDataBySql::updateData(QStringList keywordList) {
    Privilegemanager ifmdt;

    if (ifmdt.mdt(keywordList[1], userName)) {
        if ((keywordList[1] == "") ||
            (keywordList[2] == "")) {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }


        QString fieldPath = dirPath + "/table/" + keywordList[1] + "/" +
                            keywordList[1] + ".tdf";
        tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                    keywordList[1] + ".trd";
        qDebug() << "当前字段的路径为：" + fieldPath;
        qDebug() << "当前数据的路径为：" + tablePath;
        QFile readFile(tablePath);
        QFile fieldFile(fieldPath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        QString str0;
        QStringList list0;
        QTextStream updatedata(&fieldFile);
        QString     updatefield = keywordList[2];
        int update = 0;

        while (!updatedata.atEnd()) {
            str0 = updatedata.readLine();
            list0 = str0.split(",");

            if (list0[0] == updatefield) {
                qDebug() << "updatecolid=" << update;
                updateColId = update;
            }
            else {
                update++;
            }
        }
        fieldFile.close();

        if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        QTextStream read(&readFile);
        QTextStream readfield(&fieldFile);

        QString afterDelPath = dirPath + "/table/" + keywordList[1] +
                               "/del.trd";
        QFile writeFile(afterDelPath);

        if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&writeFile);
        QStringList list, datalist, updateline;
        QString     str, fofield, data, updateInfo;

        fofield = keywordList[4];

        // 要定位行的那一列的列号
        int foColId = 0;

        while (!readfield.atEnd()) {
            str = readfield.readLine();
            list = str.split(",");

            if (list[0] == fofield) {
                qDebug() << "foid=" << foColId;

                while (!read.atEnd()) {
                    data = read.readLine();
                    datalist = data.split(",");

                    if (datalist[foColId] == keywordList[6]) {
                        updateline = datalist;
                        updateInfo = "";

                        for (int i = 0; i < updateline.size(); i++) {
                            if (i < updateline.size() - 1) {
                                if (i == updateColId) {
                                    updateInfo = updateInfo + keywordList[3] +",";
                                }
                                else {
                                    updateInfo = updateInfo + updateline[i] + ",";
                                }
                            }
                            else if (i == updateline.size() - 1) {
                                if (i == updateColId) {
                                    updateInfo = updateInfo + keywordList[3];
                                }
                                else {
                                    updateInfo = updateInfo + updateline[i];
                                }
                            }
                            qDebug() << "updateInfo=" << updateInfo;
                        }
                        qDebug() << "updateInfo=" << updateInfo;
                        write << updateInfo + "\n";
                    }

                    else {
                        write << data + "\n";
                    }
                }
            }
            else {
                foColId++;
            }
        }
        writeintoLOG(2, keywordList); // 写入日志
        fieldFile.close();
        readFile.close();
        readFile.remove();
        writeFile.close();
        writeFile.rename(tablePath);
    }
    else {
        QMessageBox::critical(0, "错误", "无修改数据权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}



void ManageDataBySql::writeintoLOG(int i, QStringList keywordList) {
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString fileName = dir->path() + "/log/sys.txt";
    QFile   file(fileName);

    QDateTime dateTime;

    dateTime = QDateTime::currentDateTime();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::warning(NULL,
                             "警告！",
                             "错误！",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
    }
    QTextStream streamFile(&file);

    if (i == 0) {
        streamFile << dbName << "|" << userName << "|" <<
            dateTime.toString("yyyy-MM-dd hh:mm:ss") << "|" << "insert into " <<
            keywordList[2] << " values(" << keywordList[3] << ");" << endl;
    }
    else if (i == 1) {
        streamFile << dbName << "|" << userName << "|" <<
            dateTime.toString("yyyy-MM-dd hh:mm:ss") << "|" << "delete from " <<
            keywordList[1] << " where " << keywordList[2] << keywordList[3] <<
            keywordList[4] << ";" << endl;
    }
    else {
        streamFile << dbName << "|" << userName << "|" <<
            dateTime.toString("yyyy-MM-dd hh:mm:ss") << "|" << "update " <<
            keywordList[1] << " set " << keywordList[2] << "=" << keywordList[3]
                   << " where " << keywordList[4] << keywordList[5] <<
            keywordList[6] << ";" << endl;
    }
    file.close();
}

bool ManageDataBySql::hassame(int i,QString str){
    int flag=0;
    qDebug() << tablePath;
    QFile datafile(tablePath);
    if (!datafile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readdata(&datafile);
    QStringList list;
    QString string;
    while(!readdata.atEnd()){
        string=readdata.readLine();
        list=string.split(",");
        if(str==list[i]){
            flag=1;
        }
    }
    datafile.close();
    if(flag==1){
        return true;
    }
    else{
        return false;
    }
}

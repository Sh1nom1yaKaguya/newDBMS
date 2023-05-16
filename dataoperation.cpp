#include "dataoperation.h"
#include "ui_dataoperation.h"
#include "privilegemanager.h"
#include "QFileDialog"
#include "qdebug.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTimer"
#include "QDateTime"
using namespace std;

dataoperation::dataoperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dataoperation)
{
    ui->setupUi(this);
    initDir();
}

dataoperation::~dataoperation()
{
    delete ui;
}

void dataoperation::initDir(){
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");

    user=list[0];

    dirPath = dir->path() + "/data/" + list[1];
    qDebug() << dirPath;
    file.close();
}

void dataoperation::on_pushButton_clicked()
{


    QString fileName = dirPath + "/table/" +
                       this->ui->path->text() + "/" +
                       this->ui->path->text() + ".trd";
    filename=fileName;

    //字段文件
    QString tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                        this->ui->path->text() + ".tdf";
    qDebug() << tablePath;
    QFile tablefile(tablePath);
    if (!tablefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readtable(&tablefile);
    QStringList headlist, tablelist;
    QString readinfo;
    //表头
    while (!readtable.atEnd()) {
        readinfo = readtable.readLine();
        tablelist = readinfo.split(",");
        headlist.append(tablelist[0]);
    }

    //列数
    QString tableP = dirPath + "/table/" + this->ui->path->text() + "/" +
                     this->ui->path->text() + ".tdf";
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
    col=n;

    if (!fileName.isEmpty())
    {
        x.clear(); // x的值
        qv2.clear();

        QFile readfile(fileName);

        if (!readfile.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "ERROR", "The table does not exist!");
            return;
        }
        QTextStream read(&readfile);
        QStringList list;
        QString fileLine;


        qDebug() << "list1="<<list1;

        // 逐行读取数据并将每列分别存入x、y数组中
        while (!read.atEnd())
        {
            fileLine = read.readLine();
            list = fileLine.split(",");

            qDebug() << "list.count="<<list.count();
            x.clear();

            for (int i = 0; i < col; i++)
            {
                QString A = list.at(i); // 获取该行第1个单元格内容
                qDebug()<<"A="<<A;
                x.append(A);
                qDebug()<<"x="<<x;
            }

            qv2.append(x);
            qDebug() << "qv2=" << qv2;
        }
        qDebug() << "x=" << x;
        qDebug() << "qv2=" << qv2;

        tablefile.close();
        tablef.close();
        readfile.close();

    }


    int row = qv2.size(); // 行数


    qDebug() << "row="<<row;
    qDebug()<<"col="<<col;


    this->ui->tableWidget->setRowCount(row);                    // 设置行数
    this->ui->tableWidget->setColumnCount(col);                 // 设置列数

    this->ui->tableWidget->setHorizontalHeaderLabels(headlist); // 表头

    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->ui->tableWidget->setItem(0, 0, new QTableWidgetItem("1"));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) this->ui->tableWidget->setItem(i,
                                                                     j,
                                                                     new QTableWidgetItem(
                                                                         qv2[i][j]));
    }
}

void dataoperation::on_pushButton_insert_clicked() {

    Privilegemanager ifmdt;
    if(ifmdt.adt(this->ui->path->text(), user)){
        int row = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(row);

        for (int j = 0; j < col; j++) this->ui->tableWidget->setItem(row,
                                                                     j,
                                                                     new QTableWidgetItem(
                                                                         ""));
    }
    else{
        QMessageBox::critical(0, "错误", "无权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }

}

void dataoperation::on_pushButton_delete_clicked()
{

    Privilegemanager ifmdt;
    if(ifmdt.ddt(this->ui->path->text(),user)){
        int i = ui->tableWidget->currentRow();

        ui->tableWidget->removeRow(i);
        ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    }
    else{
        QMessageBox::critical(0, "错误", "无权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }

}




void dataoperation::on_pushButton_save_clicked()
{
    Privilegemanager ifmdt;
    if(ifmdt.mdt(this->ui->path->text(),user)){
        save();
    }
    else{
        QMessageBox::critical(0, "错误", "无权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void dataoperation::save(){
    QFile file2(filename);

    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "critical", tr("File saving failed!"),
                              QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        QTextStream  stream(&file2);
        QString      conTents;


        QString tablePath=dirPath+"/table/"+this->ui->path->text()+"/"+this->ui->path->text()+".tdf";
        qDebug()<<"tablePath="<<tablePath;
        QFile tablefile(tablePath);
        if(!tablefile.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败！";
        }
        QTextStream readcon(&tablefile);
        QStringList collist,conlist;
        QString readinfo;
        int flag=0;

        for (int j=0;j<ui->tableWidget->columnCount();j++){
            readinfo = readcon.readLine();
            conlist = readinfo.split(",");
            collist.clear();
            for(int i=0;i<ui->tableWidget->rowCount();i++){
                QTableWidgetItem *item = ui->tableWidget->item(i,j);
                if(conlist[1]=="number" && !isDigitString(item->text()) ){
                    flag=1;
                }

                else if(conlist[1]=="date" && !isDateString(item->text()) ){
                    flag=1;
                }
                else if(conlist[3]=="非空" && item->text()==NULL ){
                    flag=3;
                }
                collist.append(item->text());
            }
            if(conlist[2]=="主键" && hasSame(collist)){
                flag=2;
            }

        }

        qDebug()<<"flag="<<flag;

        for ( int i = 0; i < ui->tableWidget->rowCount(); i++ )
        {
            for ( int j = 0; j < ui->tableWidget->columnCount(); j++ )
            {
                QTableWidgetItem *item = ui->tableWidget->item(i, j);

                if (!item)
                {
                    continue;
                }

                QString str = item->text();
                str.replace(",", " ");

                if (j < ui->tableWidget->columnCount() - 1) conTents += str + ",";
                else conTents += str;
            }
            conTents += "\n";
        }

        if(flag==1){
            QMessageBox::critical(this, "critical", tr("请检查数据类型！"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(flag==2){
            QMessageBox::critical(this, "critical", tr("请检查主键是否有重复数据！"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(flag==3){
            QMessageBox::critical(this, "critical", tr("请检查非空字段是否有空数据！"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(flag==0){
            stream << conTents;
            file2.close();
        }

    }
}

void dataoperation::on_pushButton_exit_clicked() {
    this->close();
}

bool dataoperation::isDigitString(const QString& src) {
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9')s++;
    return !bool(*s);
}

bool dataoperation::isDateString(QString str){
    QDateTime date = QDateTime::fromString(str,"yyyyMMdd");
    bool res;
    if(str==""){
        res=true;
    }
    else res = date.isValid();

    if(res)    {
        qDebug()<<"res is true:"<<res;
    }
     else{
        qDebug()<<"res is false:"<<res;
    }
    return res;
}

bool dataoperation::hasSame(QStringList list){
    int i=0,j=0,flag=0;
    for(i=0;i<list.size();i++){
        for(j=i+1;j<list.size();j++){
            qDebug()<<"list["<<i<<"]="<<list[i];
            qDebug()<<"list["<<j<<"]="<<list[j];
            if(list[i]==list[j]){
                flag=1;
            }
        }
    }
    if (flag==0){
        return false;
    }
    else return true;
}

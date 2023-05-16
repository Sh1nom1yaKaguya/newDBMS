#include "dbmanager.h"
#include "login.h"
#include "qdir.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "selectdatabase.h"
#include "qfile.h"
/**
 * 1.@projectName: DBMS
 * 4.brief         数据库的创建、删除
 */
dbmanager::dbmanager()
{
    // 初始化系统目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    path = dir->path() + "/data/";
}


//创建用户数据库
void dbmanager::myCreateDataBase(QString dataname) {
    qDebug() << dataname;
    QDir *dir1 = new QDir(QDir::currentPath());

    dir1->cdUp();
    //QString path1 = dir1->path()+"/DBMS/data/sys";
    dataPath = path  + dataname;
    QDir dir(dataPath);

    if (dir.exists()) {
        qDebug() << "数据库创建失败";
        QMessageBox::warning(NULL,
                             "警告！",
                             "创建数据库失败",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);

        return;
    } else {
        dir.mkdir(dataPath);
        QMessageBox::information(NULL, "提示",
                                 "创建数据库成功！",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes);

//        qDebug() << dataPath;
//        qDebug() << "数据库创建成功";
        //表文件夹创建
     QString tablepath=dataPath+"/table";
     QDir dir1(tablepath);
     if(!dir1.exists()){
         dir1.mkdir(tablepath);
     }

     //视图文件夹创建
     QString viewpath=dataPath+"/view";
     QDir dir2(viewpath);
     if(!dir2.exists()){
         dir2.mkdir(viewpath);
     }


     //用户信息文件创建及信息输入
    QString userin =path+dataname+"/userinfo.txt";
    QFile   userfile(userin);

    if (!userfile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug()<<"打卡文件失败";
    }
     QTextStream outu(&userfile);

    QString adminpath=path+"sys/admin.txt.txt";
    QFile adminfile(adminpath);
    if(!adminfile.open(QIODevice::ReadOnly)){
        qDebug()<<"Can't open the file!";
        return;
    }
    QTextStream reada(&adminfile);
    QString adminuser=reada.readLine();
    while(!adminuser.isNull()){
        outu<<adminuser<<endl;
        adminuser=reada.readLine();

    }
    adminfile.close();
    userfile.close();
    //用户权限文件创建
    QString userpri =path+dataname+"/userprivilege.txt";
    QFile   userprifile(userpri);

    if (!userprifile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug()<<"打卡文件失败";
    }

//把新建数据库信息存入结构体中
        database my_database;
        char    *pre = dataname.toLatin1().data();
        memcpy(my_database.daname,   pre,  128);
        my_database.crtime = QDateTime::currentDateTime();
        char *pre2 = dataPath.toLatin1().data();
        memcpy(my_database.filename, pre2, 256);
        my_database.type = true;
       // writeDBinto(my_database);




        //创建基本信息文件
        QFile file01(dataPath + "/" + dataname + ".db");
        if (!file01.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
        }

        QTextStream out(&file01);
        out<<"NAME: "+dataname+"\n";
        out<<"TYPE: 用户\n";
        out<<"FILENAME: "+dataPath+"\n";
        out<<"CREATENAME: "+(my_database.crtime).toString("yyyy-mm-dd hh.mm.ss");
        file01.close();

    }
}



void dbmanager::myDeteleDataBase(QString dataname) {
    qDebug() << dataname;
    dataPath = path + "/" + dataname;
    qDebug() << dataPath;
    QDir dir(dataPath);

    if (dir.exists()) {
        dir.removeRecursively();
        QMessageBox::information(NULL, "提示",
                                 "删除数据库成功！",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes);
        qDebug() << "数据库删除成功";
     //   writedelDBinto(dataname);
        return;
    } else {
        QMessageBox::warning(NULL,
                             "警告！",
                             "删除数据库失败",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
        qDebug() << "数据库删除失败";
        return;
    }
}

// 将创建数据库日志写入文件
void dbmanager::writeDBinto(struct dataBase my_database) {
    // 初始化系统目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString fileName = dir->path() + "/log/sys.txt";
    QFile   file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::warning(NULL,
                             "警告！",
                             "错误！",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
    }
    QTextStream streamFile(&file);

    streamFile << endl;
    extern QString name;


        streamFile << name << "create " << my_database.daname << " dataBase ";
        streamFile << "filepath: " << my_database.filename << " " <<
            my_database.crtime.toString() << endl;


    file.close();
}

void dbmanager::writedelDBinto(QString dataname) {
    // 初始化系统目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString fileName = dir->path() + "/log/sys.txt";
    QFile   file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::warning(NULL,
                             "警告！",
                             "错误！",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
    }
    QTextStream streamFile(&file);

    streamFile << endl;
      extern QString name;
       streamFile << name << " delete database " << dataname << endl;

    file.close();
}

#include "selectdatabase.h"
#include "ui_selectdatabase.h"
#include "qdir.h"
#include"qtextstream.h"
#include"qdebug.h"
#include"qmessagebox.h"
selectdatabase::selectdatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectdatabase)
{
    ui->setupUi(this);
}

selectdatabase::~selectdatabase()
{
    delete ui;
}

// 打开数据库
void selectdatabase::on_pushButton_clicked()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString path=dir->path()+"/data/sys";
      QFile *file = new QFile(path+ "/curuse.txt");//此路径下没有就会自己创建一个
    if(!file->open(QIODevice::WriteOnly))

       {
           QMessageBox::critical(nullptr, "tips", "create file error");
           return;
       }

        QTextStream txtOutput(file);

        extern QString name;
        txtOutput <<name<<","<<ui->lineEdit->text();
        txtOutput.flush();

        file->close();

        QMessageBox::information(NULL,
                                 "提示",
                                 "选择数据库成功！",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes);
     qDebug()<<"选择数据库成功";
    // dpath=dir->path()+"/DBMS/data/"+name+"/"+ui->lineEdit->text();
}

void selectdatabase::on_pushButton_2_clicked()
{
    close();
}

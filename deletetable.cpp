#include "deletetable.h"
#include "ui_deletetable.h"
#include "QFileDialog"
#include "qdebug.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "privilegemanager.h"

/**
   1. @ProjName:   DBMS
   4. @Brief:      删除用户指定的数据库
 **/

deletetable::deletetable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deletetable)
{
    ui->setupUi(this);
}

deletetable::~deletetable()
{
    delete ui;
}

/*
 * @Brief:  根据界面的输入，删除对应的表文件
 * @Return: NULL
 */
void deletetable::on_deleButton_clicked()
{
    // 初始化用户目录，读取当前的用户和所使用的数据库
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    // 以只读方式打开信息文件
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    // list中依次存储着用户名和数据库名
    list = str.split(",");
    file.close();

    // 首先进行用户权限判断
    Privilegemanager deleJudge;

    if (!deleJudge.dtb(this->ui->lineEdit->text(), list[0])) {
        QMessageBox::critical(0, "错误", "无删除此表权限",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 若表名输入不为空，则进行删除
    if (this->ui->lineEdit->text() != "") {
        // 根据传入的用户名和数据库名，删除相应位置的表文件
        TableManager TM(list[0], list[1]);
        TM.tableDelete(this->ui->lineEdit->text());
        QMessageBox::information(0,
                                 "通知",
                                 "删除成功",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
    } else {
        QMessageBox::critical(0, "错误", "请输入表名",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
    this->ui->lineEdit->clear();
}

// 退出该界面的按钮
void deletetable::on_quitButton_clicked()
{
    this->close();
}

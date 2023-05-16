#include "createdatabase.h"
#include "ui_createdatabase.h"
#include <iostream>
#include "dbmanager.h"
createdatabase::createdatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createdatabase)
{
    ui->setupUi(this);
}

createdatabase::~createdatabase()
{
    delete ui;
}

void createdatabase::on_pushButton_clicked()
{
    QString str = ui->lineEdit->text();

        dbmanager *userdata = new dbmanager();
        userdata->myCreateDataBase(str);

}

void createdatabase::on_pushButton_2_clicked()
{
    close();
}

#include "deletedatabase.h"
#include "ui_deletedatabase.h"
#include "dbmanager.h"

deletedatabase::deletedatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deletedatabase)
{
    ui->setupUi(this);
}

deletedatabase::~deletedatabase()
{
    delete ui;
}

void deletedatabase::on_pushButton_2_clicked()
{
    QString str = ui->lineEdit->text();

        dbmanager *userdata = new dbmanager();
        userdata->myDeteleDataBase(str);

}

void deletedatabase::on_pushButton_clicked()
{
    close();
}

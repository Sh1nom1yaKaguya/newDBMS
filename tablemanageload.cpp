#include "tablemanageload.h"
#include "ui_tablemanageload.h"
#include "fieldmanager.h"
#include "creattable.h"
#include "deletetable.h"
tablemanageload::tablemanageload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tablemanageload)
{
    ui->setupUi(this);
}

tablemanageload::~tablemanageload()
{
    delete ui;
}

void tablemanageload::on_updatetable_clicked()
{
    FieldManager *fd = new FieldManager();

    fd->show();
    close();
}

void tablemanageload::on_deletetable_clicked()
{
    deletetable *dt = new deletetable();

    dt->show();
    close();
}

void tablemanageload::on_creattable_clicked()
{
    CreatTable *ct = new CreatTable();

    ct->show();
    close();
}

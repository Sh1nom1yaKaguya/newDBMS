#include "logdialog.h"
#include "ui_logdialog.h"
#include "qdir.h"
#include "qtextstream.h"
#include "QDebug"
LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::showlog() {
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString path = dir->path() + "/log/sys.txt";

    QFile file(path);

    if (!file.open(QIODevice::ReadWrite)) return;

    QTextStream out(&file);

    while (!file.atEnd())
    {
        ui->textEdit->setText(out.readAll());
    }

    qDebug() << "打开日志";
}

void LogDialog::on_pushButton_clicked()
{
    close();
}

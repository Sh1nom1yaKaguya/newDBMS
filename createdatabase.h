#ifndef CREATEDATABASE_H
#define CREATEDATABASE_H

#include <QWidget>
#include"selectdatabase.h"
namespace Ui {
class createdatabase;
}

class createdatabase : public QWidget
{
    Q_OBJECT

public:
    explicit createdatabase(QWidget *parent = nullptr);
    ~createdatabase();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::createdatabase *ui;
};

#endif // CREATEDATABASE_H

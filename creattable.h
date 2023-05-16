#ifndef CREATTABLE_H
#define CREATTABLE_H

#include <QWidget>
#include "fieldmanager.h"
namespace Ui {
class CreatTable;
}

class CreatTable : public QWidget {
    Q_OBJECT

public:

    explicit CreatTable(QWidget *parent = nullptr);
    ~CreatTable();

private slots:

    void on_add_clicked();

    void on_pushButton_clicked();

private:

    Ui::CreatTable *ui;
};

#endif // CREATTABLE_H

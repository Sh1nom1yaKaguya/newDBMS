#ifndef DELETEDATABASE_H
#define DELETEDATABASE_H

#include <QWidget>

namespace Ui {
class deletedatabase;
}

class deletedatabase : public QWidget
{
    Q_OBJECT

public:
    explicit deletedatabase(QWidget *parent = nullptr);
    ~deletedatabase();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::deletedatabase *ui;
};

#endif // DELETEDATABASE_H

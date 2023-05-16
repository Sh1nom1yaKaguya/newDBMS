#ifndef SELECTDATABASE_H
#define SELECTDATABASE_H

#include <QWidget>
extern QString dpath;//创建全局变量用户数据库路径
namespace Ui {
class selectdatabase;
}

class selectdatabase : public QWidget
{
    Q_OBJECT

public:
    explicit selectdatabase(QWidget *parent = nullptr);
    ~selectdatabase();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::selectdatabase *ui;
};

#endif // SELECTDATABASE_H

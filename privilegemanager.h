#ifndef PRIVILEGEMANAGER_H
#define PRIVILEGEMANAGER_H

#include <QWidget>

namespace Ui {
class Privilegemanager;
}

class Privilegemanager : public QWidget
{
    Q_OBJECT

public:
    explicit Privilegemanager(QWidget *parent = nullptr);
    ~Privilegemanager();

    //返回是否具有下列权限
    bool ctb(QString,QString);//创建表
    bool dtb(QString,QString);//删除表
    bool adt(QString,QString);//增加数据
    bool ddt(QString,QString);//删除数据
    bool mdt(QString,QString);//修改数据

    void grant(QStringList);
    void revoke(QStringList);

private slots:

    void on_querry_clicked();

    void on_finish_clicked();

    void on_exit_clicked();




private:
    Ui::Privilegemanager *ui;

    void initDir();
    void display();
    bool isfuserexist(QString,QString);
    bool isuserexist(QString);
    void initPrivilege(QString,QString);


    QString dirPath;
    QString dbName;
    QString userName;
    QString privilegePath;
    QString tablePath;
    QString tPath;

};

#endif // PRIVILEGEMANAGER_H

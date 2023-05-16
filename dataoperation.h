#ifndef DATAOPERATION_H
#define DATAOPERATION_H

#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class dataoperation;
}

class dataoperation : public QWidget
{
    Q_OBJECT

public:
    explicit dataoperation(QWidget *parent = nullptr);
    ~dataoperation();

    bool isDigitString(const QString& src);

    bool isDateString(QString str);

    //打开，插入，删除，保存，退出
private slots:
    void on_pushButton_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_exit_clicked();



private:
    Ui::dataoperation *ui;

    void initDir();
    void save();

    bool hasSame(QStringList list);

    QString dirPath;
    QString dbName;
    QString tableName;
    QString dataPath;
    QVector<QString> x;
    QVector<QVector<QString>> qv2;
    int col;
    QStringList list1;
    QString filename;
    QString user;
};

#endif // DATAOPERATION_H

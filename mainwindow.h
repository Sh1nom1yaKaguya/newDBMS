#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItemModel>
#include "landing.h"
#include <QMainWindow>
#include "createdatabase.h"
#include "deletedatabase.h"
#include "selectdatabase.h"
#include "fieldmanager.h"
#include "dataoperation.h"
#include "tablemanageload.h"
#include "privilegemanager.h"
#include "analysissql.h"
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTime(QTime);

private slots:

    void newActionsSlot();
    void selectActionSlot();
    void deleteActionSlot();
    void rlandActionSlot();
    void privileActionSlot();
    void exitActionSlot();
    void logActionSlot();
    void on_tablemanage_clicked();
    void on_datamanage_clicked();
    void on_fieldmanage_clicked();
    void setVisibleSlot();
    void resetPsdSlot();
    void showTime();
    void on_run_clicked();
    void on_rollback_clicked();
    void on_commit_clicked();

private:

    Ui::MainWindow *ui;
    QStandardItemModel *model;
    landing *l;
    AnalysisSQL *dealwithSql;
    QString dirPath;
    QString dbname;


    void        displayField(QString);
    void        displayData(QString);
    void        displayDir();
    void        importScript(QString);
    void        parseSql(QString);
    void        selectData(QStringList);
    bool        selectByIndex(QStringList);
    bool        bakeupFile();
    bool        isLogExists();
    QStringList gettablelist();
};
#endif // MAINWINDOW_H

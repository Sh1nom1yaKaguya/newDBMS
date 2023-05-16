#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablemanager.h"
#include "login.h"
#include "qdialog.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qstandarditemmodel.h"
#include "qpushbutton.h"
#include <string>
#include <qstring.h>
#include <iostream>
#include "dbmanager.h"
#include "logdialog.h"
#include "resetpassword.h"
#include "managetablebysql.h"
#include "managefieldbysql.h"
#include "managedatabysql.h"
#include "qdirmodel.h"
#include "indexmanager.h"
#include "qelapsedtimer.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 去窗口边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);

    // 设置一个好看的时钟
    QTimer *timer = new QTimer(this);

    // 实时更新
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // 连接电子时钟
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    // 创建窗口点击事件的槽函数
    connect(ui->actionnew,
            &QAction::triggered,
            this,
            &MainWindow::newActionsSlot);
    connect(ui->actiondelete,
            &QAction::triggered,
            this,
            &MainWindow::deleteActionSlot);
    connect(ui->actionselect,
            &QAction::triggered,
            this,
            &MainWindow::selectActionSlot);
    connect(ui->actionlog,
            &QAction::triggered,
            this,
            &MainWindow::logActionSlot);

    connect(ui->actionrland,
            &QAction::triggered,
            this,
            &MainWindow::rlandActionSlot);
    connect(ui->actionpower,
            &QAction::triggered,
            this,
            &MainWindow::privileActionSlot);
    connect(ui->actionexit,
            &QAction::triggered,
            this,
            &MainWindow::exitActionSlot);
    connect(ui->actioncpassword,
            &QAction::triggered,
            this,
            &MainWindow::resetPsdSlot);

    // 初始化用户目录，读取当前的用户和所使用的数据库
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    // 以只读方式打开信息文件
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine().trimmed();

    // list中依次存储着用户名和数据库名
    list = str.split(",");
    file.close();

    if (list.size() < 2) {
        dbname = "";
    } else {
        dbname = list[1];
    }


    // 初始化登陆界面
    l = new landing();
    l->setVisible(true);
    connect(l, SIGNAL(setVisibleSignal()), this, SLOT(setVisibleSlot()));
    this->hide();

    // 初始化正则表达式处理语句
    dealwithSql = new AnalysisSQL();
    displayDir();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTime(QTime)
{}

/*
 * @Brief:  设置时钟的显示格式和当前时间
 * @Return: NULL
 */
void MainWindow::showTime()
{
    QTime   time = QTime::currentTime();
    QString txtTime = time.toString("hh:mm:ss");

    ui->lcdNumber->display(txtTime);
}

void MainWindow::newActionsSlot()
{
    createdatabase *cdb = new createdatabase();

    cdb->show();
}

void MainWindow::selectActionSlot()
{
    selectdatabase *sdb = new selectdatabase();

    sdb->show();
}

void MainWindow::deleteActionSlot()
{
    deletedatabase *dbd = new deletedatabase();

    dbd->show();
}

void MainWindow::logActionSlot() {
    LogDialog *log = new LogDialog();

    log->show();
    log->showlog();
}

void MainWindow::rlandActionSlot()
{
    l->setVisible(true);
    l->show();
}

void MainWindow::privileActionSlot()
{
    Privilegemanager *plg = new Privilegemanager();

    plg->show();
}

void MainWindow::exitActionSlot()
{
    on_commit_clicked();
    exit(0);
}

void MainWindow::on_tablemanage_clicked()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    file.close();


    if (list.length() == 2) {
        tablemanageload *tml = new tablemanageload();
        tml->show();
    } else {
        QMessageBox::critical(0, "critical message", "请新建或选择数据库",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void MainWindow::on_datamanage_clicked()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    file.close();

    if (list.length() == 2) {
        dataoperation *dp = new dataoperation();
        dp->show();
    } else {
        QMessageBox::critical(0, "critical message", "请新建或选择数据库",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void MainWindow::on_fieldmanage_clicked()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    file.close();

    if (list.length() == 2) {
        FieldManager *fm = new FieldManager();
        fm->show();
    } else {
        QMessageBox::critical(0, "critical message", "请新建或选择数据库",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void MainWindow::setVisibleSlot()
{
    this->setVisible(true);
}

// 重新设置密码
void MainWindow::resetPsdSlot()
{
    resetpassword *rpsd = new resetpassword;

    rpsd->show();
}

// 运行SQL代码
void MainWindow::on_run_clicked()
{
    // 获取关键字列表
    QStringList keywordList = dealwithSql->resolveSql(ui->sqllineEdit->text());

    qDebug() << "list大小为：" + QString::number(keywordList.size());

    // 容错判断
    if (keywordList.size() == 0) {
        QMessageBox::critical(0, "错误", "请检查SQL语句！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 根据返回的操作类型，进行相关的操作
    switch (keywordList[0].toInt()) {
    // -----数据库管理-----
    case 0:
    { dbmanager *userdata = new dbmanager();
      userdata->myCreateDataBase(keywordList[1]);
      break; }

    case 1:
    { dbmanager *userdata = new dbmanager();
      userdata->myDeteleDataBase(keywordList[1]);
      break; }


    // -----表管理-----
    // 创建表
    case 2:
    {
        ManageTableBySql mtbs;
        mtbs.createTable(keywordList[1]);
        break;
    }

    // 删除表
    case 3:
    {
        ManageTableBySql mtbs;
        mtbs.deleteTable(keywordList[1]);
        break;
    }

    // -----字段管理-----
    // 增加字段并展示
    case 4: {
        ManageFieldBySql mfbs;
        mfbs.addField2tdf(keywordList);
        displayField(keywordList[1]);
        break;
    }

    // 删除字段并展示
    case 5: {
        ManageFieldBySql mfbs;
        mfbs.deleFileFromtdf(keywordList);
        displayField(keywordList[1]);
        break;
    }

    // 修改字段并展示
    case 6: {
        ManageFieldBySql mfbs;
        mfbs.modifyInfo2tb(keywordList);
        displayField(keywordList[1]);
        break;
    }

    // -----数据管理-----
    // 插入
    case 7: {
        ManageDataBySql mdbs;
        mdbs.insertData(keywordList);
        displayData(keywordList[2]);
        break;
    }

    // 删除
    case 8: {
        ManageDataBySql mdbs;
        mdbs.deleteData(keywordList);
        displayData(keywordList[1]);
        break;
    }

    // 更新
    case 9: {
        ManageDataBySql mdbs;
        mdbs.updateData(keywordList);
        displayData(keywordList[1]);
        break;
    }

    // -----数据查询-----
    case 10:
    case 11:
    case 12: {
        if (!selectByIndex(keywordList)) {
            selectData(keywordList);
        }
        break;
    }

    /* // 特定字段
       case 11:
         selectData(keywordList);
         break;

       // 简单条件查询
       case 12:
         selectData(keywordList);

         break;*/

    // -----创建索引-----
    case 13:
    {  qDebug() << "main没问题";
       Indexmanager *my_index = new Indexmanager(keywordList[2]);
       my_index->createFalseIndex(keywordList);

       break; }

    // -----删除索引-----
    case 14:
    {  qDebug() << "main没问题";
       Indexmanager *my_index = new Indexmanager(keywordList[2]);
       my_index->deleteIndex(keywordList[1]);

       break; }

    // -----导入sql脚本-----
    case 15:
        importScript(keywordList[1]);
        break;

    // -----权限赋予和收回-----

    // 授予权限
    case 16: {
        Privilegemanager pmgrant;
        pmgrant.grant(keywordList);
        break;
    }

    // 收回权限
    case 17: {
        Privilegemanager pmrevoke;
        pmrevoke.revoke(keywordList);
        break;
    }

    default:
        break;
    }
    displayDir();
}

/*
 * @Brief:  在进行字段操作之后，展示出表定义文件信息
 * @Param:  tablename 要展示信息的表名称
 * @Return: NULL
 */
void MainWindow::displayField(QString tableName)
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "初始化文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    QString dbName = list[1];
    QString dirPath = dir->path() + "/data/" + list[1];

    file.close();

    ui->tableWidget->clear();

    QString tablePath = dirPath + "/table/" + tableName + "/" +
                        tableName + ".tdf";

    QFile tempFile(tablePath);
    bool  isTableExist = tempFile.exists();

    if (isTableExist) {
        tablePath = dirPath + "/table/" + tableName + "/" +
                    tableName + ".tdf";
        QFile readFile(tablePath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&readFile);

        QString str, info;
        QStringList strlist, headlist;
        headlist << "字段名" << "数据类型" << "是否为主键" << "可否为空";
        int rownum = 0, colnum = 4;
        ui->tableWidget->setColumnCount(colnum);

        while (!read.atEnd()) {
            str = read.readLine();

            if (str != "") {
                ui->tableWidget->setRowCount(rownum + 1);

                strlist = str.split(",");

                for (int i = 0; i < colnum; i++) {
                    ui->tableWidget->setItem(rownum, i,
                                             new QTableWidgetItem(strlist[i]));
                }
                rownum++;
            }
        }
        readFile.close();
        ui->tableWidget->setHorizontalHeaderLabels(headlist);
    }
}

void MainWindow::displayData(QString tableName) {
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");

    dirPath = dir->path() + "/data/" + list[1];
    qDebug() << dirPath;
    file.close();

    QString fileName = dirPath + "/table/" +
                       tableName + "/" +
                       tableName + ".trd";

    // 字段文件
    QString tablePath = dirPath + "/table/" + tableName + "/" +
                        tableName + ".tdf";

    qDebug() << tablePath;
    QFile tablefile(tablePath);

    if (!tablefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readtable(&tablefile);
    QStringList headlist, tablelist;
    QString     readinfo;

    // 表头
    while (!readtable.atEnd()) {
        readinfo = readtable.readLine();
        tablelist = readinfo.split(",");
        headlist.append(tablelist[0]);
    }

    // 列数
    QString tableP = dirPath + "/table/" + tableName + "/" +
                     tableName + ".tdf";

    qDebug() << tableP;
    QFile tablef(tableP);

    if (!tablef.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readt(&tablef);
    QString     readi;
    int n = 0;

    while (!readt.atEnd()) {
        readi = readt.readLine();
        n++;
    }
    int col = n;

    QVector<QString> x;
    QVector<QVector<QString> > qv2;

    if (!fileName.isEmpty())
    {
        x.clear(); // x的值
        qv2.clear();

        QFile readfile(fileName);

        if (!readfile.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "ERROR", "The table does not exist!");
            return;
        }
        QTextStream read(&readfile);
        QStringList list;
        QString     fileLine;

        // 逐行读取数据并将每列分别存入x、y数组中
        while (!read.atEnd())
        {
            fileLine = read.readLine();
            list = fileLine.split(",");

            qDebug() << "list.count=" << list.count();
            x.clear();

            for (int i = 0; i < col; i++)
            {
                QString A = list.at(i); // 获取该行第1个单元格内容
                qDebug() << "A=" << A;
                x.append(A);
                qDebug() << "x=" << x;
            }

            qv2.append(x);
            qDebug() << "qv2=" << qv2;
        }
        qDebug() << "x=" << x;
        qDebug() << "qv2=" << qv2;
        file.close();
    }


    int row = qv2.size();                                       // 行数

    this->ui->tableWidget->setRowCount(row);                    // 设置行数
    this->ui->tableWidget->setColumnCount(col);                 // 设置列数

    this->ui->tableWidget->setHorizontalHeaderLabels(headlist); // 表头

    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    this->ui->tableWidget->setItem(0, 0, new QTableWidgetItem("1"));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) this->ui->tableWidget->setItem(i,
                                                                     j,
                                                                     new QTableWidgetItem(
                                                                         qv2[i][j]));
    }
}

bool MainWindow::isLogExists()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    // 获取日志文件的路径
    QString logPath = dir->path() + "/log/sys.txt";

    // 打开日志文件
    QFile readLog(dir->path() + "/log/sys.txt");

    if (!readLog.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return false;
    }
    QTextStream read(&readLog);
    QStringList allLogInfo, sqlInfo;

    // 逐行读取出所有的日志信息
    while (!read.atEnd()) {
        allLogInfo.append(read.readLine().trimmed());
    }
    int idx1 = allLogInfo.lastIndexOf("revoke");
    int idx2 = allLogInfo.lastIndexOf("commit");

    qDebug() << "idx1:" + QString::number(idx1);
    qDebug() << "idx2:" + QString::number(idx2);

    // 定位到最后一次未提交或回滚的位置
    int lastUncheckIndex = idx1 > idx2 ? idx1 : idx2;

    qDebug() << "lastUncheckIndex:" + QString::number(idx2);

    for (int i = allLogInfo.size(); i > lastUncheckIndex + 1; i--) {
        if ((allLogInfo[i - 1] != "") || (allLogInfo[i - 1] != "\n")) {
            // 提取日志最后的sql语句
            sqlInfo.append(allLogInfo[i - 1].split("|").last());
        }
    }
    qDebug() << "sql提取成功";

    QStringList tablename, distList;

    for (int j = 0; j < sqlInfo.size(); j++) {
        // 获取关键字列表
        QStringList keywordList = dealwithSql->resolveSql(sqlInfo[j]);

        switch (keywordList[0].toInt()) {
        case 7:
            tablename.append(keywordList[2]);
            break;

        case 8:
            tablename.append(keywordList[1]);
            break;

        case 9:
            tablename.append(keywordList[1]);
            break;

        default:
            break;
        }
    }
    qDebug() << "关键字列表提取成功";

    // 获取不重复的表名
    for (int i = 0; i < tablename.length(); i++) {
        if (!distList.contains(tablename[i])) {
            distList.append(tablename[i]);
        }
    }
    qDebug() << distList;
    qDebug() << "获取不重复的表名成功";
    QStringList postfixList; // 后缀列表

    postfixList << ".tb" << ".tdf" << ".trd";


    for (int i = 0; i < distList.size(); i++) {
        // 替换目标文件
        // 备份文件
        QDir *dir = new QDir(QDir::currentPath());
        dir->cdUp();
        QString dirPath = dir->path() + "/temp/" + distList[i] + "/";
        qDebug() << "一层循环";

        for (int j = 0; j < postfixList.size(); j++) {
            qDebug() << "二层循环";

            // 原文件 包含路径 文件名
            QString sCurrentPath = dirPath + distList[i] + postfixList[j];

            // 要覆盖的文件 包含路径 文件名
            QString sBachUpPath = dir->path() + "/data/" +
                                  dbname + "/table/" +
                                  distList[i] + "/" + distList[i] +
                                  postfixList[j];
            qDebug() << sBachUpPath;
            QFile currenFile(sCurrentPath);
            QFile targetFile(sBachUpPath);

            if (targetFile.exists()) targetFile.remove();
            currenFile.copy(sBachUpPath); // copy函数不能直接创建文件夹,所有需要先把文件夹创建出来再进行拷贝
        }
    }
    QFile logFile(dir->path() + "/log/sys.txt");

    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text |
                      QIODevice::Append)) {
        qDebug() << "文件打开失败";
        return false;
    }
    QTextStream write(&logFile);

    write << "revoke\n";
    logFile.close();
    QMessageBox::information(0,
                             "通知",
                             "回滚成功，请重新查看",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);
    return false;
}

// 获取当前数据库目录下的所有表
QStringList MainWindow::gettablelist()
{
    QStringList names;
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    // --1 判断文件夹是否存在
    QString folderPath = dir->path() + "/data/" + dbname + "/table/";
    QDir    dbDir(folderPath);

    if (!dbDir.exists())
    {
        QMessageBox::critical(this, tr("错误"), tr("文件夹找不到"));
        return names;
    }

    // --2 获取当前路径下所有的文件夹名字
    // -- 注：QDir::Dirs 为获取所有文件夹名称，获取文件名称需要修改
    names = dbDir.entryList(QDir::Dirs);

    // --3 删除当前文件夹和上级文件夹（温馨提示：隐藏的文件夹获取不了）
    names.removeOne(".");
    names.removeOne("..");

    // --4 打印出获取的文件名
    qDebug() << "names: " << names;
    return names;
}

/*
 * @Brief:  在主界面展示目录结构
 * @Return: NULL
 */
void MainWindow::displayDir()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data";

    QDirModel *model = new QDirModel();

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(dirPath));

    for (int i = 1; i < model->columnCount(); i++)
    {
        ui->treeView->setColumnHidden(i, true);
    }
}

/*
 * @Brief:  通过导入sql脚本，解析并批量执行
 * @Param:  scriptPath 要导入的目标脚本的路径
 * @Return: NULL
 */
void MainWindow::importScript(QString scriptPath)
{
    // 根据导入的路径打开脚本文件
    QString fileName = scriptPath;
    QFile   file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL,
                             "警告！",
                             "错误！",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
        return;
    } else {
        QMessageBox::information(NULL,
                                 "成功",
                                 "成功",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes);
    }

    // 存储sql语句
    QString sqlinfo;

    // 逐行读取sql语句
    while (!file.atEnd()) {
        sqlinfo = file.readLine();
        parseSql(sqlinfo);
    }

    file.close();
}

void MainWindow::parseSql(QString sqlText)
{
    // 获取关键字列表
    QStringList keywordList = dealwithSql->resolveSql(sqlText);

    qDebug() << "list大小为：" + QString::number(keywordList.size());

    // 容错判断
    if (keywordList.size() == 0) {
        QMessageBox::critical(0, "错误", "请检查SQL语句！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 根据返回的操作类型，进行相关的操作
    switch (keywordList[0].toInt()) {
    // -----数据库管理-----
    case 0:
    { dbmanager *userdata = new dbmanager();
      userdata->myCreateDataBase(keywordList[1]);
      break; }

    case 1:
    { dbmanager *userdata = new dbmanager();
      userdata->myDeteleDataBase(keywordList[1]);
      break; }


    // -----表管理-----
    // 创建表
    case 2:
    {
        ManageTableBySql mtbs;
        mtbs.createTable(keywordList[1]);
        break;
    }

    // 删除表
    case 3:
    {
        ManageTableBySql mtbs;
        mtbs.deleteTable(keywordList[1]);
        break;
    }

    // -----字段管理-----
    // 增加字段并展示
    case 4: {
        ManageFieldBySql mfbs;
        mfbs.addField2tdf(keywordList);
        displayField(keywordList[1]);
        break;
    }

    // 删除字段并展示
    case 5: {
        ManageFieldBySql mfbs;
        mfbs.deleFileFromtdf(keywordList);
        displayField(keywordList[1]);
        break;
    }

    // 修改字段并展示
    case 6: {
        ManageFieldBySql mfbs;
        mfbs.modifyInfo2tb(keywordList);
        displayField(keywordList[1]);
        break;
    }

    // -----数据管理-----
    // 插入
    case 7: {
        ManageDataBySql mdbs;
        mdbs.insertData(keywordList);
        displayData(keywordList[2]);
        break;
    }

    // 删除
    case 8: {
        ManageDataBySql mdbs;
        mdbs.deleteData(keywordList);
        displayData(keywordList[1]);
        break;
    }

    // 更新
    case 9: {
        ManageDataBySql mdbs;
        mdbs.updateData(keywordList);
        displayData(keywordList[1]);
        break;
    }

    // -----数据查询-----
    // 全部字段
    case 10:
        displayData(keywordList[2]);
        break;

    // 特定字段
    case 11:
        selectData(keywordList);
        break;

    // 简单条件查询
    case 12:
        selectData(keywordList);
        break;

    // -----创建索引-----
    case 13:
    {  qDebug() << "main没问题";
       Indexmanager *my_index = new Indexmanager(keywordList[2]);
       my_index->createFalseIndex(keywordList);

       break; }

    // -----删除索引-----
    case 14:
    {  qDebug() << "main没问题";
       Indexmanager *my_index = new Indexmanager(keywordList[2]);
       my_index->deleteIndex(keywordList[1]);

       break; }


    default:
        break;
    }
}

/*
 * @Brief:  根据查询条件显示出对应的数据
 * @Param:  First
 * @Param:  Second
 * @Return: NULL
 */

// 测试 select (sname,sex) from course;
void MainWindow::selectData(QStringList keywordList)
{
    QElapsedTimer mstimer; // 定义对象

    mstimer.start();       // 开始计时
    ui->tableWidget->clear();

    // 判断关键字列表的大小，若长度大于3则说明存在筛选条件
    bool isWhere = keywordList.size() > 3 ? true : false;

    // 打开用户信息文件
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();
    QString     tableName = keywordList[2];

    // 划分用户名和密码
    list = str.split(",");
    dirPath = dir->path() + "/data/" + list[1];
    file.close();


    // 字段文件
    QString tablePath = dirPath + "/table/" + tableName + "/" +
                        tableName + ".tdf";
    QFile tablefile(tablePath);

    if (!tablefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readtable(&tablefile);
    QStringList headlist, tablelist;
    QString     readinfo;


    QString opeartSign;       // 比较符
    QString restrictValue;    // 限制的值
    int     restrictFieldCol; // 限制的字段所在的列
    QString dataType;         // 限制字段的数据类型

    // 读取表头
    while (!readtable.atEnd()) {
        readinfo = readtable.readLine();
        tablelist = readinfo.split(",");
        headlist.append(tablelist[0]);

        // 若存在筛选条件，则将限制变量进行赋值
        if (isWhere && (headlist.last() == keywordList[3])) {
            restrictFieldCol = headlist.indexOf(keywordList[3]);
            opeartSign = keywordList[4];
            restrictValue = keywordList[5];
            dataType = tablelist[1];

            qDebug() << dataType + "!!!!!!!!!!!!!!!!";

            // 若进行的是大小比较运算且数据类型不是数字，则退出
            if (((opeartSign == "<") || (opeartSign == ">")) &&
                (dataType != "number")) {
                QMessageBox::critical(0, "错误", "该数据类型不支持比较",
                                      QMessageBox::Ok | QMessageBox::Default,
                                      QMessageBox::Cancel | QMessageBox::Escape,
                                      0);
                return;
            }
        }
    }

    // 记录要展示字段对应的名称
    QStringList fieldList;

    // 记录要展示字段对应的列号
    QList<int> fieldCol;

    // 提取要展示的字段名称，若是*就是全部展示，否则展示指定的字段内容
    if (keywordList[1] == "*") {
        fieldList = headlist;
    } else {
        fieldList = keywordList[1].split(",");
    }

    // 记录数据的行数和列数
    int col = fieldList.size(), row = 0;

    ui->tableWidget->setColumnCount(col);

    // 依次找出对应的字段所在的列号
    for (int i = 0; i < fieldList.size(); i++) {
        fieldCol.append(headlist.indexOf(fieldList[i]));

        // 若返回值为-1则说明匹配不成功，sql出错
        if (fieldCol[i] == -1) return;
    }

    // 打开数据存储文件
    QString dataFilePath = dirPath + "/table/" +
                           tableName + "/" +
                           tableName + ".trd";

    // 判断需要的文件是否存在
    QFile dataFile(dataFilePath);

    qDebug() << "数据文件读取成功";

    if (dataFile.exists()) {
        if (!dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&dataFile);
        QString     dataInfo; // 接受文件每行的信息
        QStringList dataList;

        // 只要不读到末尾，就持续进行赋值
        while (!dataFile.atEnd()) {
            dataInfo = dataFile.readLine();
            dataInfo = dataInfo.trimmed(); // 去除换行符

            if (dataInfo != "") {
                // 以“,”为分割，划分出一行的数据
                dataList = dataInfo.split(",");

                // 如果没有筛选条件，则展示出对应字段的所有数据
                if (!isWhere) {
                    // 设置行数
                    ui->tableWidget->setRowCount(row + 1);

                    for (int i = 0; i < col; i++) {
                        ui->tableWidget->setItem(row, i,
                                                 new QTableWidgetItem(dataList[
                                                                          fieldCol
                                                                          [i]]));
                    }
                    row++;
                } else { // 有筛选条件，则根据筛选条件进行选择
                    // 如果是小于号，则进行大小比较
                    if (opeartSign == "<") {
                        qDebug() << dataList[restrictFieldCol].toInt();
                        qDebug() << restrictValue.toInt();
                        qDebug() << "-------------";

                        if (dataList[restrictFieldCol].toInt() <
                            restrictValue.toInt()) {
                            ui->tableWidget->setRowCount(row + 1);

                            for (int i = 0; i < col; i++) {
                                ui->tableWidget->setItem(row,
                                                         i,
                                                         new QTableWidgetItem(
                                                             dataList[fieldCol[i]]));
                            }
                            row++;
                        }
                    }
                    else if (opeartSign == "=") {
                        if (dataList[restrictFieldCol] == restrictValue) {
                            ui->tableWidget->setRowCount(row + 1);

                            for (int i = 0; i < col; i++) {
                                ui->tableWidget->setItem(row,
                                                         i,
                                                         new QTableWidgetItem(
                                                             dataList[fieldCol[i]]));
                            }
                            row++;
                        }
                    } else if (opeartSign == ">") {
                        if (dataList[restrictFieldCol].toInt() >
                            restrictValue.toInt()) {
                            ui->tableWidget->setRowCount(row + 1);

                            for (int i = 0; i < col; i++) {
                                ui->tableWidget->setItem(row,
                                                         i,
                                                         new QTableWidgetItem(
                                                             dataList[fieldCol[i]]));
                            }
                            row++;
                        }
                    } else
                    {
                        QMessageBox::critical(0,
                                              "错误",
                                              "请检查where条件",
                                              QMessageBox::Ok | QMessageBox::Default,
                                              QMessageBox::Cancel | QMessageBox::Escape,
                                              0);
                        return;
                    }
                }
            }
        }
        dataFile.close();

        // 添加表头
        ui->tableWidget->setHorizontalHeaderLabels(fieldList);

        // 毫秒计时
        float time = (double)mstimer.nsecsElapsed() / (double)1000000;
        qDebug() << "搜索用时:" << time << " ms";
        return;
    }
}

/*
 * @Brief:  通过索引查询
 * @Param:  keywordList 关键字列表
 * @Return: NULL
 */
bool MainWindow::selectByIndex(QStringList keywordList)
{
    /* 查询语句使用时
       1.  Indexmanager* idmg=new Indexmanager(QString tablename)
       2.  idmg.checkindex(QString finame1,QString finame2)
       查看含有该字段组的索引文件名，如果没有该索引，则返回NULL
       3.  idmg.SelectBtree(QString index_name,QString keyvalues)
       index_name为2中返回的索引名，keyvalues为关键字对应的值
       4.  imdg.searesult
       查找结果存在searesult中
       形式为"values1,values2"，若未找到相应值，则searesult值为"未查到相应结果"*/

    QStringList fieldList = keywordList[1].split(",");

    if (fieldList.size() == 2) {
        QElapsedTimer mstimer; // 定义对象
        mstimer.start();       // 开始计时
        Indexmanager *idmg = new Indexmanager(keywordList[2]);
        QString indexname = idmg->checkindex(fieldList[0], fieldList[1]);

        if (indexname != NULL) {
            qDebug() << "Last:" + keywordList.last();
            qDebug() << indexname;
            idmg->SelectBtree(indexname, keywordList.last());
            qDebug() << "SelectBtree执行完毕";
            qDebug() << idmg->searesult;

            if (idmg->searesult.contains(",")) {
                QStringList resultList = idmg->searesult.split(",");

                // 添加表头
                ui->tableWidget->setHorizontalHeaderLabels(fieldList);

                // 设置行列
                ui->tableWidget->setRowCount(1);
                ui->tableWidget->setColumnCount(2);

                for (int i = 0; i < 2; i++) {
                    ui->tableWidget->setItem(0, i,
                                             new QTableWidgetItem(resultList[i]));
                }

                // 毫秒计时
                float time = (double)mstimer.nsecsElapsed() / (double)1000000;
                qDebug() << "搜索用时:" << time << " ms";
                return true;
            }
        }
    }
    return false;
}

// 对文件进行备份
bool MainWindow::bakeupFile()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "初始化文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    QString dbName = list[1];

    file.close();

    QStringList tablenameList = gettablelist();

    if (tablenameList.size() == 0) {
        return false;
    }

    // 对所有表进行备份
    for (int i = 0; i < tablenameList.size(); i++) {
        QString dirPath = dir->path() + "/data/" + dbName + "/table/" +
                          tablenameList[i] + "/";
        QDir tableDir(dirPath);

        qDebug() << tableDir.exists();

        if (!tableDir.exists()) // 如果目标目录不存在
        {
            return false;
        }

        // 获取要操作的表路径
        QDir targetDir(dir->path() + "/temp/" + tablenameList[i] + "/");

        if (!targetDir.exists()) // 如果目标目录不存在，则进行创建
        {
            if (!targetDir.mkdir(targetDir.absolutePath()))
            {
                qDebug() << "创建备份文件夹错误!";
                return false;
            }
        }

        QStringList postfixList; // 后缀列表

        postfixList << ".tb" << ".tdf" << ".trd";

        for (int j = 0; j < postfixList.size(); j++) {
            // 源数文件 包含路径 文件名
            QString sCurrentPath = dirPath + tablenameList[i] + postfixList[j];

            // 备份文件 包含路径 文件名
            QString sBachUpPath = dir->path() + "/temp/" +
                                  tablenameList[i] + "/" +
                                  tablenameList[i] + postfixList[j];
            QFile currenFile(sCurrentPath);
            QFile targetFile(sBachUpPath);

            if (targetFile.exists()) targetFile.remove();
            currenFile.copy(sBachUpPath); // copy函数不能直接创建文件夹,所有需要先把文件夹创建出来再进行拷贝
        }
    }

    return true;
}

// 回滚按钮，点击后将文件回滚到上一次提交的结构
// 将本地文件内容更改为最新的备份文件
void MainWindow::on_rollback_clicked()
{
    // 若系统文件目录不存在，则返回，否则继续执行
    if (!isLogExists()) {
        return;
    }

    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    // 获取日志文件的路径
    QString logPath = dir->path() + "/log/sys.txt";

    // 打开日志文件
    QFile readLog(dir->path() + "/log/sys.txt");

    if (!readLog.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readLog);
    QStringList allLogInfo, sqlInfo;

    // 逐行读取出所有的日志信息
    while (!read.atEnd()) {
        allLogInfo.append(read.readLine().trimmed());
    }
    int idx1 = allLogInfo.lastIndexOf("revoke");
    int idx2 = allLogInfo.lastIndexOf("commit");

    // 定位到最后一次未提交或回滚的位置
    int lastUncheckIndex = idx1 > idx2 ? idx1 : idx2;

    for (int i = allLogInfo.size(); i > lastUncheckIndex + 1; i--) {
        if ((allLogInfo[i - 1] != "") || (allLogInfo[i - 1] != "\n")) {
            // 提取日志最后的sql语句
            sqlInfo.append(allLogInfo[i - 1].split("|").last());
        }
    }

    /*从最后一行向上反向逆推
       如果是增加，则找到对应增加的那一列删除
       如果是删除，则根据删除条件，从备份文件里找到被删除的数据
       如果是修改，则根据修改条件，总备份文件中找到被修改的数据，逐个替换掉修改后的数据
     * 数据管理
     * 插入：insert into tablename values(1,2,3);
     * 删除：delete from users where userid=001;
     * 更新：update tablename set username=111 where id=2;
     */

    for (int j = 0; j < sqlInfo.size(); j++) {
        // 获取关键字列表
        QStringList keywordList = dealwithSql->resolveSql(sqlInfo[j]);

        qDebug() << "list大小为：" + QString::number(keywordList.size());

        // 根据返回的操作类型，进行相关的操作
        switch (keywordList[0].toInt()) {
        // -----数据管理-----
        // 插入撤回
        case 7: {
            // 定位文件路径，以只读方式打开
            QString tablePath = dir->path() + "/data/" + dbname + "/table/" +
                                keywordList[2] + "/" +
                                keywordList[2] + ".trd";
            QFile readFile(tablePath);

            if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败";
                return;
            }
            QTextStream read(&readFile);

            // 创建新文件，来存储修改后的文件内容
            QString afterDelPath = dir->path() + "/data/" + dbname +
                                   "/table/" + keywordList[2] +
                                   "/del.trd";
            QFile writeFile(afterDelPath);

            if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败";
            }

            QTextStream write(&writeFile);
            QStringList list;
            QString     str, delInfo;

            // 获取要删除数据
            delInfo = keywordList[3].trimmed();

            // 要删除的那一列的列号

            // 执行删除操作，并记录要删除的字段是哪一列
            while (!read.atEnd()) {
                str = read.readLine().trimmed();

                if (str == delInfo) {
                    // 删除相应的数据
                }
                else {
                    write << str + "\n";
                }
            }

            // 将原文件用新文件替换
            readFile.close();
            readFile.remove();
            writeFile.close();
            writeFile.rename(tablePath);
            break;
        }

        // 删除
        case 8: {
            // 字段文件
            QString tdfPath = dir->path() + "/temp/" + dbname + "/table/" +
                              keywordList[1] + "/" +
                              keywordList[1] + ".tdf";
            QFile tdffile(tdfPath);

            if (!tdffile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败！";
            }
            QTextStream readtable(&tdffile);
            QStringList headlist, tablelist;
            QString     readinfo;

            QString opeartSign;       // 比较符
            QString restrictValue;    // 限制的值
            int     restrictFieldCol; // 限制的字段所在的列

            // 读取表头
            while (!readtable.atEnd()) {
                readinfo = readtable.readLine();
                tablelist = readinfo.split(",");
                headlist.append(tablelist[0]);

                // 若查询到筛选条件，则将限制变量进行赋值
                if (headlist.contains(keywordList[3])) {
                    restrictFieldCol = headlist.indexOf(keywordList[3]);
                    opeartSign = keywordList[4];
                    restrictValue = keywordList[5];
                }
            }

            // 定位文件路径，以只读方式打开
            QString tablePath = dir->path() + "/temp/" +
                                keywordList[1] + "/" +
                                keywordList[1] + ".trd";
            QFile readFile(tablePath);

            if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败";
                return;
            }
            QTextStream read(&readFile);

            // 创建新文件，来存储修改后的文件内容
            QString afterDelPath = dir->path() + "/data/" + dbname +
                                   "/table/" + keywordList[1] + "/" +
                                   keywordList[1] + ".trd";
            QFile writeFile(afterDelPath);

            if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text |
                                QIODevice::Append)) {
                qDebug() << "文件打开失败";
            }

            QTextStream write(&writeFile);
            QStringList list;
            QString     str, delInfo;


            // 逐行读取文本内容
            while (!read.atEnd()) {
                str = read.readLine().trimmed();
                list = str.split(",");

                // 根据符号条件进行判断
                if (opeartSign == "<") {
                    if (list[restrictFieldCol].toInt() < restrictValue.toInt()) {
                        write << str + "\n";
                    }
                } else if (opeartSign == "=") {
                    if (list[restrictFieldCol] == restrictValue) {
                        write << str + "\n";
                    }
                } else if (opeartSign == ">") {
                    if (list[restrictFieldCol].toInt() > restrictValue.toInt()) {
                        write << str + "\n";
                    }
                }
            }

            // 将原文件用新文件替换
            readFile.close();
            readFile.remove();
            writeFile.close();
            writeFile.rename(tablePath);
            break;
        }

        // 更新
        case 9: {
            // 字段文件
            QString tdfPath = dir->path() + "/data/" + dbname + "/table/" +
                              keywordList[1] + "/" +
                              keywordList[1] + ".tdf";
            QFile tdffile(tdfPath);

            if (!tdffile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败！";
            }
            QTextStream readtable(&tdffile);
            QStringList headlist, tablelist;
            QString     readinfo;

            QString opeartSign;       // 比较符
            QString restrictValue;    // 限制的值
            int     restrictFieldCol; // 限制的字段所在的列

            // 读取表头
            while (!readtable.atEnd()) {
                readinfo = readtable.readLine();
                tablelist = readinfo.split(",");
                headlist.append(tablelist[0]);

                // 若查询到筛选条件，则将限制变量进行赋值
                if (headlist.contains(keywordList[5])) {
                    restrictFieldCol = headlist.indexOf(keywordList[4]);
                    opeartSign = keywordList[5];
                    restrictValue = keywordList[6];
                }
            }

            // 定位文件路径，以只读方式打开
            QString tablePath = dir->path() + "/temp/" +
                                keywordList[1] + "/" +
                                keywordList[1] + ".trd";
            QFile readFile(tablePath);

            if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败";
                return;
            }
            QTextStream read(&readFile);

            // 新文件，来存储修改后的文件内容
            QString afterDelPath = dir->path() + "/data/" + dbname +
                                   "/table/" + keywordList[1] + "/" +
                                   keywordList[1] + ".trd";
            QFile writeFile(afterDelPath);

            if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text |
                                QIODevice::Append)) {
                qDebug() << "文件打开失败";
            }

            QTextStream write(&writeFile);
            QStringList list;
            QString     str, delInfo;


            // 逐行读取文本内容
            while (!read.atEnd()) {
                str = read.readLine().trimmed();
                list = str.split(",");

                // 根据符号条件进行判断
                if (opeartSign == "<") {
                    if (list[restrictFieldCol].toInt() < restrictValue.toInt()) {
                        write << str + "\n";
                    }
                } else if (opeartSign == "=") {
                    if (list[restrictFieldCol] == restrictValue) {
                        write << str + "\n";
                    }
                } else if (opeartSign == ">") {
                    if (list[restrictFieldCol].toInt() > restrictValue.toInt()) {
                        write << str + "\n";
                    }
                }
            }

            // 将原文件用新文件替换
            readFile.close();
            readFile.remove();
            writeFile.close();
            writeFile.rename(tablePath);
            break;
        }

        default:
            break;
        }
    }

    QFile logFile(dir->path() + "/log/sys.txt");

    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text |
                      QIODevice::Append)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream write(&logFile);

    write << "revoke\n";
    logFile.close();
    QMessageBox::information(0,
                             "通知",
                             "回滚成功，请重新查看",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);
}

// 提交按钮，点击即可提交事务
// 进行commit后，将原来的备份文件删除，然后更新最新版本,
void MainWindow::on_commit_clicked()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    if (dbname == "") return;

    // 若数据备份成功，则说明提交成功
    if (bakeupFile()) {
        QFile logFile(dir->path() + "/log/sys.txt");

        if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text |
                          QIODevice::Append)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&logFile);
        write << "commit\n";
        logFile.close();
        qDebug() << "备份成功!";
    } else {
        qDebug() << "备份出错!";
    }
}

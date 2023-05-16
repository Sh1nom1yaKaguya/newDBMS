#include "resetpassword.h"
#include "ui_resetpassword.h"
#include "qmessagebox.h"
#include "qdir.h"
#include "qdebug.h"
#include <QCryptographicHash> // md5加密的库

/**
   1. @ProjName:   DBMS
   4. @Brief:      File Description
 **/

resetpassword::resetpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resetpassword)
{
    ui->setupUi(this);

    // 初始化系统目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    path = dir->path() + "/data";

    // 设置数据库目录列表
    getDbList();
}

resetpassword::~resetpassword()
{
    delete ui;
}

// 返回数据库文件夹的目录
void resetpassword::getDbList()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    // --1 判断文件夹是否存在
    QString folderPath = dir->path() + "/data";
    QDir    dbDir(folderPath);

    if (!dbDir.exists())
    {
        QMessageBox::critical(this, tr("错误"), tr("文件夹找不到-resetpassword.cpp"));
        return;
    }

    // --2 获取当前路径下所有的文件夹名字
    // -- 注：QDir::Dirs 为获取所有文件夹名称，获取文件名称需要修改
    QStringList names = dbDir.entryList(QDir::Dirs);

    // --3 删除当前文件夹和上级文件夹（温馨提示：隐藏的文件夹获取不了）
    names.removeOne(".");
    names.removeOne("..");
    names.removeOne("sys");

    // --4 将数据库名称添加到组件中
    for (int i = 0; i < names.size(); i++) {
        ui->dbName->addItem(names[i]);
    }
}

/*
 * @Brief:  根据用户输入，修改密码
 * @Return: NULL
 */
void resetpassword::on_modifyButton_clicked()
{
    // 判断要求输入的内容不能为空
    if ((ui->userName->text() == "") ||
        (ui->passWord->text() == "") ||
        (ui->passWord_2->text() == "")) {
        QMessageBox::critical(0, "错误", "请确保填写完全",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 检查原始用户名和密码是否一致
    if (!checkLog(ui->dbName->currentText(), ui->userName->text(),
                  ui->passWord->text())) {
        QMessageBox::critical(0, "错误", "请保证用户名位于所选数据库且原密码正确",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 防止密码太短
    if (ui->passWord_2->text().length() < 4) {
        QMessageBox::critical(0, "错误", "密码太短请修改",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }


    // 读取存储用户信息的文件
    QFile readFile(path + "/" + ui->dbName->currentText() + "/userinfo.txt");

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    // 要写入数据的文件
    QString afterDelPath = path + "/" + ui->dbName->currentText() + "/modify.txt";
    QFile   writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString     str, modInfo;

    // 获取要更新的对象
    modInfo = this->ui->userName->text();
    QString pw =
        QCryptographicHash::hash(ui->passWord_2->text().toLatin1(),
                                 QCryptographicHash::Md5).toHex();

    // 逐行读取数据
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");

        // 当读取到的用户名和要修改的用户名相同时，进行修改，否则直接写入
        if (list[0] == modInfo) {
            modInfo += "," + pw + "\n";
            write << modInfo;
        } else {
            write << str + "\n";
        }
    }


    // 用有修改信息的文件替换旧文件
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(path + "/" + ui->dbName->currentText() + "/userinfo.txt");
    QMessageBox::information(0,
                             "通知",
                             "修改成功",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);
}

/*
 * @Brief:  登陆时查看用户名和密码是否匹配
 * @Param:  dbname 数据库名
 * @Param:  username 用户名
 * @Param:  psd 密码
 * @Return: 匹配为真，否则为假
 */
bool resetpassword::checkLog(QString dbname, QString username, QString psd)
{
    // 初始化系统目录
    QString cpath = path + "/" + dbname + "/userinfo.txt";
    QString cname, cpas; // 用户名，密码
    QFile   file;
    QString pw =
        QCryptographicHash::hash(psd.toLatin1(), QCryptographicHash::Md5).toHex();

    // 当文件存在时继续操作
    if (file.exists(cpath)) {
        QFile   userFile(cpath);
        QString lineInf; // 读取一名用户的信息

        // 只读方式打开
        if (!userFile.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(0, "错误", "userinfo文件打开失败",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return false;
        }
        QTextStream readInf(&userFile); // 读取用户信息
        QStringList userList;

        // 逐行读取文件，
        while (!readInf.atEnd()) {
            lineInf = readInf.readLine();
            userList = lineInf.split(",");

            // 依次将用户名和密码进行匹配
            // 若匹配成功则返回真
            if ((username == userList[0]) && (pw == userList[1])) {
                userFile.close();
                QFile useFile(path + "/sys/curuse.txt");

                if (!useFile.open(QIODevice::WriteOnly)) {
                    QMessageBox::critical(0,
                                          "错误",
                                          "curuse文件打开失败",
                                          QMessageBox::Ok | QMessageBox::Default,
                                          QMessageBox::Cancel | QMessageBox::Escape,
                                          0);
                    return false;
                }
                QTextStream writeInf(&useFile);

                writeInf << username + "," + dbname;
                useFile.close();
                return true;
            }
        }
        userFile.close();
    }

    return false;
}

// 退出
void resetpassword::on_exitButton_clicked()
{
    this->close();
}

#include "login.h"
#include "qdir.h"
#include "qdebug.h"
#include <QCryptographicHash> // md5加密的库
#include "qmessagebox.h"

/**
   1. @ProjName:   DBMS
   4. @Brief:      实现用户登陆或注册，以及登陆或注册时相关的异常检验
 **/


login::login()
{
    // 初始化系统目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    path = dir->path() + "/data";
}

/*
 * @Brief:  检查用户名密码是否出错
 * @Param:  username 用户名
 * @Param:  psd      密码
 * @Return: 没错为真 ， 出错为假
 */
bool login::checkLog(QString dbname, QString username, QString psd)
{
    // 如果是管理员账号，则进行单独的一套逻辑判断
    qDebug() << dbname;
    qDebug() << username;
    qDebug() << psd;

    if (dbname == "管理员") {
        QString cpath = path + "/sys/admin.txt"; // 管理员信息文件路径
        QString cname, cpas;                     // 用户名，密码
        QFile   file;
        qDebug() << cpath;

        // 密码使用md5加密
        QString pw =
            QCryptographicHash::hash(psd.toLatin1(),
                                     QCryptographicHash::Md5).toHex();
        qDebug() << file.exists(cpath);

        if (file.exists(cpath)) {
            QFile   userFile(cpath);
            QString lineInf; // 读取一名用户的信息

            // 只读方式打开用户信息文件
            if (!userFile.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(0, "错误", "文件打开失败",
                                      QMessageBox::Ok | QMessageBox::Default,
                                      QMessageBox::Cancel | QMessageBox::Escape,
                                      0);
                return false;
            }
            QTextStream readInf(&userFile); // 读取用户信息
            QStringList userList;

            // 逐行读取文件
            // userList[0]是用户名；userList[1]是密码
            while (!readInf.atEnd()) {
                lineInf = readInf.readLine();
                userList = lineInf.split(",");

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

                    // 将当前用户信息写入文件
                    writeInf << username;
                    useFile.close();
                    return true;
                }
            }
            userFile.close();
        }
    }

    QString cpath = path + "/" + dbname + "/userinfo.txt"; // 信息文件路径
    QString cname, cpas;                                   // 用户名，密码
    QFile   file;
    qDebug()<<"dbname is "<<dbname<<endl;
    qDebug()<<"cpath is "<<cpath<<endl;
    qDebug()<<"测试"<<endl;
    // 密码使用md5加密
    QString pw =
        QCryptographicHash::hash(psd.toLatin1(), QCryptographicHash::Md5).toHex();

    if (file.exists(cpath)) {
        QFile   userFile(cpath);
        QString lineInf; // 读取一名用户的信息
        qDebug()<<lineInf<<endl;

        // 只读方式打开用户信息文件
        if (!userFile.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(0, "错误", "userinfo文件打开失败",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return false;
        }
        QTextStream readInf(&userFile); // 读取用户信息
        QStringList userList;

        // 逐行读取文件
        // userList[0]是用户名；userList[1]是密码
        while (!readInf.atEnd()) {
            lineInf = readInf.readLine();
            userList = lineInf.split(",");
            qDebug()<<userList[0]<<userList[1]<<endl;

            qDebug()<<username<<endl;
            qDebug()<<pw<<endl;
            if ((username == userList[0]) && (psd == userList[1])) {
                qDebug()<<"进入pw"<<endl;

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

                // 将当前用户信息写入文件
                writeInf << username + "," + dbname;
                useFile.close();
                return true;
            }
        }
        userFile.close();
    }

    return false;
}

/*
 * @Brief:  注册时判断异常,两种错误，1、用户名已存在或包含标点 2、两次密码不一致 3、密码中包含标点
 * @Param:  username 用户名
 * @Param:  psd      密码
 * @Return: 1 用户名已存在  2 用户名内容违规、密码内容违规 3 长度太短 4 两次密码不一致 0 通过验证
 */
int login::checkError(QString dbname, QString username, QString psd1,
                      QString psd2)
{
    qDebug()<<"dbname is "<<dbname<<endl;
    qDebug()<<"username is "<<username<<endl;
    qDebug()<<"psd1 is "<<psd1<<endl;
    qDebug()<<"psd2 is "<<psd2<<endl;
    if (psd1 != psd2) {
        return 4;
    }

//    if ((username.length() < 4) || (psd1.length() < 4)) {
//        return 3;
//    }

    if (username.contains(",") || username.contains("，") || psd1.contains(",") ||
        psd1.contains("，")) {
        return 2;
    }

    // 目标文件路径
    QString cpath = path + "/" + dbname + "/userinfo.txt";
    QFile   file;

    if (file.exists(cpath)) {
        qDebug() << "userinfo文件存在";
        QFile   userFile(cpath);
        QString lineInf; // 存储一名用户的信息

        if (!userFile.open(QIODevice::ReadOnly)) {
            qDebug() << "userinfo文件打开失败";
            return false;
        }
        QTextStream readInf(&userFile); // 读取用户信息
        QStringList userList;

        // 判断当前注册的用户名是否重复
        while (!readInf.atEnd()) {
            lineInf = readInf.readLine();
            userList = lineInf.split(",");

            if ((username == userList[0])) {
                userFile.close();
                return 1;
            }
        }
        userFile.close();
    }

    return 0;
}

/*
 * @Brief:  将用户名密码存储到文件
 * @Param:  username 用户名
 * @Param:  psd      密码
 * @Return: NULL
 */
void login::insert2File(QString dbname, QString username, QString psd)
{
    qDebug()<<"dbname is "<<dbname<<endl;
    qDebug()<<"username is "<<username<<endl;
    qDebug()<<"psd is "<<psd<<endl;
    // 将密码转换为md5格式
    QString pw =
        QCryptographicHash::hash(psd.toLatin1(), QCryptographicHash::Md5).toHex();

    // 以追加方式打开用户文件
    QFile file(path + "/" + dbname + "/userinfo.txt");

    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&file);

    // 写入新注册的用户名和密码
    out << username + "," + psd + "\n";
    file.close();
    qDebug()<<"userpassword is"<<psd<<endl;

    // 更新用户权限文件
    QFile privilege(path + "/" + dbname + "/userprivilege.txt");

    privilege.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream outp(&privilege);

    outp << username + ",1,1,1,1,1\n";
    privilege.close();
}

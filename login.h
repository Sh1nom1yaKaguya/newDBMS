#ifndef LOGIN_H
#define LOGIN_H
#include "qstring.h"
typedef struct user {
    QString username;  // 用户名
    QString psd;       // 密码
    QString privilege; // 管理权限
} user;

class login {
public:

    login();

    // 登录时，判断用户名密码是否正确
    bool checkLog(QString,
                  QString,
                  QString);

    // 注册时判断用户名和密码是否重复或错误
    int checkError(QString,
                   QString,
                   QString,
                   QString);

    // 注册好后插入数据信息
    void insert2File(QString,
                     QString,
                     QString
                     );

private:

    QString path;
};

#endif // LOGIN_H

#ifndef MANAGEDATABYSQL_H
#define MANAGEDATABYSQL_H
#include "qstringlist.h"

class ManageDataBySql {
public:

    ManageDataBySql();
    void insertData(QStringList);
    void deleteData(QStringList);
    void updateData(QStringList);
    void writeintoLOG(int i,QStringList keywordList);//写入日志
private:

    void initDir();
    int countfield(QString);
    bool hassame(int,QString);

    QString dirPath;
    QString dbName;
    QString userName;
    QString tablePath;
    int updateColId;
};

#endif // MANAGEDATABYSQL_H

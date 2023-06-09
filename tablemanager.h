#ifndef CREATETABLE_H
#define CREATETABLE_H
#include "qstring.h"
#include "qdebug.h"
#include "qdir.h"
class TableManager {
public:

    TableManager();
    TableManager(QString,
                 QString);
    bool isTableExist(QString);
    void tableCreator(QString);
    void tableModifier(QString,
                       int);
    bool tableDelete(QString);

private:

    QString dirPath;
    QString tablePath;
    QString username;
};

#endif // CREATETABLE_H

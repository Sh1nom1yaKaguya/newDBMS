#ifndef ANALYSISSQL_H
#define ANALYSISSQL_H
#include "qstringlist.h"

#define SQLTYPE 5
class AnalysisSQL {
public:

    AnalysisSQL();
    QStringList resolveSql(QString);

private:

    QStringList regList;
};

#endif // ANALYSISSQL_H

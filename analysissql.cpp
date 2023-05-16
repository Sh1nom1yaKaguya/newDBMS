#include "analysissql.h"
#include "qdebug.h"

/**
   1. @ProjName:   DBMS
   4. @Brief:      sql语句解析函数
 **/

/*
 *  可能用到的sql语句如下:
 * 1.数据库相关
 * 创建数据库：create database DBname;
 * 删除数据库：drop database DBname;
 * 2.表管理
 * 创建表：create table tablename;
 * 删除表：drop table tablename;
 * 3.字段管理
 * 增加字段：alter table tablename add colname number;
 * 删除字段：alter table tablename drop column colname;
 * 修改字段：alter table tablename modify colname not null;
 * 4.数据管理
 * 插入：insert into tablename values(**,**,*);
 * 删除：delete from users where userid=001;
 * 更新：update tablename set username=111 where id=2;
 * 5.查询
 * 查询全部：select * from tablename;
 * 查询指定字段所有记录：select (fieldname1,fieldname2) from tablename;
 * ****注意：提取括号里的所有内容，然后展示的时候再用正则进一步解析
 * 查询指定字段和where条件（单一条件）:select (sname,sno,sex) from tablename where id=1009;
 * 6.索引
 * create index idxname on tablename(fieldname);
 * drop index idxname on tablename;
 * 7.导入sql脚本
 * import script E:/database.sql;
 * 8.权限赋予和回收
 * （任意数量的权限和用户名）
 * grant create,drop,update,insert,delete on tablename to username1,username2;
 * revoke create,drop,update,insert,delete on tablename from username;
 */

/*
 * @Brief:  初始化构造器，加入所需要的正则表达式
 * @Return: null
 */
AnalysisSQL::AnalysisSQL()
{
    // 保存所有可能用到的正则表达式
    // 数据库相关
    regList.push_back(
        "(?:create|CREATE)(?:\\s*)(?:database|DATABASE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
    regList.push_back(
        "(?:drop|DROP)(?:\\s*)(?:database|DATABASE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");

    // 表管理
    regList.push_back(
        "(?:create|CREATE)(?:\\s*)(?:table|TABLE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
    regList.push_back(
        "(?:drop|DROP)(?:\\s*)(?:table|TABLE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");

    // 字段管理
    regList.push_back(
        "(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:add|ADD)\\s*(\\w+)\\s*(number|char|varchar|date|NUMBER|CHAR|VARCHAR|DATE)\\s*(primary key|PRIMARY KEY)?\\s*(not null|NOT NULL)?;");
    regList.push_back(
        "(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:drop|DROP)\\s*column\\s*(\\w+);");
    regList.push_back(
        "(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:modify|MODIFY)\\s*(\\w+)\\s*(primary key|PRIMARY KEY)?\\s*(not null|NOT NULL)?;");

    // 数据管理
    regList.push_back(
        "((?:insert into )|(?:INSERT INTO ))(\\w+)(?: values)(?:\\s*)\\((.+)\\)(?:\\s*);");
    regList.push_back(
        "(?:delete|DELETE)\\s*(?:FROM|from)\\s*(\\w+)\\s*(?:WHERE|where)\\s*(\\w+)\\s*(<|=|>)\\s*(\\w+);");
    regList.push_back(
        "(?:update|UPDATE)(?:\\s*)(\\w+)(?:\\s*)(?:set|SET)(?:\\s*)(\\w+)(?:\\s*)=(\\w+)(?:\\s*)where(?:\\s*)(\\w+)(?:\\s*)(<|=|>)(\\w+)(?:\\s*);");

    // 数据查询
    regList.push_back(
        "(?:select|SELECT)(?:\\s*)([\\*])(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*);");
    regList.push_back(
        "(?:select|SELECT)(?:\\s*)\\((.+)\\)(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*);");
    regList.push_back(
        "(?:select|SELECT)(?:\\s+)\\((.+)\\)(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*)where(?:\\s*)(\\w+)(?:\\s*)(<|=|>)(\\w+)(?:\\s*);");

    // 创建索引
    regList.push_back(
        "(?:create|CREATE)(?:\\s*)(?:index|INDEX)(?:\\s*)(\\w+)(?:\\s*)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)\\((.+)\\);");

    // 删除索引
    regList.push_back(
        "(?:drop|DROP)(?:\\s*)(?:index|INDEX)(?:\\s*)(\\w+)(?:\\s*)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*);");


    // 导入sql脚本
    regList.push_back(
        "(?:import|IMPORT)(?:\\s*)(?:script|SCRIPT)(?:\\s*) ([a-zA-Z]:(?:.(?:[a-zA-Z0-9_]+.[a-zA-Z0-9_]{1,16}))+);");

    // 权限赋予和收回
    regList.push_back(
        "(?:grant|Grant)(?:\\s)+(.+)(?:\\s+)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)(?:to|TO)(?:\\s)+(.+)(?:\\s*);");

    regList.push_back(
        "(?:revoke|REVOKE)(?:\\s)+(.+)(?:\\s+)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)(?:from|FROM)(?:\\s)+(.+)(?:\\s*);");
}

/*
 * @Brief:  通过正则表达式分析控制台发送的sql语句，提取关键信息
 * @Param:  sql cmd传来的sql语句
 * @Return: 含有所需关键子的列表
 */
QStringList AnalysisSQL::resolveSql(QString sql)
{
    qDebug() << "SQL语句为" + sql;

    // 通过分析sql语句得到的有用关键字的列表
    QStringList keyWordList;

    // 依次与正则表达式进行匹配
    for (int i = 0; i < regList.size(); i++) {
        QRegExp re(regList[i]);
        int     pos = re.indexIn(sql);

        // 当返回的下角标不为-1时，则匹配成功
        if (pos != -1) {
            // 获取捕获得到的关键字
            keyWordList = re.capturedTexts();

            // 首位是该操作的类型
            keyWordList[0] = QString::number(i);
            qDebug() << "匹配成功：";
            qDebug() << keyWordList;
            return keyWordList;
        }
    }
    qDebug() << "匹配失败";
    return keyWordList;
}

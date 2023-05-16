#ifndef INDEXMANAGER_H
#define INDEXMANAGER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "qstring.h"
#define M       3 // 设定3阶B-Tree
#define QUANEUE_LEN 100
#include <iostream>
using namespace std;
#include <string.h>

//

#define MALLOC_NODE(p, type) type *p = (type *)malloc(sizeof(type)); memset(p,      \
                                                                            0,      \
                                                                            sizeof( \
                                                                                type))
#define FREE_NODE(p) free(p)

#define FSEEK_END_WRITE(fp, pos, buf, size) fseek(fp, 0, SEEK_END); \
    pos = ftell(fp); fwrite(buf, size, 1, fp)
#define FSEEK_HED_WRITE(fp, pos, buf, size) fseek(fp, 0, SEEK_SET); \
    pos = ftell(fp); fwrite(buf, size, 1, fp)
#define FSEEK_FIXED_READ(fp, pos, buf, size) fseek(fp, pos, SEEK_SET); fread(buf,  \
                                                                             size, \
                                                                             1,    \
                                                                             fp)
#define FSEEK_FIXED_WRITE(fp, pos, buf, size) fseek(fp, pos, SEEK_SET); fwrite( \
        buf,                                                                    \
        size,                                                                   \
        1,                                                                      \
        fp)
#define OPEN_FILE(file_name, mode) fopen(file_name, mode)
#define OPEN_FILE_READ(file_name, mode, buf,                              \
                       size) fp = OPEN_FILE(file_name, mode); fread(buf,  \
                                                                    size, \
                                                                    1,    \
                                                                    fp)
#define OPEN_FILE_WRITE(file_name, mode, buf,                               \
                        size) fp = OPEN_FILE(file_name, mode); fwrite(buf,  \
                                                                      size, \
                                                                      1,    \
                                                                      fp)
#define CLOSE_FILE(fp) fclose(fp)
typedef unsigned int       uint;
typedef unsigned short int sint;
typedef FILE              *file;
typedef unsigned long long ull;

/* 数据结构体 */
typedef struct {
    // string  values;
    // string  values02;
    sint len; // 数据长度
    uint pos; // 数据位置
} _data;

/* 文件头结构体 */
typedef struct {
    uint head; // 头结点位置
    uint node; // 节点数目
} FileHead;

/* 索引节点结构体 */
typedef struct {
    sint  keyNum;      // 关键字数量
    uint  parent;      // 父节点
    ull   key[M + 1];  // 关键字也就是索引值
    uint  ptr[M + 1];  // 儿子节点位置
    _data data[M + 1]; // 数据信息
} BTNode;

// 存储查找结果
typedef struct {
    sint leng;
    uint pt;  /* 指向找到的结点位置 */
    sint i;   /* 1..m，在结点中的关键字序号 */
    sint tag; /* 1:查找成功，0:查找失败 */

    // string values;//结点值
    // string values02;
} Result;

typedef struct {
    char NAME[128];
    bool unique;
    bool asc;
    int  field_num;
    char fields[128][2];
    char record_file[256];
    char index_file[256];
} index_desc;
class Indexmanager {
public:

    /* 查询语句使用时
       1.  Indexmanager* idmg=new Indexmanager(QString tablename)
       2.  idmg.checkindex(QString finame1,QString finame2)
       查看含有该字段组的索引文件名，如果没有该索引，则返回NULL
       3.  idmg.SelectBtree(QString index_name,QString keyvalues)
       index_name为2中返回的索引名，keyvalues为关键字对应的值
       4.  imdg.searesult
       查找结果存在searesult中
       形式为"values1,values2"，若未找到相应值，则searesult值为"未查到相应结果"*/
    Indexmanager();
    Indexmanager(QString tablename);
    void createFalseIndex(QStringList keyword);
    int  Search(BTNode *NodeBuf,
                ull     key); // 根据键值查找
    void SearchBTree(uint    node_pos,
                     ull     key,
                     Result *r);
    void upFileHead(uint new_head_pos); // 更新头节点结构信息
    void newRoot(uint  head_pos,
                 ull   key,
                 _data data,
                 uint  ap);  // 创建B树新根
    uint   split(BTNode *NodeBuf,
                 uint    node_pos,
                 sint    s); // 分裂
    BTNode Insert(uint  node_pos,
                  sint  i,
                  ull   key,
                  uint  ap,
                  _data data);
    void InsertBTree(uint  head_pos,
                     ull   key,
                     uint  node_pos,
                     sint  i,
                     _data data);
    void    insertData(char *con,
                       ull   key);           // 插入数据
    ull     hashkey(string s);
    void    SelectBtree(QString index_name,
                        QString keyvalues);  // 查找值
    void    deleteIndex(QString index_name); // 删除索引文件
    QString checkindex(QString finame1,
                       QString finame2);     // 查看含有该字段组的索引文件名
    QString searesult;                       // 如果没有该索引，则返回NULL

private:

    // index_desc indexinformation;
    QString dirPath;
    QString indexPath;
    QString datafile;
    QString indexfile; //
    QString tablefile;
    QString recordfile;
    QString indexrecordfile;
    file fp;

    // 查找结果字符串，形式为"values1,values2"
    // 若未找到相应值，则searesult值为"未查到相应结果"
    ull mod = 1e9 + 7;
    ull h[100010];
    ull prime = 233317;
};

#endif // INDEXMANAGER_H

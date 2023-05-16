#include "indexmanager.h"
#include"qdir.h"
#include"string"
#include<string>
#include"qdebug.h"
#include<algorithm>
#include<stdio.h>
#include"qmessagebox.h"
/**
* 1.@projectName: DBMS
* 4.brief         索引管理系统
*                 包含三个文件 .ix文件为二进制索引数据文件
*                            .tid文件为二进制索引头文件
*
*
* 5.Function      (1)
*/

/* 查询语句使用时
1.  Indexmanager* idmg=new Indexmanager(QString tablename)
2.  idmg.checkindex(QString finame1,QString finame2)
 查看含有该字段组的索引文件名，如果没有该索引，则返回NULL
3.  idmg.SelectBtree(QString index_name,QString keyvalues)
 index_name为2中返回的索引名，keyvalues为关键字对应的值
4.  imdg.searesult
 查找结果存在searesult中
 形式为"values1,values2"，若未找到相应值，则searesult值为"未查到相应结果"*/

Indexmanager::Indexmanager()
{

}

Indexmanager::Indexmanager(QString tablename){

    QDir *dir = new QDir(QDir::currentPath());

    searesult="未查到相应结果";
    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "initDir文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    qDebug() << "用户信息" + str;

    list = str.split(",");

    QString userName = list[0];
    QString dbName = list[1];
    dirPath = dir->path() + "/data/" + list[1];
    file.close();


    tablefile=dirPath+"/table/"+tablename+"/"+tablename+".tdf";//字段文件
    recordfile=dirPath+"/table/"+tablename+"/"+tablename+".trd";//该表数据存储文件
    indexrecordfile=dirPath+"/table/"+tablename+"/"+tablename+".tid";/*文件格式为
                                                                       字段1名，字段2名，对应的索引文件名
                                                                       */
    dirPath=dirPath+"/table/"+tablename+"/";

}

int Indexmanager:: Search( BTNode* NodeBuf, ull key )
{
    sint i = 1;
    while ( i <= NodeBuf->keyNum && key > NodeBuf->key[i] )
    {
        i++;
    }
    return i;
}

void Indexmanager:: SearchBTree( uint node_pos, ull key, Result* r )
{
    sint    i       = 0;
    sint    found       = 0;
    uint    parent_pos  = 0;
    _data temp;
    MALLOC_NODE( NodeBuf, BTNode );

    //
    while ( node_pos != 0 && found == 0 )
    {
        FSEEK_FIXED_READ( fp, node_pos, NodeBuf, sizeof(BTNode) );
        i = Search( NodeBuf, key );
        if ( i <= NodeBuf->keyNum && NodeBuf->key[i] == key )
        {
            found = 1;
        } else {
            parent_pos  = node_pos;

           // templeng=NodeBuf->data->len;
            node_pos    = NodeBuf->ptr[i - 1];  /* 指针下移 */
        }
    }
    if ( 1 == found )                                       /* 查找成功，返回key的位置node_pos和i */
    {
        //输出结点值
   r->pt   = node_pos;
        r->i    = i;
        r->tag  = 1;
       // Buffer
      temp=NodeBuf->data[i];
       qDebug()<<temp.pos;
       // char* aaa = nullptr;

        MALLOC_NODE(aaa,char);
        qDebug()<<temp.len;
       file mm=OPEN_FILE( datafile.toLatin1().data(), "rb" );
        FSEEK_FIXED_READ(mm,temp.pos, aaa,temp.len );

        searesult=QString::fromStdString(aaa);

         qDebug()<<searesult;


     //FREE_NODE(aaa);
        CLOSE_FILE(mm);
     FREE_NODE( NodeBuf );//关闭缓存区

     return;
    } else {                                                 /* 查找失败，返回key的插入位置parent_pos和i */
        r->pt   = parent_pos;
        r->i    = i;
        r->tag  = 0;
  //qDebug()<<"未找到相应值";
    }

   // qDebug()<<"未找到相应值";
    FREE_NODE( NodeBuf );//关闭缓存区
}



 void Indexmanager:: upFileHead( uint new_head_pos )
{
    MALLOC_NODE( fileHeadBuf, FileHead );
    FSEEK_FIXED_READ( fp, 0, fileHeadBuf, sizeof(FileHead) );
    if ( new_head_pos > 0 )
    {
        fileHeadBuf->head = new_head_pos;
    }
    fileHeadBuf->node++;
    FSEEK_FIXED_WRITE( fp, 0, fileHeadBuf, sizeof(FileHead) );
    FREE_NODE( fileHeadBuf );
}



void Indexmanager:: newRoot( uint head_pos, ull key, _data data, uint ap )
 {
     uint pos;
     MALLOC_NODE( rootNodeBuf, BTNode );

     rootNodeBuf->keyNum = 1;
     rootNodeBuf->ptr[0] = head_pos;
     rootNodeBuf->ptr[1] = ap;
     rootNodeBuf->key[1] = key;
     rootNodeBuf->data[1]    = data;

     FSEEK_END_WRITE( fp, pos, rootNodeBuf, sizeof(BTNode) );

     /* 读取原根结点更新parent位置 */
     FSEEK_FIXED_READ( fp, head_pos, rootNodeBuf, sizeof(BTNode) );
     rootNodeBuf->parent = pos;
     FSEEK_FIXED_WRITE( fp, head_pos, rootNodeBuf, sizeof(BTNode) );

     /* 读取分裂结点更新parent位置 */
     FSEEK_FIXED_READ( fp, ap, rootNodeBuf, sizeof(BTNode) );
     rootNodeBuf->parent = pos;
     FSEEK_FIXED_WRITE( fp, ap, rootNodeBuf, sizeof(BTNode) );

     /* 更新文件头 */
     upFileHead( pos );

     FREE_NODE( rootNodeBuf );
 }




uint Indexmanager:: split( BTNode* NodeBuf, uint node_pos, sint s )
{
    sint    i, j;
    sint    n = NodeBuf->keyNum;
    uint    ap;
    MALLOC_NODE( apNodeBuf, BTNode );
    MALLOC_NODE( apNodeBufChild, BTNode );

    apNodeBuf->ptr[0] = NodeBuf->ptr[s];
    for ( i = s + 1, j = 1; i <= n; i++, j++ )
    {
        apNodeBuf->key[j]   = NodeBuf->key[i];
        apNodeBuf->ptr[j]   = NodeBuf->ptr[i];
        apNodeBuf->data[j]  = NodeBuf->data[i];
    }
    apNodeBuf->keyNum   = n - s;
    apNodeBuf->parent   = NodeBuf->parent;
    FSEEK_END_WRITE( fp, ap, apNodeBuf, sizeof(BTNode) );

    /* 更新文件头结点数量 */
    upFileHead( 0 );

    for ( i = 0; i <= n - s; i++ )
    {
        /* 修改新结点的子结点的parent域 */
        if ( apNodeBuf->ptr[i] != 0 )
        {
            FSEEK_FIXED_READ( fp, apNodeBuf->ptr[i], apNodeBufChild, sizeof(BTNode) );
            apNodeBufChild->parent = ap;
            FSEEK_FIXED_WRITE( fp, apNodeBuf->ptr[i], apNodeBufChild, sizeof(BTNode) );
        }
    }

    FSEEK_FIXED_READ( fp, node_pos, NodeBuf, sizeof(BTNode) );
    NodeBuf->keyNum = s - 1; /* 修改NodeBuf结点的关键字数量 */
    FSEEK_FIXED_WRITE( fp, node_pos, NodeBuf, sizeof(BTNode) );
    FREE_NODE( apNodeBuf );
    FREE_NODE( apNodeBufChild );
    return(ap);
}



BTNode Indexmanager:: Insert( uint node_pos, sint i, ull key, uint ap, _data data )
{
   BTNode  buf;
   BTNode  * NodeBuf = &buf;
   /* 读取节点 */
   FSEEK_FIXED_READ( fp, node_pos, NodeBuf, sizeof(BTNode) );

   sint j;
   for ( j = NodeBuf->keyNum; j >= i; j-- )
   {
       /* 后移 */
       NodeBuf->key[j + 1] = NodeBuf->key[j];
       NodeBuf->ptr[j + 1] = NodeBuf->ptr[j];
       NodeBuf->data[j + 1]    = NodeBuf->data[j];
   }
   NodeBuf->key[i]     = key;
   NodeBuf->ptr[i]     = ap;
   NodeBuf->data[i]    = data;

   NodeBuf->keyNum++;
   FSEEK_FIXED_WRITE( fp, node_pos, NodeBuf, sizeof(BTNode) );
   return(*NodeBuf);
}

void Indexmanager:: InsertBTree( uint head_pos, ull key, uint node_pos, sint i, _data data )
{
   sint    s       = 0;
   sint    finished    = 0;
   sint    needNewRoot = 0;
   uint    ap      = 0;
   BTNode  NodeBuf;
   Result  res;
   while ( 0 == needNewRoot && 0 == finished )
   {
       NodeBuf = Insert( node_pos, i, key, ap, data );
       if ( NodeBuf.keyNum < M )
       {
           finished = 1;
       } else {
           /* 得到中间结点位置 */
           s = (M + 1) / 2;
           /* 分裂结点 */
           ap  = split( &NodeBuf, node_pos, s );
           key = NodeBuf.key[s];
           data    = NodeBuf.data[s];
           /* 在双亲位置插入关键字 */
           if ( NodeBuf.parent != 0 )
           {
               /* 寻找插入的位置 */
               node_pos = NodeBuf.parent;
               FSEEK_FIXED_READ( fp, node_pos, &NodeBuf, sizeof(BTNode) );
               i = Search( &NodeBuf, key );

           } else {
               needNewRoot = 1;
           }
       }
   }
   if ( 1 == needNewRoot )
   {
       newRoot( head_pos, key, data, ap );
   }
}



void Indexmanager:: createFalseIndex(QStringList keyword)
{
    sint        node_pos;
    FileHead    head;
    BTNode      node;
    QString index_name=keyword[1];
QString field_name=keyword[3];
     datafile=dirPath+index_name+".ix";
    //file datafile(dirPath.toStdString);
     indexfile=dirPath+index_name+".tid";
     //fieldfile=dirPath+index_name+".if";


     /* 创建索引文件 */
    if ( OPEN_FILE(indexfile.toLatin1().data(), "rb" ) == NULL )
    {
        fp = OPEN_FILE( indexfile.toLatin1().data(), "wb+" );

        /* 初始化Head */
        FileHead head = { 0, 1 };
        FSEEK_END_WRITE( fp, node_pos, (char *) &head, sizeof(head) );

        /* 初始化Node */
        BTNode node = { 0 };
        FSEEK_END_WRITE( fp, node_pos, (char *) &node, sizeof(node) );

        /* 更新head指向第一个node */
        head.head = node_pos;
        FSEEK_HED_WRITE( fp, node_pos, (char *) &head, sizeof(head) );
        CLOSE_FILE( fp );
    }

    /* 创建数据文件 */
    if ( OPEN_FILE(datafile.toLatin1().data(), "rb" ) == NULL )
    {
        fp = OPEN_FILE( datafile.toLatin1().data(), "wb" );
        //找到对应字段的列号

        int column=0;
        int column02=0;

        QStringList fieldlist=field_name.split(",");
        //打开表文件
        QFile tdf(tablefile);

        if(!tdf.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件
        {
        qDebug() << "Can't open the file!";
        return;
        }
        //打开该表索引记录总文件
        QFile ic(indexrecordfile);
        if (!ic.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            qDebug()<<"Can't open the file!";
            return;}
        QTextStream streamFileic(&ic);

        QTextStream check(&tdf);  //用文件构造流
        QString  fieldrecord = check.readLine();//读取一行放到字符串里
        int i=0;
        while(!fieldrecord.isNull())//字符串有内容
        {
            QStringList listtemp=fieldrecord.split(",");


            if(listtemp[0]==fieldlist[0]){
                column=i;
                if(listtemp[2]!="主键")
                  { QMessageBox::critical(0, "critical message", "索引创建错误，键值不唯一",
                                          QMessageBox::Ok | QMessageBox::Default,
                                          QMessageBox::Cancel | QMessageBox::Escape, 0);
                    qDebug()<<"键值不唯一";
                    deleteIndex(index_name);
                return ;}
               qDebug()<<listtemp[2];
            }
            if(listtemp[0]==fieldlist[1])
              {  column02=i;
           // qDebug()<<listtemp[0];
            }
            i++;
            fieldrecord=check.readLine();
        }



        //容错判断
        if(column02==0){
            QMessageBox::critical(0, "critical message", "索引创建错误，此表不存在相应字段",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
    qDebug()<<"索引创建错误，此表不存在相应字段";
      deleteIndex(index_name);
            return ;
        }


        streamFileic<<fieldlist[0]<<","<<fieldlist[1]<<","<<index_name<<endl;
        ic.close();
        tdf.close();

       // qDebug()<<column02;
       //从数据文件中取出对应数值，建立B树
        QFile file(recordfile);
        //qDebug()<<recordfile;
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件
        {
        qDebug() << "Can't open the file!";
        return;
        }
        QTextStream in(&file);  //用文件构造流
        QString  line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
        QStringList list1 = line.split(",");
        //string data2=line.toStdString();
        string data1=list1[column].toStdString()+
                ","+list1[column02].toStdString();
       //  data1=data1+","+line.toStdString();
       // qDebug()<<QString::fromStdString(data1);
        ull key=hashkey(list1[column].toStdString());//根据关键值的求哈希值
//       qDebug()<<"哈希值";
        qDebug()<<key;
        insertData((char*)data1.data(),key);
        line=in.readLine();//循环读取下行
        }
        file.close();
        CLOSE_FILE( fp );
    }
    QMessageBox::information(0, "information message", "创建成功",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);
   //SelectBtree("nn","34");
  // SelectBtree("hhh","WWW");
}



void Indexmanager:: insertData( char* con, ull key ){
    _data data;
        /* 写入数据 */
       data.len = sizeof ( con );
  // qDebug()<<data.len;
        fp = OPEN_FILE( datafile.toLatin1().data(), "ab" );
      FSEEK_END_WRITE( fp, data.pos, con, data.len );
      CLOSE_FILE( fp );
        /* 写入索引 */
        MALLOC_NODE( HeadBuf, FileHead );
        Result res;
        /* 读取索引头 */
        OPEN_FILE_READ( indexfile.toLatin1().data(), "rb+", HeadBuf, sizeof(FileHead) );

        /* 查找树 */
        SearchBTree( HeadBuf->head, key, &res );
        /* 插入树 */
        InsertBTree( HeadBuf->head, key, res.pt, res.i, data );

        FREE_NODE( HeadBuf );

        CLOSE_FILE( fp );


}



//生成字符串对应的哈希值（即B树中的key值）
ull Indexmanager::hashkey(string s){

   int length =s.size();
        ull temp=((ull)s[0])%mod;
        for(int i=1;i<length;i++)
        {
            temp=(temp*prime+(ull)s[i])%mod;
        }
        return temp;
}

//查询函数利用索引
void Indexmanager::SelectBtree(QString index_name,QString keyvalues){
    Result res;

    datafile=dirPath+index_name+".ix";
   //file datafile(dirPath.toStdString);
    indexfile=dirPath+index_name+".tid";
     MALLOC_NODE( HeadBuf, FileHead );
    /* 读取索引头 */
       OPEN_FILE_READ(indexfile.toLatin1().data() , "rb+", HeadBuf, sizeof(FileHead) );

       ull key =hashkey(keyvalues.toStdString());//根据关键字值利用索引查找
       qDebug()<<key;
       /* 查找树 */
       SearchBTree( HeadBuf->head, key, &res );
      // qDebug()<<res.pt;
       FREE_NODE( HeadBuf );

      // qDebug()<<QString::fromStdString(res.values);
}



//删除索引文件
void Indexmanager::deleteIndex(QString index_name){
    datafile=dirPath+index_name+".ix";
   //file datafile(dirPath.toStdString);
    indexfile=dirPath+index_name+".tid";



    // 是否传入了空的路径||路径是否存在
    if (datafile.isEmpty() || !QDir().exists(datafile)) {
       QMessageBox::critical(0, "critical message", "此索引不存在",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);
qDebug()<<"此索引不存在";
        return ;
    }

    QFileInfo FileInfo(datafile);
QFileInfo FileIn(indexfile);
    if (FileInfo.isFile())     // 如果是文件
       { QFile::remove(datafile);
     QFile::remove(indexfile);}

    QMessageBox::information(0, "information message", "删除成功",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);

}

QString Indexmanager::checkindex(QString finame1, QString finame2){

    //QString resultname;
    QFile ic(indexrecordfile);

    if(!ic.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件
    {
    qDebug() << "Can't open the file!";
    return NULL;
    }
    QTextStream check(&ic);  //用文件构造流
    QString  fieldrecord = check.readLine();//读取一行放到字符串里
   //int mark=0;
    while(!fieldrecord.isNull())//字符串有内容
    {
        QStringList listtemp=fieldrecord.split(",");

        if(listtemp[0]==finame1&&listtemp[1]==finame2)
        {  return listtemp[2]; }

        fieldrecord=check.readLine();
    }
    ic.close();
    return NULL;

}

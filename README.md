# DBMS

#### 介绍
大二下实训 编写DBMS
首次下载不要去管mainwindow里的东西，那是我用来debug用的，截至5月1日，目前项目中可使用的类有login、tablemanager和fieldmanager。

#### 使用说明

1.  所有涉及的读写文件在data目录下
2.  sys文件夹存储系统文件，里面的alluser文件存储用户名和密码，用英文逗号隔开，后续的权限可在每行的后面用1.2.3这样的数字来标明等级
    curuse文件只有一行数据 存储内容为 当前使用的用户名，当前使用的数据库，当前使用的表  依旧用英文逗号隔开。每次项目结束时将内容清空。
3.  data目录下的其他文件为用户文件 目录结构为 用户/数据库/表/各类表文件    注：表文件的后缀和里面的字段结构 所代表的意思详见老师发的文件



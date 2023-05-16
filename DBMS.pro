QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analysissql.cpp \
    createdatabase.cpp \
    creattable.cpp \
    dataoperation.cpp \
    dbmanager.cpp \
    deletedatabase.cpp \
    deletetable.cpp \
    fieldmanager.cpp \
    indexmanager.cpp \
    landing.cpp \
    logdialog.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    managedatabysql.cpp \
    managefieldbysql.cpp \
    managetablebysql.cpp \
    privilegemanager.cpp \
    registerw.cpp \
    resetpassword.cpp \
    selectdatabase.cpp \
    tablemanageload.cpp \
    tablemanager.cpp

HEADERS += \
    analysissql.h \
    createdatabase.h \
    creattable.h \
    dataoperation.h \
    dbmanager.h \
    deletedatabase.h \
    deletetable.h \
    fieldmanager.h \
    indexmanager.h \
    landing.h \
    logdialog.h \
    login.h \
    mainwindow.h \
    managedatabysql.h \
    managefieldbysql.h \
    managetablebysql.h \
    privilegemanager.h \
    registerw.h \
    resetpassword.h \
    selectdatabase.h \
    tablemanageload.h \
    tablemanager.h

FORMS += \
    createdatabase.ui \
    creattable.ui \
    dataoperation.ui \
    deletedatabase.ui \
    deletetable.ui \
    fieldmanager.ui \
    landing.ui \
    logdialog.ui \
    mainwindow.ui \
    privilegemanager.ui \
    registerw.ui \
    resetpassword.ui \
    selectdatabase.ui \
    tablemanageload.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc

DISTFILES += \
    .gitignore \
    DBMS.pro.user \
    README.md

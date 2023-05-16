/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionnew;
    QAction *actionselect;
    QAction *actionlog;
    QAction *actionexit;
    QAction *actionrland;
    QAction *actioncpassword;
    QAction *actionpower;
    QAction *actionintroduce;
    QAction *actiondelete;
    QWidget *centralwidget;
    QLabel *label;
    QTreeView *treeView;
    QTableWidget *tableWidget;
    QPushButton *run;
    QPushButton *tablemanage;
    QPushButton *datamanage;
    QPushButton *fieldmanage;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *sqllineEdit;
    QLCDNumber *lcdNumber;
    QPushButton *commit;
    QPushButton *rollback;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1582, 976);
        MainWindow->setStyleSheet(QString::fromUtf8("*{\n"
"background:rgb(255, 255, 255);\n"
"font-size:px;\n"
"	font: 16pt \"\346\245\267\344\275\223\";\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"\n"
"QFrame{\n"
"border-style:outset;\n"
"border-radius:15px;\n"
"border:sold 10px rgba(0,0,0);\n"
"background-color: rgba(255, 255, 255,0.5);\n"
"}\n"
"QLineEdit{\n"
"color:#8d98a1;\n"
"background-color:#405361;\n"
"font-size:24px;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton{\n"
"background:#ced1d8;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgb(224,0,0);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QCheckBox{\n"
"background:rgba(85,170,255,0);\n"
"color:white;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QLabel{\n"
"background:rgba(85,170,255,0);\n"
"color:white;\n"
"font-style:MingLiU-ExtB;\n"
"font-size:14px;\n"
"}\n"
""));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QString::fromUtf8("actionnew"));
        actionselect = new QAction(MainWindow);
        actionselect->setObjectName(QString::fromUtf8("actionselect"));
        actionlog = new QAction(MainWindow);
        actionlog->setObjectName(QString::fromUtf8("actionlog"));
        actionexit = new QAction(MainWindow);
        actionexit->setObjectName(QString::fromUtf8("actionexit"));
        actionrland = new QAction(MainWindow);
        actionrland->setObjectName(QString::fromUtf8("actionrland"));
        actioncpassword = new QAction(MainWindow);
        actioncpassword->setObjectName(QString::fromUtf8("actioncpassword"));
        actionpower = new QAction(MainWindow);
        actionpower->setObjectName(QString::fromUtf8("actionpower"));
        actionintroduce = new QAction(MainWindow);
        actionintroduce->setObjectName(QString::fromUtf8("actionintroduce"));
        actiondelete = new QAction(MainWindow);
        actiondelete->setObjectName(QString::fromUtf8("actiondelete"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-10, 0, 1611, 991));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 233, 255);"));
        label->setScaledContents(true);
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 120, 271, 721));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(320, 570, 601, 271));
        run = new QPushButton(centralwidget);
        run->setObjectName(QString::fromUtf8("run"));
        run->setGeometry(QRect(980, 300, 221, 41));
        tablemanage = new QPushButton(centralwidget);
        tablemanage->setObjectName(QString::fromUtf8("tablemanage"));
        tablemanage->setGeometry(QRect(340, 390, 221, 41));
        datamanage = new QPushButton(centralwidget);
        datamanage->setObjectName(QString::fromUtf8("datamanage"));
        datamanage->setGeometry(QRect(680, 390, 221, 41));
        fieldmanage = new QPushButton(centralwidget);
        fieldmanage->setObjectName(QString::fromUtf8("fieldmanage"));
        fieldmanage->setGeometry(QRect(980, 390, 221, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(990, 0, 181, 181));
        label_2->setStyleSheet(QString::fromUtf8("font: 22pt \"\346\245\267\344\275\223\";\n"
"color: rgb(0, 0, 0);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(970, 500, 171, 261));
        label_4->setStyleSheet(QString::fromUtf8("font: 22pt \"\346\245\267\344\275\223\";\n"
"color: rgb(0, 0, 0);"));
        sqllineEdit = new QLineEdit(centralwidget);
        sqllineEdit->setObjectName(QString::fromUtf8("sqllineEdit"));
        sqllineEdit->setGeometry(QRect(310, 170, 921, 91));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(710, 40, 211, 91));
        lcdNumber->setStyleSheet(QString::fromUtf8("color:rgb(78,104,255)"));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setDigitCount(8);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        commit = new QPushButton(centralwidget);
        commit->setObjectName(QString::fromUtf8("commit"));
        commit->setGeometry(QRect(340, 299, 220, 41));
        rollback = new QPushButton(centralwidget);
        rollback->setObjectName(QString::fromUtf8("rollback"));
        rollback->setGeometry(QRect(680, 299, 220, 41));
        verticalWidget = new QWidget(centralwidget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setGeometry(QRect(120, -20, 1201, 831));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(320, 470, 491, 71));
        textBrowser_2 = new QTextBrowser(centralwidget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(470, 30, 391, 121));
        textBrowser_2->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 219, 255);"));
        MainWindow->setCentralWidget(centralwidget);
        lcdNumber->raise();
        verticalWidget->raise();
        label->raise();
        treeView->raise();
        tableWidget->raise();
        run->raise();
        tablemanage->raise();
        datamanage->raise();
        fieldmanage->raise();
        label_2->raise();
        label_4->raise();
        sqllineEdit->raise();
        commit->raise();
        rollback->raise();
        textBrowser->raise();
        textBrowser_2->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1582, 27));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionnew);
        menu->addSeparator();
        menu->addAction(actionselect);
        menu->addSeparator();
        menu->addAction(actiondelete);
        menu->addSeparator();
        menu->addAction(actionlog);
        menu->addSeparator();
        menu->addAction(actionexit);
        menu->addSeparator();
        menu_2->addAction(actionrland);
        menu_2->addSeparator();
        menu_2->addAction(actioncpassword);
        menu_2->addSeparator();
        menu_2->addAction(actionpower);
        menu_2->addSeparator();
        menu_3->addAction(actionintroduce);
        menu_3->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionnew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        actionselect->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\351\241\271\347\233\256", nullptr));
        actionlog->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        actionexit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionrland->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\347\231\273\345\275\225", nullptr));
        actioncpassword->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        actionpower->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\346\235\203\351\231\220", nullptr));
        actionintroduce->setText(QCoreApplication::translate("MainWindow", "\351\241\271\347\233\256\344\273\213\347\273\215", nullptr));
        actiondelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\241\271\347\233\256", nullptr));
        label->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\350\277\231\345\260\206\347\224\250\346\235\245\344\275\234\350\241\250\345\233\276\345\275\242\347\225\214\351\235\242\345\261\225\347\244\272", nullptr));
        run->setText(QCoreApplication::translate("MainWindow", "\346\211\247\350\241\214\344\273\243\347\240\201", nullptr));
        tablemanage->setText(QCoreApplication::translate("MainWindow", "\350\241\250\347\256\241\347\220\206", nullptr));
        datamanage->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        fieldmanage->setText(QCoreApplication::translate("MainWindow", "\345\255\227\346\256\265\347\256\241\347\220\206", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>SQL\345\221\275\344\273\244\345\214\272</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\347\273\223\346\236\234\346\230\276\347\244\272\345\214\272 </p></body></html>", nullptr));
        sqllineEdit->setText(QCoreApplication::translate("MainWindow", "\345\234\250\346\255\244\350\276\223\345\205\245sql\345\221\275\344\273\244", nullptr));
        commit->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244", nullptr));
        rollback->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\212\344\270\200\346\255\245", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\346\245\267\344\275\223'; font-size:16pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\231\347\225\231\345\276\205\345\241\253\345\205\205\346\233\264\345\244\232\345\206\205\345\256\271</p></body></html>", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\346\245\267\344\275\223'; font-size:16pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\254\242\350\277\216\346\235\245\345\210\260\346\223\215\344\275\234\347\225\214\351\235\242\357\274\214\344\275\240\345\260\206\345\217\257\344\273\245\350\277\233\350\241\214\345\210\233\345\273\272\345\272\223\343\200\201\350\241\250\357\274\214\347\256\241\347\220\206\346\225\260\346\215\256\347\255\211\346\223\215\344\275\234</p></body></html>", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

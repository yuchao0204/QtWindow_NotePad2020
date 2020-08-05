/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWin
{
public:
    QAction *action123;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWin)
    {
        if (MainWin->objectName().isEmpty())
            MainWin->setObjectName(QString::fromUtf8("MainWin"));
        MainWin->resize(800, 600);
        action123 = new QAction(MainWin);
        action123->setObjectName(QString::fromUtf8("action123"));
        centralwidget = new QWidget(MainWin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWin);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWin->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWin->setStatusBar(statusbar);

        retranslateUi(MainWin);

        QMetaObject::connectSlotsByName(MainWin);
    } // setupUi

    void retranslateUi(QMainWindow *MainWin)
    {
        MainWin->setWindowTitle(QApplication::translate("MainWin", "MainWin", nullptr));
        action123->setText(QApplication::translate("MainWin", "123", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWin: public Ui_MainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H

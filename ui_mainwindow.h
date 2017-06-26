/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextBrowser *textDisplayer;
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *sendMessageButton;
    QPushButton *startCommunicationsButton;
    QPushButton *quitButton;
    QPushButton *leaveChannelButton;
    QLabel *label_2;
    QFrame *enterNameFrame;
    QLabel *enterNameLabel;
    QLineEdit *enterNameEdit;
    QPushButton *enterNameButton;
    QLabel *loginErrorLabel;
    QListWidget *communicationsWidget;
    QPushButton *refreshButton;
    QListWidget *clientsList;
    QLabel *requestLabel;
    QPushButton *acceptRequestButton;
    QPushButton *declineRequestButton;
    QMenuBar *menuBar;
    QMenu *menuSecure_Internet_Relay_Chat;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(987, 677);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textDisplayer = new QTextBrowser(centralWidget);
        textDisplayer->setObjectName(QStringLiteral("textDisplayer"));
        textDisplayer->setGeometry(QRect(40, 30, 411, 241));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(460, 20, 161, 17));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(40, 280, 411, 81));
        QFont font;
        font.setPointSize(8);
        font.setItalic(false);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QLatin1String(".QLineEdit, .QTextEdit\n"
"{\n"
"background-color: bluergb(0, 0, 200);\n"
"}"));
        sendMessageButton = new QPushButton(centralWidget);
        sendMessageButton->setObjectName(QStringLiteral("sendMessageButton"));
        sendMessageButton->setGeometry(QRect(130, 360, 89, 25));
        QFont font1;
        font1.setPointSize(8);
        sendMessageButton->setFont(font1);
        startCommunicationsButton = new QPushButton(centralWidget);
        startCommunicationsButton->setObjectName(QStringLiteral("startCommunicationsButton"));
        startCommunicationsButton->setGeometry(QRect(660, 30, 111, 25));
        startCommunicationsButton->setFont(font1);
        quitButton = new QPushButton(centralWidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(0, 570, 111, 41));
        leaveChannelButton = new QPushButton(centralWidget);
        leaveChannelButton->setObjectName(QStringLiteral("leaveChannelButton"));
        leaveChannelButton->setGeometry(QRect(360, 360, 89, 25));
        leaveChannelButton->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(810, 10, 101, 17));
        enterNameFrame = new QFrame(centralWidget);
        enterNameFrame->setObjectName(QStringLiteral("enterNameFrame"));
        enterNameFrame->setGeometry(QRect(40, 230, 891, 211));
        enterNameFrame->setStyleSheet(QLatin1String(".QFrame\n"
"{\n"
"background-color: bluergb(0, 0, 200);\n"
"}"));
        enterNameFrame->setFrameShape(QFrame::StyledPanel);
        enterNameFrame->setFrameShadow(QFrame::Raised);
        enterNameLabel = new QLabel(enterNameFrame);
        enterNameLabel->setObjectName(QStringLiteral("enterNameLabel"));
        enterNameLabel->setGeometry(QRect(380, 40, 231, 31));
        QFont font2;
        font2.setPointSize(15);
        enterNameLabel->setFont(font2);
        enterNameEdit = new QLineEdit(enterNameFrame);
        enterNameEdit->setObjectName(QStringLiteral("enterNameEdit"));
        enterNameEdit->setGeometry(QRect(150, 100, 621, 41));
        enterNameButton = new QPushButton(enterNameFrame);
        enterNameButton->setObjectName(QStringLiteral("enterNameButton"));
        enterNameButton->setGeometry(QRect(400, 150, 131, 41));
        loginErrorLabel = new QLabel(enterNameFrame);
        loginErrorLabel->setObjectName(QStringLiteral("loginErrorLabel"));
        loginErrorLabel->setGeometry(QRect(40, 70, 811, 20));
        loginErrorLabel->setAutoFillBackground(false);
        loginErrorLabel->setStyleSheet(QLatin1String(".QLabel\n"
"{\n"
"background-color: red\n"
"}"));
        communicationsWidget = new QListWidget(centralWidget);
        communicationsWidget->setObjectName(QStringLiteral("communicationsWidget"));
        communicationsWidget->setGeometry(QRect(460, 40, 171, 321));
        refreshButton = new QPushButton(centralWidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));
        refreshButton->setGeometry(QRect(668, 100, 101, 31));
        clientsList = new QListWidget(centralWidget);
        clientsList->setObjectName(QStringLiteral("clientsList"));
        clientsList->setGeometry(QRect(810, 30, 161, 471));
        requestLabel = new QLabel(centralWidget);
        requestLabel->setObjectName(QStringLiteral("requestLabel"));
        requestLabel->setGeometry(QRect(240, 500, 631, 20));
        acceptRequestButton = new QPushButton(centralWidget);
        acceptRequestButton->setObjectName(QStringLiteral("acceptRequestButton"));
        acceptRequestButton->setGeometry(QRect(380, 540, 89, 25));
        declineRequestButton = new QPushButton(centralWidget);
        declineRequestButton->setObjectName(QStringLiteral("declineRequestButton"));
        declineRequestButton->setGeometry(QRect(480, 540, 89, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 987, 22));
        menuSecure_Internet_Relay_Chat = new QMenu(menuBar);
        menuSecure_Internet_Relay_Chat->setObjectName(QStringLiteral("menuSecure_Internet_Relay_Chat"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSecure_Internet_Relay_Chat->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        textDisplayer->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "active communications", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        sendMessageButton->setText(QApplication::translate("MainWindow", "Send Message", Q_NULLPTR));
        startCommunicationsButton->setText(QApplication::translate("MainWindow", "Start Communication", Q_NULLPTR));
        quitButton->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        leaveChannelButton->setText(QApplication::translate("MainWindow", "Leave Channel", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Active users", Q_NULLPTR));
        enterNameLabel->setText(QApplication::translate("MainWindow", "Enter Username", Q_NULLPTR));
        enterNameButton->setText(QApplication::translate("MainWindow", "Continue", Q_NULLPTR));
        loginErrorLabel->setText(QApplication::translate("MainWindow", "asdasdasdasd", Q_NULLPTR));
        refreshButton->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        requestLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        acceptRequestButton->setText(QApplication::translate("MainWindow", "Acccept", Q_NULLPTR));
        declineRequestButton->setText(QApplication::translate("MainWindow", "Decline", Q_NULLPTR));
        menuSecure_Internet_Relay_Chat->setTitle(QApplication::translate("MainWindow", "Secure Internet Relay Chat", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

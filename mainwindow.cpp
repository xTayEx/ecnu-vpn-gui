#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createTrayIcon();
    systemTray->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_button_clicked()
{
    QString username = ui->username_lineedit->text();
    QString password = ui->password_lineedit->text();
    QString cmd = "echo '%1\n%2' | sudo openconnect vpn-cn.ecnu.edu.cn";
    cmd = cmd.arg(username, password);
    qDebug() << cmd << "\n";
    QStringList args;
    args << "-c" << cmd;
    if (QProcess::startDetached("/usr/bin/bash", args)) {
        qDebug() << "Failed to run\n";
    }
    ui->login_button->setDisabled(true);
}

void MainWindow::createTrayIcon()
{
    trayMenu = new QMenu(this);
    trayMenu->addAction(restoreAction);
    trayMenu->addAction(quitAction);
    systemTray = new QSystemTrayIcon(this);
    systemTray->setContextMenu(trayMenu);
    systemTray->setIcon(QIcon(":/image/ecnu_icon.png"));
}

void MainWindow::createActions()
{
    restoreAction = new QAction("restore", this);
    connect(restoreAction,
            &QAction::triggered,
            this,
            &QWidget::showNormal);

    quitAction = new QAction("quit", this);
    connect(quitAction,
            &QAction::triggered,
            this,
            &QApplication::quit);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (systemTray->isVisible()) {
        hide();
        event->ignore();
    }
}

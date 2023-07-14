#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ecnu-vpn-gui_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QString cmd = "sudo killall openconnect";
    QStringList args;
    args << "-c" << cmd;
    QObject::connect(&a, &QApplication::aboutToQuit, [=]() {
        QProcess::startDetached("/usr/bin/bash", args);
    });
    MainWindow w;
    w.setWindowTitle("ECNU vpn client");

    w.show();
    return a.exec();
}

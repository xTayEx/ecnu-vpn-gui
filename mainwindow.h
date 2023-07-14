#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_button_clicked();
    void onWindowIconChanged(Qt::WindowStates oldState, Qt::WindowStates newState) {
        if (newState & Qt::WindowMinimized) {
            hide(); // hide window
            systemTray->show(); // show system tray
        } else {
            systemTray->hide(); // hide system tray
            show(); // show window
        }
    }

private:
    void createTrayIcon();
    void createActions();

    void closeEvent(QCloseEvent *event) override;

    QAction *restoreAction;
    QAction *quitAction;
    Ui::MainWindow *ui;
    QSystemTrayIcon *systemTray;
    QMenu *trayMenu;
};
#endif // MAINWINDOW_H

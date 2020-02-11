#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "types.h"
#include "ros_bridge.h"
#include "ros_topic.h"
#include "ros_service.h"
#include "client/socket_tcp_connection.h"
#include "ros_time.h"

using namespace rosbridge2cpp;

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
    void on_connectBtn_clicked();

    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;
    SocketTCPConnection *t;
    ROSBridge *ros;
    bool isConnected;

    ROSTopic *test_topic;
    ROSTopic *sub_topic;
    void initVal();

};
#endif // MAINWINDOW_H

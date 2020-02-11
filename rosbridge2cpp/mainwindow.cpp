#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isConnected(false)
{
    ui->setupUi(this);
    this->initVal();
}

MainWindow::~MainWindow()
{
    delete test_topic;
    delete sub_topic;

    delete ros;
    delete t;

    delete ui;
}


void MainWindow::on_connectBtn_clicked()
{
    if(not isConnected) {
        if(ros->Init(QUrl("ws://192.168.1.102:9090")))
        {
            isConnected = not isConnected;
        }else{
            std::cerr << "Failed to connect to ROSBridge" << std::endl;
        }

        test_topic = new ROSTopic(*ros, "/test", "std_msgs/String");
        sub_topic = new ROSTopic(*ros, "/client_count", "std_msgs/Int32");
        rapidjson::Document d;
        sub_topic->Subscribe([&](ROSBridgePublishMsg& msg) -> void {std::cout << Helper::get_string_from_rapidjson(msg.ToJSON(d.GetAllocator())) << std::endl;});
    }
}

void MainWindow::on_startBtn_clicked()
{
    rapidjson::Document cmd;
    cmd.SetObject();
    cmd.AddMember("data","HHHHHHHHHHH", cmd.GetAllocator());
    test_topic->Publish(cmd);
}

void MainWindow::initVal()
{
    t = new SocketTCPConnection();
    t->RegisterErrorCallback([](QAbstractSocket::SocketError err) {
        if(err == QAbstractSocket::SocketError::HostNotFoundError)
            std::cout << "Host not found - You should correct the IP" << std::endl;
        if(err == QAbstractSocket::SocketError::SocketAccessError )
            std::cout << "Error on ROSBridge Socket - You should reinit ROSBridge" << std::endl;
    });
    ros = new ROSBridge(*t);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTimer>
#include <QLayout>
#include <QVector>
#include <QList>
#include <QPainter>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void TcpConnected();
    void TcpReceiverData();
    void TcpError();
    void confirm_btn();
    void led_button();
    void fan_button();
    void exti_btn();
    void SendWifiInfoFunction();
    void on_smartconfig_clicked();
    void paintEvent(QPaintEvent *);
    void creatData();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    QUdpSocket *udpSever;
    QDialog *smartconfig;
    QLineEdit *eidtSSID;
    QLineEdit *eidtPassword;
    QPushButton *ledbutton;
    QPushButton *fanbutton;
    QLineEdit *temp;
    QLineEdit *gas;
    QLineEdit *humidity;
    QLineEdit *dust;
    QPushButton *confirm;  //开始配置按键
    QPushButton *exti; //返回按键
    QTimer *SendWifiInfo;  //定时发送信息的定时器

//    QPainter painter;
    double m_count=50;
    double x;
    int ledState;
    int fanState;
    QTimer* m_Timer;
    QList<double> xList;
    QList<double> yList;
};

#endif // MAINWINDOW_H

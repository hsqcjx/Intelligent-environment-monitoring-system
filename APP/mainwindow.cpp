#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <qmath.h>



void MainWindow::creatData()
{
    m_count+=0.2;
    if(yList.count()>=100)
    {
        for(int i=0;i<yList.count()-1;i++)
        {
            yList[i]=yList[i+1];
        }
        yList[99]=qSin(m_count);
        update();
    }
    else
    {
        x += 0.2;
        xList.append(x);
        yList.append(qSin(x));
 //      update();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
#if 0
    QPainter painter(this);
    QPen pen;

    smartconfig = new QDialog();
    painter.begin(smartconfig);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(3);
    painter.setPen(pen);
    int x=width()/10;
    int y=height()/10;
    int w=width()-width()/5;
    int h=height()-height()/5;

    int DataX=x+w/20;
    int DataY1=y+h/3*0.8;
    int DataY2=y+h/3*0.8+h/3;
    int DataY3=y+h/3*0.8+h/3+h/3;
    painter.setViewport(x,y,w,h);
    painter.setWindow(x,y,w,h);
    painter.setBrush(Qt::white);
    painter.drawRect(x,y,w,h);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(QPointF(20, 20),"温度");

    painter.drawLine(QPoint(DataX, y), QPoint(DataX, y+h));
    painter.drawLine(QPoint(DataX, DataY1), QPoint(w-DataX, DataY1));
    painter.drawLine(QPoint(DataX, DataY2), QPoint(w-DataX, DataY2));
    painter.drawLine(QPoint(DataX, DataY3), QPoint(w-DataX, DataY3));

//ui->setupUi(this);
    for(int i = 0; i < yList.count(); i++)
    {
        if(i == 0)
            painter.drawPoint(QPointF(xList[i], yList[i]));
        else
            painter.drawLine(QPointF(xList[i-1], yList[i-1]), QPointF(xList[i], yList[i]));
    }
#endif
}













MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ledState=0;
    fanState=0;
    udpSever = new QUdpSocket();
    tcpClient=new QTcpSocket();
    this->setWindowTitle("ESP8266 APP");
    //创建定时器
    SendWifiInfo = new QTimer(this);
    temp = new QLineEdit(this);
    gas = new QLineEdit(this);
    humidity = new QLineEdit(this);
    dust = new QLineEdit(this);
    ledbutton =new QPushButton(this);
    fanbutton =new QPushButton(this);
    //将定时器超时信号与槽(功能函数)联系起来
    connect( SendWifiInfo, SIGNAL(timeout()), this, SLOT(SendWifiInfoFunction()) );

    connect(tcpClient, SIGNAL(connected()), this, SLOT(TcpConnected()));
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(TcpReceiverData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
            this, SLOT(TcpError()));
    QFont font ( "Microsoft YaHei", 10, 75); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
 //   ui->DataText->setFont(font);
    x = -10;
    m_count = 0;
    m_Timer = new QTimer(this);
    m_Timer->start(10);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(creatData()));

    //设置值
    temp->setText(tr("28℃"));
    gas->setText(tr("9"));
    humidity->setText(tr("80%"));
    dust->setText(tr("90"));

    //设置位置
    temp->move(220, 100);
    gas->move(220, 150);
    humidity->move(220, 200);
    dust->move(220, 250);

    //设置不可外部写入
    temp->setEnabled(false);
    gas->setEnabled(false);
    humidity->setEnabled(false);
    dust->setEnabled(false);

    //设置对齐方式
    temp->setAlignment(Qt::AlignRight);
    gas->setAlignment(Qt::AlignRight);
    humidity->setAlignment(Qt::AlignRight);
    dust->setAlignment(Qt::AlignRight);

    //设置led灯开关
    QIcon ledico("F:/QT/APP/picture/ON.jpg");
    ledbutton->setIcon(ledico);
    ledbutton->resize(100,30);
    ledbutton->move(390+220,120);
    ledbutton->setIconSize(QSize(100,30));
    ledbutton->setFlat(true);
    connect(ledbutton, SIGNAL(clicked()), this, SLOT(led_button()));  //连接信号槽

    //设置风扇的开关
    QIcon fanico("F:/QT/APP/picture/ON.jpg");  //引用本地图片
    fanbutton->setIcon(fanico);   //将图片添加到开关中
    fanbutton->resize(100,30);    //设置开关大小
    fanbutton->move(390+220,220); //设置开关位置
    fanbutton->setIconSize(QSize(100,30)); //设置图片大小
    fanbutton->setFlat(true);
    connect(fanbutton, SIGNAL(clicked()), this, SLOT(fan_button()));  //连接信号槽
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TcpConnected()
{
    confirm->setEnabled(false);
    eidtSSID->setEnabled(false);
    eidtPassword->setEnabled(false);
    SendWifiInfo->start(1000);
}


void MainWindow::TcpReceiverData()
{
    QByteArray Data=tcpClient->readAll();
    qDebug()<<QString(Data)<<endl;
    this->show();
    smartconfig->reject();
}

void MainWindow::TcpError()
{
}

void MainWindow::SendWifiInfoFunction()
{
    QString Data="SSID:";
    Data+=eidtSSID->text();
    Data+="   password:";
    Data+=eidtPassword->text();
    qDebug()<<QString(Data)<<endl;
    tcpClient->write(Data.toLatin1());
}

void MainWindow::confirm_btn()
{
    confirm->setText(tr("配置中..."));
    exti->setText(tr("取消配置"));
    eidtPassword->setEnabled(false);
    eidtSSID->setEnabled(false);
    QByteArray Data="SSID:";
    Data+=eidtSSID->text();
    Data+="   password:";
    Data+=eidtPassword->text();
    qDebug()<<QString(Data)<<endl;
    tcpClient->connectToHost("192.168.4.1",8000);
}


void MainWindow::led_button()
{
    if(fanState==0)
    {
        fanState=1;
        QIcon ledico("F:/QT/APP/picture/OFF.jpg");
        ledbutton->setIcon(ledico);
    }
    else
    {
        fanState=0;
        QIcon ledico("F:/QT/APP/picture/ON.jpg");
        ledbutton->setIcon(ledico);
    }
    ledbutton->setIconSize(QSize(100,30));
    ledbutton->setFlat(true);
}

void MainWindow::fan_button()
{
    if(fanState==0)
    {
        fanState=1;
        QIcon fanico("F:/QT/APP/picture/OFF.jpg");
        fanbutton->setIcon(fanico);
    }
    else
    {
        fanState=0;
        QIcon fanico("F:/QT/APP/picture/ON.jpg");
        fanbutton->setIcon(fanico);
    }
    fanbutton->setIconSize(QSize(100,30));
    fanbutton->setFlat(true);
}


void MainWindow::exti_btn()
{
    this->show();
    smartconfig->reject();
}

void MainWindow::on_smartconfig_clicked()
{
//    this->hide();
    smartconfig = new QDialog();
    //窗口初始化
    smartconfig->setModal(true);//与show（）搭配，堆栈上创建
    smartconfig->setWindowTitle("wifi config");//消息框名称

    //设置窗口大小和位置
    smartconfig->setMaximumSize(400, 260);
    smartconfig->setMinimumSize(400, 260);
    smartconfig->move(this->geometry().x() + 200, this->geometry().y() + 95);
    QPalette palette;
    QPixmap pixmap = QPixmap("F:/QT/APP/picture/WIFI1.png").scaled(smartconfig->size());
    palette.setBrush(smartconfig->backgroundRole(),
                              QBrush(pixmap.scaled(smartconfig->size(),
                              Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation)));
    smartconfig->setPalette(palette);
    smartconfig->setAutoFillBackground(true);
    //初始化SSID提示框和输入框
    QLabel *lableSSID = new QLabel(smartconfig);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    lableSSID->setPalette(pe);
    lableSSID->setText("wifi名称");
    lableSSID->move(110, 50);//设置位置
    eidtSSID = new QLineEdit(smartconfig);
    eidtSSID->setText(tr("chenjiaxin"));
    eidtSSID->move(110, 80);


    //初始化password提示框和输入框
    QLabel *lablePassword = new QLabel(smartconfig);
    lablePassword->setPalette(pe);
    lablePassword->setText("wifi密码");
    lablePassword->move(110, 110);
    eidtPassword = new QLineEdit(smartconfig);
    eidtPassword->setText(tr("201530040119"));
    eidtPassword->move(110, 140);

    //初始化确认按键
    confirm = new QPushButton(smartconfig);
    confirm->setText("确认");
    confirm->move(90,200);
    connect(confirm, SIGNAL(clicked()), this, SLOT(confirm_btn()));  //连接信号槽

    //初始化返回按键
    exti = new QPushButton(smartconfig);
    exti->setText("返回");
    exti->move(190,200);
    connect(exti, SIGNAL(clicked()), this, SLOT(exti_btn())); //连接信号槽

    smartconfig->show();
}



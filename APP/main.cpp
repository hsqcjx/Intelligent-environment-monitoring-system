#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(780,480);


    QPalette palette;
    //设置背景图片
    QPixmap pixmap = QPixmap("F:/QT/APP/picture/environment2.png").scaled(w.size());  //设置背景图片
    palette.setBrush(w.backgroundRole(),
                              QBrush(pixmap.scaled(w.size(),
                              Qt::IgnoreAspectRatio,
                              Qt::SmoothTransformation)));
    w.setPalette(palette);
    w.setAutoFillBackground(true);
#if 0
    pixmap = QPixmap("F:/QT/project/APP/71X58PICNjx_1024.jpg").scaled(w.size()/2);    //利用label显示一张图片
    QLabel *label = new QLabel(&w);
    label->setPixmap(QPixmap(pixmap));
    label->resize(QSize(pixmap.width(),pixmap.height()));

    QLabel *label1 = new QLabel(label);
    label1->setText("天气");
    label1->move(100,100);
#endif
    //设置字体颜色和大小
    QFont ft;
    ft.setPointSize(14);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    //数据采集框
    QLabel *Data = new QLabel(&w);
    Data->setPalette(pe);
    Data->setFont(ft);
    Data->setText("数据采集");
    Data->move(140, 50);//设置位置

    //智能控制框
    pe.setColor(QPalette::WindowText,Qt::black);
    QLabel *Control = new QLabel(&w);
    Control->setPalette(pe);
    Control->setFont(ft);
    Control->setText("智能控制");
    Control->move(390+140, 50);//设置位置

    //温度数据
    pe.setColor(QPalette::WindowText,Qt::white);
    QLabel *Tempdata = new QLabel(&w);
    Tempdata->setPalette(pe);
    Tempdata->setFont(ft);
    Tempdata->setText("温度");
    Tempdata->move(50, 100);//设置位置

    //湿度数据
    QLabel *gasdata = new QLabel(&w);
    gasdata->setPalette(pe);
    gasdata->setFont(ft);
    gasdata->setText("有害气体");
    gasdata->move(50, 150);//设置位置
    //湿度数据
    QLabel *Humdata = new QLabel(&w);
    Humdata->setPalette(pe);
    Humdata->setFont(ft);
    Humdata->setText("湿度");
    Humdata->move(50, 200);//设置位置

    //湿度数据
    QLabel *dustdata = new QLabel(&w);
    dustdata->setPalette(pe);
    dustdata->setFont(ft);
    dustdata->setText("粉尘");
    dustdata->move(50, 250);//设置位置

    //灯光控制
    pe.setColor(QPalette::WindowText,Qt::black);
    QLabel *ledcon = new QLabel(&w);
    ledcon->setPalette(pe);
    ledcon->setFont(ft);
    ledcon->setText("灯光");
    ledcon->move(390+50, 120);//设置位置

    //风扇控制
    QLabel *fancon = new QLabel(&w);
    fancon->setPalette(pe);
    fancon->setFont(ft);
    fancon->setText("风扇");
    fancon->move(390+50, 220);//设置位置
    w.show();
    return a.exec();
}

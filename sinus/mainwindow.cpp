#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include <QPushButton>
#include "QtMath"
#include "paths.h"
#include "poland.h"
#include "QLineEdit"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);


    button = new QPushButton(this);
    button->setGeometry(width()-10 -100, 10 ,100, 50);
    connect(button,SIGNAL(clicked()),this,SLOT(myClick()));


    ui->s->setGeometry(40, 10, width()-3*10 -130, 50);


    ui->a->setGeometry(width()-10 -80, 70, 80, 50);

    ui->b->setGeometry(width()-10 -80, 130, 80, 50);

    ui->fx->setGeometry(10,10, 20 , 50);

    ui->al->setGeometry(width()-10 -100, 70, 20, 50);

    ui->bl->setGeometry(width()-10 -100, 130, 20, 50);

    ui->ai->setGeometry(width()-10 -70,height()-60, 100, 10);

    ui->bi->setGeometry(width()-10 -70,height()-45, 100, 10);



}

void MainWindow::myClick(){



    QString line = ui->s->text();






    ui->label->setGeometry(10, 70, width()-3*10 -100, height()-8*10);
    QPixmap pm(width()-3*10-100,height()-8*10);
    QPainter painter;
    painter.begin(&pm);
    QPen pen;
    pen.setColor(0xc0c0c0);

    float ans;


    pm.fill(0xda70d6);
    ui->label->setPixmap(pm);

    double x, xmax, xmin;
    if (ui->a->text().size() > 0){
        double a = (ui->a->text()).toDouble();
        xmax = a;
    }
    else{
        xmax = 10;
    }

    if (ui->b->text().size() > 0){
        double b = (ui->b->text()).toDouble();
        xmin = b;
    }
    else{
        xmin = -10;
    }



    double y, ymax, ymin;


    ymax = 10;
    ymin = -10;


    int xg, xgmax, xgmin;
    xgmin =0;
    xgmax = pm.width();

    int yg, ygmax, ygmin;
    ygmax = pm.height();
    ygmin = 0;

    double kx, ky;
    kx = (xgmax-xgmin)/(xmax-xmin);
    ky = (ygmin-ygmax)/(ymax-ymin);
    x= xmin;

    double x0, y0;
    x0 = xgmin - kx*xmin;
    y0 = ygmin - ky*ymax;

    double stepx;
    stepx = (xmax-xmin)/(xgmax-xgmin);




    QPainterPath path;
    QPainterPath path1;
    xg = int(x0 + kx*x);
    yg = int(y0 + ky*y);
    path1.moveTo(xgmax/2, ygmax);
    path1.lineTo(xgmax/2,ygmin);

    path1.moveTo(xgmin, ygmax/2);
    path1.lineTo(xgmax,ygmax/2);

    painter.setPen(pen);
    painter.drawPath(path1);

    pen.setColor(0x191970);
    painter.setPen(pen);
    string stri = line.toStdString();
    QString striQ = QString(stri.c_str());
    striQ.replace('x',"(" + QString(to_string(x).c_str()) + ")");
    string strix = striQ.toStdString();
    calc(strix,ans);
    y = ans;
    xg = int(x0 + kx*x);
    yg = int(y0 + ky*y);
    path.moveTo(xg,yg);


    while(x<=xmax){
        QString striQ = QString(stri.c_str());
        striQ.replace('x',"(" + QString(to_string(x).c_str()) + ")");
        strix = striQ.toStdString();
        calc(strix,ans);
        y = ans;
        if ((ky*y) >= ygmax || (y0 + ky*y) <= ygmin || calc(strix,ans) == false ) {
            x = x + stepx;
            QString striQ = QString(stri.c_str());
            striQ.replace('x',"(" + QString(to_string(x).c_str()) + ")");
            strix = striQ.toStdString();
            calc(strix,ans);
            y = ans;
            xg = int(x0 + kx*x);
            yg = int(y0 + ky*y);
            path.moveTo(xg,yg);
        }
        else {
            xg = int(x0 + kx*x);
            yg = int(y0 + ky*y);
            path.lineTo(xg,yg);

            x = x+stepx;
        }
    }
    painter.drawPath(path);
    ui->label->setPixmap(pm);



}



MainWindow::~MainWindow()
{
    delete ui;
}

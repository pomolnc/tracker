#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

#include <string.h>
#include "Marker.h"
#include "XPoints.h"
#include "MTXPoint.h"
#include "Persistence.h"
#include "Cameras.h"
#include "Facet.h"
#include "Xform3D.h"
#include "MTC.h"
#include <math.h>
#include <stdio.h>
#include <vector>
#include "processing.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    Processing *process=new Processing();
    process=new Processing();
    process->initialINIAccess();
    process->setupCameras();

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    timer->setInterval(50);
    timer->start();


}

Widget::~Widget()
{
    delete ui;
}


//void Widget::drawImage(unsigned char *addrL,unsigned char *addrR,unsigned char *addrM){
void Widget::drawImage(){
//    QImage img；
//    img=(addr,640*2,480*2,QImage::Format_Grayscale8))；
//     QImage imgL(addrL,640*2,480*2,QImage::Format_Grayscale8);
//     QImage imgR(addrR,640*2,480*2,QImage::Format_Grayscale8);
//     QImage imgM(addrM,640*2,480*2,QImage::Format_Grayscale8);
    QImage imgL((unsigned char *)addrL,640*2,480*2,QImage::Format_Grayscale8);
    QImage imgR((unsigned char *)addrR,640*2,480*2,QImage::Format_Grayscale8);
    QImage imgM((unsigned char *)addrM,640*2,480*2,QImage::Format_Grayscale8);

    imgL=imgL.convertToFormat(QImage::Format_RGB888);
    imgR=imgR.convertToFormat(QImage::Format_RGB888);
    imgM=imgM.convertToFormat(QImage::Format_RGB888);

//    process->showIdentifiedXPoints();
    process->pXPoints->processFrame(NULL);
MTCollection::Collection* xpointsCollection = new MTCollection::Collection(process->pXPoints->detectedXPoints(process->pCurrCam));
//if (xpointsCollection->count() == 0) {
//    delete xpointsCollection;
//    return;
//}

double x[3], y[3];
double x3,y3,z3;
int XPNum=1;
MTXPoint* XP;
double radius = 5;
// here we need the left side presentation: coordinates in sensor space, distances etc
Xform3D* Marker2CurrCameraXf = NULL;
//cout<<xpointsCollection->count()<<endl;
    if(process->isShowingPositions)
    if(1)
{
    for (XPNum = 1; XPNum <= xpointsCollection->count(); XPNum++)
    {
        XP = new MTXPoint(xpointsCollection->itemI(XPNum));
        XP->Position2D(&x[0], &y[0], &x[1], &y[1], &x[2], &y[2]);
        XP->Position3D(&x3, &y3, &z3);
        XP->setIndex(XPNum);

//        drawCircle(0, x[0], y[0], radius, 1.0, 0, 0, 0xFFFF);
        drawCircle(&imgL,x[0], y[0]);
        drawCircle(&imgR,x[1], y[1]);
//        drawCircle(&imgM,x[2], y[2]);
//        cout<<x[2]<<' '<<y[2]<<endl;//the  XY-Component of the 2D back projected XP on middle image is allways zero.
        drawText(&imgL,x[0], y[0],XPNum);
        drawText(&imgR,x[1], y[1],XPNum);
    }
}

//drawText(&imgL,100, 100,XPNum);
     ui->label_L->setPixmap(QPixmap::fromImage(imgL.scaled(ui->label_L->width(),ui->label_L->height())));
     ui->label_R->setPixmap(QPixmap::fromImage(imgR.scaled(ui->label_R->width(),ui->label_R->height())));
     ui->label_M->setPixmap(QPixmap::fromImage(imgM.scaled(ui->label_M->width(),ui->label_M->height())));



}

void Widget::drawCircle(QImage* img,double x,double y){
    QPainter painter(img);
    QPen pen(Qt::green,4,Qt::SolidLine);
    painter.setPen(pen);
    double radius= 15;
    painter.drawEllipse(x-radius/2,y-radius/2,radius,radius);
}

void Widget::drawText(QImage* img,double x,double y,int num){
    QPainter painter(img);
//    QPen pen(Qt::green,2,Qt::SolidLine);
    QPen pen(Qt::green,2);
    painter.setPen(pen);
//    double radius= 20;
//    QRectF rect(x+2, y, 200 ,300 );
//    painter.drawText(rect,Qt::AlignLeft,tr("#"+num));
    QFont font("Arial",20,QFont::Bold,true);
    painter.setFont(font);

    QString strNum;
    QString text="#"+strNum.setNum(num);
     QByteArray ba= text.toLatin1();
     const char *c_text = ba.data();
     painter.drawText(x+10,y+5,tr(c_text));

}

void Widget::onTimerOut()
{
//    cout<<process->pCameras->grabFrame(NULL)<<endl;
    process->pCameras->grabFrame(NULL);
    /*unsigned char **addrL,**addrR,**addrM;*/// declare 3 address to store cameras's frame addresses
    process->pCurrCam->getImages3( &addrL, &addrR, &addrM);
//cout<<(int)addrL<<endl<<(int)addrR<<endl<<(int)addrM<<endl;
//    drawImage((unsigned char *)addrL, (unsigned char *)addrR, (unsigned char *)addrM);
    drawImage();
// QImage imgL((unsigned char *)addrL,640*2,480*2,QImage::Format_Grayscale8);
//  ui->label_L->setPixmap(QPixmap::fromImage(imgL.scaled(ui->label_L->width(),ui->label_L->height())));

}

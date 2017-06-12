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

// here we need the left side presentation: coordinates in sensor space, distances etc
Xform3D* Marker2CurrCameraXf = NULL;
//cout<<xpointsCollection->count()<<endl;
PointNum=xpointsCollection->count();
    if(process->isShowingPositions)
    if(1)
{
    for (XPNum = 1; XPNum <= xpointsCollection->count(); XPNum++)
    {
        XP = new MTXPoint(xpointsCollection->itemI(XPNum));
        XP->Position2D(&x[0], &y[0], &x[1], &y[1], &x[2], &y[2]);
        XP->Position3D(&x3, &y3, &z3);

        pointX[XPNum]=x3;
        pointY[XPNum]=y3;
        pointZ[XPNum]=z3;

        XP->setIndex(XPNum);

//        drawCircle(0, x[0], y[0], radius, 1.0, 0, 0, 0xFFFF);
        drawCircle(&imgL,x[0], y[0]);
        drawCircle(&imgR,x[1], y[1]);
//        drawCircle(&imgM,x[2], y[2]);
//        cout<<x[2]<<' '<<y[2]<<endl;//the XY-Component of the 2D back projected XP on middle image is allways zero.
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
    filterProcess();
    displayData();
    basePosition();
    targetPosition();

}


void Widget::displayData(){
    int index_x_in=ui->comboBox_x_in->currentIndex();
    QString strNum;
    QString text="base_x_in:["+strNum.setNum(pointX[index_x_in+1])+","+strNum.setNum(pointY[index_x_in+1])+","+strNum.setNum(pointZ[index_x_in+1])+"]";
    QByteArray ba= text.toLatin1();
    const char *c_text = ba.data();
    ui->label_x_in_dis->setText(c_text);

    int index_x_out=ui->comboBox_x_out->currentIndex();
    text="base_x_out:["+strNum.setNum(pointX[index_x_out+1])+","+strNum.setNum(pointY[index_x_out+1])+","+strNum.setNum(pointZ[index_x_out+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_x_out_dis->setText(c_text);

    int index_y_in=ui->comboBox_y_in->currentIndex();
    text="base_y_in:["+strNum.setNum(pointX[index_y_in+1])+","+strNum.setNum(pointY[index_y_in+1])+","+strNum.setNum(pointZ[index_y_in+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_y_in_dis->setText(c_text);

    int index_y_out=ui->comboBox_y_out->currentIndex();
    text="base_y_out:["+strNum.setNum(pointX[index_y_out+1])+","+strNum.setNum(pointY[index_y_out+1])+","+strNum.setNum(pointZ[index_y_out+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_y_out_dis->setText(c_text);

    int index_1_in=ui->comboBox_1_in->currentIndex();
    text="end_1_in:["+strNum.setNum(pointX[index_1_in+1])+","+strNum.setNum(pointY[index_1_in+1])+","+strNum.setNum(pointZ[index_1_in+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_1_in_dis->setText(c_text);

    int index_1_out=ui->comboBox_1_out->currentIndex();
    text="end_1_out:["+strNum.setNum(pointX[index_1_out+1])+","+strNum.setNum(pointY[index_1_out+1])+","+strNum.setNum(pointZ[index_1_out+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_1_out_dis->setText(c_text);

    int index_2_in=ui->comboBox_2_in->currentIndex();
    text="end_2_in:["+strNum.setNum(pointX[index_2_in+1])+","+strNum.setNum(pointY[index_2_in+1])+","+strNum.setNum(pointZ[index_2_in+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_2_in_dis->setText(c_text);

    int index_2_out=ui->comboBox_2_out->currentIndex();
    text="end_2_out:["+strNum.setNum(pointX[index_2_out+1])+","+strNum.setNum(pointY[index_2_out+1])+","+strNum.setNum(pointZ[index_2_out+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_2_out_dis->setText(c_text);

    int index_3_in=ui->comboBox_3_in->currentIndex();
    text="end_3_in:["+strNum.setNum(pointX[index_3_in+1])+","+strNum.setNum(pointY[index_3_in+1])+","+strNum.setNum(pointZ[index_3_in+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_3_in_dis->setText(c_text);

    int index_3_out=ui->comboBox_3_out->currentIndex();
    text="end_3_out:["+strNum.setNum(pointX[index_3_out+1])+","+strNum.setNum(pointY[index_3_out+1])+","+strNum.setNum(pointZ[index_3_out+1])+"]";
    ba= text.toLatin1();
    c_text = ba.data();
    ui->label_3_out_dis->setText(c_text);
}

void Widget::filterProcess(){
    for (int i=1;i<=10;i++){
        pointX[i]=filter(pointX[i]);
        pointY[i]=filter(pointY[i]);
        pointZ[i]=filter(pointZ[i]);
    }
}

double Widget::filter(double input)
{
    double array[10];
    for (int i=10;i>=1;i=i-1)
    {
        if (i=1)
           {array[i]=input;}
        else
           {array[i]=array[i-1];}
    }
    return (array[10]+array[9]+array[8]+array[7]+array[6]+array[5]+array[4]+array[3]+array[2]+array[1])/10;
}

void Widget::targetPosition(){
    int index_1_in=ui->comboBox_1_in->currentIndex();
    int index_1_out=ui->comboBox_1_out->currentIndex();
    int index_2_in=ui->comboBox_2_in->currentIndex();
    int index_2_out=ui->comboBox_2_out->currentIndex();
    int index_3_in=ui->comboBox_3_in->currentIndex();
    int index_3_out=ui->comboBox_3_out->currentIndex();

    double tar_abs_position_x= (pointX[index_1_in+1]+pointX[index_2_in+1]+pointX[index_3_in+1]+pointX[index_1_out+1]+pointX[index_2_out+1]+pointX[index_3_out+1])/6;
    double tar_abs_position_y= (pointY[index_1_in+1]+pointY[index_2_in+1]+pointY[index_3_in+1]+pointY[index_1_out+1]+pointY[index_2_out+1]+pointY[index_3_out+1])/6;
    double tar_abs_position_z= (pointZ[index_1_in+1]+pointZ[index_2_in+1]+pointZ[index_3_in+1]+pointZ[index_1_out+1]+pointZ[index_2_out+1]+pointZ[index_3_out+1])/6;

    double x_unit[3];
    double y_unit[3];
    double z_unit[3];

    int index_x_in=ui->comboBox_x_in->currentIndex();
    int index_x_out=ui->comboBox_x_out->currentIndex();
    int index_y_in=ui->comboBox_y_in->currentIndex();
    int index_y_out=ui->comboBox_y_out->currentIndex();

    x_unit[1]=(pointX[index_x_out+1]-pointX[index_x_in+1])/40;
    x_unit[2]=(pointY[index_x_out+1]-pointY[index_x_in+1])/40;
    x_unit[3]=(pointZ[index_x_out+1]-pointZ[index_x_in+1])/40;

    y_unit[1]=(pointX[index_y_out+1]-pointX[index_y_in+1])/40;
    y_unit[2]=(pointY[index_y_out+1]-pointY[index_y_in+1])/40;
    y_unit[3]=(pointZ[index_y_out+1]-pointZ[index_y_in+1])/40;

    //calculate z unit vector by cross product
    z_unit[1]=x_unit[2]* y_unit[3]-y_unit[2]* x_unit[3];
    z_unit[2]=x_unit[3]* y_unit[1]-y_unit[3]* x_unit[1];
    z_unit[3]=x_unit[1]* y_unit[2]-y_unit[1]* x_unit[2];

    double tar_rel_position_x=dotproduct(tar_abs_position_x-basePoint[1],tar_abs_position_y-basePoint[2],tar_abs_position_z-basePoint[3],x_unit[1],x_unit[2],x_unit[3]);
    double tar_rel_position_y=dotproduct(tar_abs_position_x-basePoint[1],tar_abs_position_y-basePoint[2],tar_abs_position_z-basePoint[3],y_unit[1],y_unit[2],y_unit[3]);
    double tar_rel_position_z=dotproduct(tar_abs_position_x-basePoint[1],tar_abs_position_y-basePoint[2],tar_abs_position_z-basePoint[3],z_unit[1],z_unit[2],z_unit[3]);

    QString strNum;
    QString text="Target_Position:["+strNum.setNum(tar_rel_position_x)+","+strNum.setNum(tar_rel_position_y)+","+strNum.setNum(tar_rel_position_z)+"]";
    QByteArray ba= text.toLatin1();
    const char *c_text = ba.data();
    ui->label_TarPos_dis->setText(c_text);

}

void Widget::basePosition(){
    int index_x_in=ui->comboBox_x_in->currentIndex();
    int index_x_out=ui->comboBox_x_out->currentIndex();
    int index_y_in=ui->comboBox_y_in->currentIndex();
    int index_y_out=ui->comboBox_y_out->currentIndex();

    double base_x1=pointX[index_x_in+1]-35*(pointX[index_x_out+1]-pointX[index_x_in+1])/40;
    double base_x2=pointX[index_y_in+1]-35*(pointX[index_y_out+1]-pointX[index_y_in+1])/40;
    basePoint[1]=(base_x1+base_x2)/2;

    double base_y1=pointY[index_x_in+1]-35*(pointY[index_x_out+1]-pointY[index_x_in+1])/40;
    double base_y2=pointY[index_y_in+1]-35*(pointY[index_y_out+1]-pointY[index_y_in+1])/40;
    basePoint[2]=(base_y1+base_y2)/2;

    double base_z1=pointZ[index_x_in+1]-35*(pointZ[index_x_out+1]-pointZ[index_x_in+1])/40;
    double base_z2=pointZ[index_y_in+1]-35*(pointZ[index_y_out+1]-pointZ[index_y_in+1])/40;
    basePoint[3]=(base_z1+base_z2)/2;

}

double Widget::vecLen(double x1,double y1,double z1,double x2,double y2,double z2){
return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}

double Widget::dotproduct(double x1,double y1,double z1,double x2,double y2,double z2){
    return x1*x2+y1*y2+z1*z2;
}

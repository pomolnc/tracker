#include "widget.h"
#include "ui_widget.h"

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
    Processing* process=new Processing();
    process->initialINIAccess();
    process->setupCameras();

    unsigned char **addrL,**addrR,**addrM;// declare 3 address to store cameras's frame addresses
    process->pCurrCam->getImages3( &addrL, &addrR, &addrM);

    drawImage(addrL, addrR, addrM);


}

Widget::~Widget()
{
    delete ui;
}


void Widget::drawImage(unsigned char **addrL,unsigned char **addrR,unsigned char **addrM){
//    QImage img；
//    img=(addr,640*2,480*2,QImage::Format_Grayscale8))；
     QImage imgL((unsigned char *)addrL,640*2,480*2,QImage::Format_Grayscale8);
     QImage imgR((unsigned char *)addrR,640*2,480*2,QImage::Format_Grayscale8);
     QImage imgM((unsigned char *)addrM,640*2,480*2,QImage::Format_Grayscale8);

     ui->label_L->setPixmap(QPixmap::fromImage(imgL.scaled(ui->label_L->width(),ui->label_L->height())));

}

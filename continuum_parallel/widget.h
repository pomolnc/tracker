#ifndef WIDGET_H
#define WIDGET_H

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

#include <QWidget>
#include <QTimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
//    Processing *process=new Processing();
   void drawImage();
   void drawCircle(QImage* img,double x,double y);
   void drawText(QImage* img, double x, double y, int num);
   void displayData();
   double filter(double input);
   void filterProcess();
   void targetPosition();
   void basePosition();
   double vecLen(double x1,double y1,double z1,double x2,double y2,double z2);
   double dotproduct(double x1,double y1,double z1,double x2,double y2,double z2);


    unsigned char **addrL,**addrR,**addrM;
    Processing *process;
    QTimer *timer;

    double* pointX=new double[100];
    double* pointY=new double[100];
    double* pointZ=new double[100];
    int PointNum;
    double* basePoint=new double[3];
    double* targetPoint=new double[3];

private:
    Ui::Widget *ui;

public slots:
    void onTimerOut();
};

#endif // WIDGET_H

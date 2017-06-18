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
#include <QDir>
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
//   double filter(double input);
   double filter(double input,double &arr);
   void filterProcess();
   void targetPosition();
   void basePosition();
   double vecLen(double x1,double y1,double z1,double x2,double y2,double z2);
   double dotproduct(double x1,double y1,double z1,double x2,double y2,double z2);
   void fileOperation();

    unsigned char **addrL,**addrR,**addrM;
    Processing *process;
    QTimer *timer;

    double* pointX=new double[100];
    double* pointY=new double[100];
    double* pointZ=new double[100];
    int PointNum;
    double* basePoint=new double[3];
//    double* targetPoint=new double[3];
    double tar_abs_position_x;
    double tar_abs_position_y;
    double tar_abs_position_z;
    double tar_rel_position_x;
    double tar_rel_position_y;
    double tar_rel_position_z;

    double bufferX[10][10];
    double bufferY[10][10];
    double bufferZ[10][10];
private:
    Ui::Widget *ui;

public slots:
    void onTimerOut();
private slots:
    void on_pushButton_savedata_clicked();
};

#endif // WIDGET_H

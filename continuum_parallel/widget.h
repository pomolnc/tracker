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


    unsigned char **addrL,**addrR,**addrM;
    Processing *process;
    QTimer *timer;

private:
    Ui::Widget *ui;

public slots:
    void onTimerOut();
};

#endif // WIDGET_H

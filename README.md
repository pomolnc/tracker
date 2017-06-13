# ClaroNav MicronTracker
仅限于RIIlab内部使用。

## 基本代码
使用自带的MTDemoCPP中提供的库，删除flkt与openGL等GUI相关的部分。重点调用的是XPoint相关的函数，用以提取特征点的相关坐标。具体操作可查看API说明。

### XPoints Processing
A measurement cycle for XPoints Processing includes the following steps:
+ Calling Cameras_GrabFrame() to transfer the latest frame to the MTC’s buffers;
+ Calling XPoints_ProcessFrame() to detect each individual XPoints from the frame buffers;
+ Calling XPoints_DetectedXPointsGet() to obtain a collection of handles to the detected XPoints;
+ For each detected XPoints in the collection, calling XPoint_2DPositionGet() and XPoint_3DPositionGet() provide 3D and 2D position data of the XPoint.

这一部分的代码大部分不需要改动，可以尝试修改 XPoints_ProcessFrame() 中一些调整画面的参数。

## 扩展代码
主要使用Qt编写的代码：processing.cpp（修改自Demo中的GuiGenerator.cpp，主要是摄像头的初始化）、widget.cpp（GUI和主要的操作）。

processing.cpp中的基本不用管。
主要说一下widget.cpp。

```
    ui->setupUi(this);
    process=new Processing();
    process->initialINIAccess();
    process->setupCameras();
```
调用processing进行初始化，顺序不要改。

```
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    timer->setInterval(50);
    timer->start();
```
不断循环调用各种操作，各种操作都写在onTimerOut里。

```
void Widget::onTimerOut()
{
    process->pCameras->grabFrame(NULL);
    process->pCurrCam->getImages3( &addrL, &addrR, &addrM);
    drawImage();
    filterProcess();
    displayData();
    basePosition();
    targetPosition();
}
```
操作依次是：获取图片存放到3个地址中（Demo自带函数）、画图、坐标做均值滤波、显示数据、坐标转换。

```
void Widget::drawImage(){
    //获取三个摄像头的画面存入3个addr中
    QImage imgL((unsigned char *)addrL,640*2,480*2,QImage::Format_Grayscale8);
    QImage imgR((unsigned char *)addrR,640*2,480*2,QImage::Format_Grayscale8);
    QImage imgM((unsigned char *)addrM,640*2,480*2,QImage::Format_Grayscale8);
    //图片格式转换
    imgL=imgL.convertToFormat(QImage::Format_RGB888);
    imgR=imgR.convertToFormat(QImage::Format_RGB888);
    imgM=imgM.convertToFormat(QImage::Format_RGB888);

    //XPoint process的操作
    process->pXPoints->processFrame(NULL);
MTCollection::Collection* xpointsCollection = new MTCollection::Collection(process->pXPoints->detectedXPoints(process->pCurrCam));


double x[3], y[3];
double x3,y3,z3;
int XPNum=1;
MTXPoint* XP;

// here we need the left side presentation: coordinates in sensor space, distances etc
Xform3D* Marker2CurrCameraXf = NULL;
PointNum=xpointsCollection->count();//获取识别点的数量
    if(process->isShowingPositions)
    if(1)
{
    for (XPNum = 1; XPNum <= xpointsCollection->count(); XPNum++)
    {
        //获取识别出的点在每个摄像头中的二维坐标与三维坐标，并存入数组。只有左右两个摄像头有坐标数据
        XP = new MTXPoint(xpointsCollection->itemI(XPNum));
        XP->Position2D(&x[0], &y[0], &x[1], &y[1], &x[2], &y[2]);
        XP->Position3D(&x3, &y3, &z3);

        pointX[XPNum]=x3;
        pointY[XPNum]=y3;
        pointZ[XPNum]=z3;

        XP->setIndex(XPNum);
        
        //在图片里相应位置画圈
        drawCircle(&imgL,x[0], y[0]);
        drawCircle(&imgR,x[1], y[1]);
        //在图片里相应点标出序号
        drawText(&imgL,x[0], y[0],XPNum);
        drawText(&imgR,x[1], y[1],XPNum);
    }
}
     //在GUI中显示图片
     ui->label_L->setPixmap(QPixmap::fromImage(imgL.scaled(ui->label_L->width(),ui->label_L->height())));
     ui->label_R->setPixmap(QPixmap::fromImage(imgR.scaled(ui->label_R->width(),ui->label_R->height())));
     ui->label_M->setPixmap(QPixmap::fromImage(imgM.scaled(ui->label_M->width(),ui->label_M->height())));
}
```


```
void Widget::drawCircle(QImage* img,double x,double y)
void Widget::drawText(QImage* img,double x,double y,int num)
```
这两个都是用于在画面上画图和写文字的函数。要注意x和y的意义，不是中心的坐标，而是图形左上角的位置。另外drawText的参数const char*格式要注意。

```
void Widget::displayData()
void Widget::targetPosition()
void Widget::basePosition()
void Widget::fileOperation()
```
针对不同需求可进行修改的函数，主要是GUI显示、向量运算和文件保存等功能。针对需求改变量，格式可以不改。

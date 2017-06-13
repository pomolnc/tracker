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

···
    ui->setupUi(this);
    process=new Processing();
    process->initialINIAccess();
    process->setupCameras();
···

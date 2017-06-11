/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_L;
    QLabel *label_R;
    QLabel *label_M;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1405, 1010);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 1381, 1001));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_L = new QLabel(gridLayoutWidget);
        label_L->setObjectName(QStringLiteral("label_L"));
        label_L->setMinimumSize(QSize(640, 480));
        label_L->setMaximumSize(QSize(640, 480));

        gridLayout->addWidget(label_L, 0, 0, 1, 1);

        label_R = new QLabel(gridLayoutWidget);
        label_R->setObjectName(QStringLiteral("label_R"));
        label_R->setMinimumSize(QSize(640, 480));
        label_R->setMaximumSize(QSize(640, 480));

        gridLayout->addWidget(label_R, 0, 1, 1, 1);

        label_M = new QLabel(gridLayoutWidget);
        label_M->setObjectName(QStringLiteral("label_M"));
        label_M->setMinimumSize(QSize(640, 480));
        label_M->setMaximumSize(QSize(640, 480));

        gridLayout->addWidget(label_M, 1, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        label_L->setText(QString());
        label_R->setText(QString());
        label_M->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

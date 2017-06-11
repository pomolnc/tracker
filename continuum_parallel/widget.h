#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
   void drawImage(unsigned char **addrL, unsigned char **addrR, unsigned char **addrM);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H

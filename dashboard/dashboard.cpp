#include "dashboard.h"
#include "QPainter"

#include "pixmaps/defaultmonitor.h"



Dashboard::Dashboard()
{
    pixmap = new DefaultMonitor();
}

void Dashboard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap test = pixmap->scaled(this->width(), this->height(), Qt::KeepAspectRatio ,Qt::SmoothTransformation);

    //painter.drawPixmap(0, 0, this->width(), this->height(), *pixmap);
    painter.drawPixmap(0, 0, this->width(), this->height(), test);

}







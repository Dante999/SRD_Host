#include "dashboard.h"
#include "QPainter"

#include "pixmaps/defaultmonitor.h"
#include "pixmaps/damagemonitor.h"



Dashboard::Dashboard(clientDataStruct *gameData)
{
    this->gameData = gameData;

    //content = new DefaultMonitor();
    content = new DamageMonitor();
}


void Dashboard::paintEvent(QPaintEvent *)
{
    content->drawValues(*gameData);

    QPainter painter(this);

    QPixmap scaledPixmap = content->scaled(this->width(),
                                           this->height(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);

    painter.drawPixmap(0, 0, this->width(), this->height(), scaledPixmap);

}







#include "damagemonitor.h"
#include "settings.h"
#include <QPainter>
#include <QDebug>
#include <QVector>







DamageMonitor::DamageMonitor()
{

    carshape = new CarShape();

    QPainter p(this);

    p.drawPixmap(0, 0, PIXMAP_WIDTH, PIXMAP_HEIGHT, *carshape);
    calculateFrames();

}




void DamageMonitor::calculateFrames()
{

}

void DamageMonitor::drawLabels()
{

}



void DamageMonitor::drawValues(clientDataStruct data)
{

}

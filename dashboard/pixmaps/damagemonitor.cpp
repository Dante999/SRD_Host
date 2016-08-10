#include "damagemonitor.h"
#include "settings.h"
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QThread>






DamageMonitor::DamageMonitor()
{
    refreshCarshape();
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
    carshape.drawShapeImage();
    carshape.drawDamage(shape::TYRE_FRONT_LEFT, data.damageTyre[eTYRE_FRONT_LEFT]);
    carshape.drawDamage(shape::TYRE_FRONT_RIGHT, data.damageTyre[eTYRE_FRONT_RIGHT]);
    carshape.drawDamage(shape::TYRE_REAR_LEFT, data.damageTyre[eTYRE_REAR_LEFT]);
    carshape.drawDamage(shape::TYRE_REAR_RIGHT, data.damageTyre[eTYRE_REAR_RIGHT]);
    carshape.drawDamage(shape::SUSP_FRONT_LEFT, data.damageSuspension[eTYRE_FRONT_LEFT]);
    carshape.drawDamage(shape::SUSP_FRONT_RIGHT, data.damageSuspension[eTYRE_FRONT_RIGHT]);
    carshape.drawDamage(shape::SUSP_REAR_LEFT, data.damageSuspension[eTYRE_REAR_LEFT]);
    carshape.drawDamage(shape::SUSP_REAR_RIGHT, data.damageSuspension[eTYRE_REAR_RIGHT]);
    carshape.drawDamage(shape::ENGINE, data.damageEngine);
    carshape.drawDamage(shape::AERO, data.damageAero);
}

void DamageMonitor::refreshCarshape()
{
    QPainter paint;

    paint.begin(this);
    paint.drawPixmap(0, 0, PIXMAP_WIDTH, PIXMAP_HEIGHT, carshape);
    paint.end();
}

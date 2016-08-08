#include "damagemonitor.h"
#include "settings.h"
#include <QPainter>
#include <QDebug>
#include <QVector>


#define TYRE_WIDTH      26
#define TYRE_HEIGHT     61
#define TYRE_RADIUS     4

#define BRAKE_WIDTH     7
#define BRAKE_HEIGHT    53
#define BRAKE_RADIUS    2




DamageMonitor::DamageMonitor()
{
    carshape = new QImage;

    if( carshape->load("img//carframe.png") == false)
    {
        qDebug() << "can't load image carshape!";
    }


    QPainter p(this);

    p.drawImage(QRectF(0,0,PIXMAP_WIDTH,PIXMAP_HEIGHT), *carshape);

    p.end();
    calculateFrames();

}




void DamageMonitor::calculateFrames()
{

    QPainter paint(this);



    //frames[DMG::TYRE_FRONT_LEFT].addRoundedRect(431, 188, )
    frames[DMG::TYRE_FRONT_LEFT].addRoundedRect(431, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    frames[DMG::TYRE_FRONT_RIGHT].addRoundedRect(568, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    frames[DMG::TYRE_REAR_LEFT].addRoundedRect(431, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    frames[DMG::TYRE_REAR_RIGHT].addRoundedRect(568, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);

    frames[DMG::BRAKE_FRONT_LEFT].addRoundedRect(458, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    frames[DMG::BRAKE_FRONT_RIGHT].addRoundedRect(560, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    frames[DMG::BRAKE_REAR_LEFT].addRoundedRect(458, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    frames[DMG::BRAKE_REAR_RIGHT].addRoundedRect(560, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);

    frames[DMG::ENGINE].addRect(497, 422, 31, 43);
    frames[DMG::ENGINE].addRect(493, 424, 4, 39);
    frames[DMG::ENGINE].addRect(528, 424, 4, 39);


    QVector<QPointF> aeroPoints;

    aeroPoints.append(QPointF(431, 133));
    aeroPoints.append(QPointF(431, 133));
    aeroPoints.append(QPointF(431, 184));
    aeroPoints.append(QPointF(435, 184));
    aeroPoints.append(QPointF(451, 176));
    aeroPoints.append(QPointF(469, 176));
    aeroPoints.append(QPointF(477, 173));
    aeroPoints.append(QPointF(493, 157));
    aeroPoints.append(QPointF(501, 157));
    aeroPoints.append(QPointF(504, 133));

    QPolygonF leftAero(aeroPoints);

    for(int i = 0; i < aeroPoints.size(); i++)
    {
        qreal x = aeroPoints.at(i).x();

        //x = x * (-1) + (PIXMAP_WIDTH/2);
        x = (512-x) + 513;

        aeroPoints.operator [](i).setX(x);
    }

    QPolygonF rightAero(aeroPoints);

    frames[DMG::AERO].addPolygon(leftAero);
    frames[DMG::AERO].addPolygon(rightAero);




/*
    frames[DMG::AERO].moveTo(431, 133);
    frames[DMG::AERO].lineTo(431, 184);
    frames[DMG::AERO].lineTo(435, 184);
    frames[DMG::AERO].lineTo(451, 176);
    frames[DMG::AERO].lineTo(469, 176);
    frames[DMG::AERO].lineTo(477, 173);
    frames[DMG::AERO].lineTo(493, 157);
    frames[DMG::AERO].lineTo(501, 157);
    frames[DMG::AERO].lineTo(504, 133);
*/


    /*
    frames[DMG::AERO].moveTo(431, 133);
    frames[DMG::AERO].lineTo(431, 183);
    frames[DMG::AERO].lineTo(452, 175);
    frames[DMG::AERO].lineTo(466, 176);
    frames[DMG::AERO].lineTo(477, 172);
    frames[DMG::AERO].lineTo(492, 156);
    frames[DMG::AERO].lineTo(501, 156);
    frames[DMG::AERO].lineTo(504, 133);
    //frames[DMG::AERO].lineTo(431, 133);
*/



            paint.setPen(Qt::red);

            //QBrush brush;

            paint.setOpacity(0.5);



            for(size_t i = 0; i < sizeof(frames)/sizeof(QPainterPath); i++)
            {
                paint.fillPath(frames[i], QBrush(Qt::green));
                //paint.drawPath(frames[i]);
            }


}

void DamageMonitor::drawLabels()
{

}



void DamageMonitor::drawValues(clientDataStruct data)
{

}

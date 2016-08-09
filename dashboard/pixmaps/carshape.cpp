#include "carshape.h"

#include <QDebug>
#include <QPainter>



#define CAR_IMAGE_X_CENTER  512

#define TYRE_WIDTH      26
#define TYRE_HEIGHT     61
#define TYRE_RADIUS     4

#define BRAKE_WIDTH     7
#define BRAKE_HEIGHT    53
#define BRAKE_RADIUS    2


CarShape::CarShape() : QPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT)
{
    carImage = new QImage;

    if( carImage->load("img//carframe.png") == false)
    {
        qDebug() << "can't load image carshape!";
    }


    QPainter p(this);
    p.drawImage(QRectF(0,0,PIXMAP_WIDTH,PIXMAP_HEIGHT), *carImage);
    p.end();


    drawShapes();
}


CarShape::drawShapes()
{
    QVector<QPointF> points;

    // TYRES
    dmgParts[TYRE_FRONT_LEFT].addRoundedRect(431, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    dmgParts[TYRE_FRONT_RIGHT].addRoundedRect(568, 188, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    dmgParts[TYRE_REAR_LEFT].addRoundedRect(431, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);
    dmgParts[TYRE_REAR_RIGHT].addRoundedRect(568, 488, TYRE_WIDTH, TYRE_HEIGHT, TYRE_RADIUS, TYRE_RADIUS);

    // BRAKES
    dmgParts[BRAKE_FRONT_LEFT].addRoundedRect(458, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    dmgParts[BRAKE_FRONT_RIGHT].addRoundedRect(560, 191, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    dmgParts[BRAKE_REAR_LEFT].addRoundedRect(458, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);
    dmgParts[BRAKE_REAR_RIGHT].addRoundedRect(560, 492, BRAKE_WIDTH, BRAKE_HEIGHT, BRAKE_RADIUS, BRAKE_RADIUS);

    // ENGINE
    dmgParts[ENGINE].addRect(497, 422, 31, 43);
    dmgParts[ENGINE].addRect(493, 424, 4, 39);
    dmgParts[ENGINE].addRect(528, 424, 4, 39);

    // AERO
    points.append(QPointF(431, 133));
    points.append(QPointF(431, 133));
    points.append(QPointF(431, 184));
    points.append(QPointF(435, 184));
    points.append(QPointF(451, 176));
    points.append(QPointF(469, 176));
    points.append(QPointF(477, 173));
    points.append(QPointF(493, 157));
    points.append(QPointF(501, 157));
    points.append(QPointF(504, 133));

    QPolygonF leftAero(points);

    mirrorPoints(CAR_IMAGE_X_CENTER, &points );

    QPolygonF rightAero(points);

    dmgParts[AERO].addPolygon(leftAero);
    dmgParts[AERO].addPolygon(rightAero);

    // SUSPENSION FRONT
    points.clear();
    points.append(QPointF(499, 198));
    points.append(QPointF(465, 206));
    points.append(QPointF(465, 230));
    points.append(QPointF(496, 256));
    points.append(QPointF(498, 242));
    points.append(QPointF(471, 220));
    points.append(QPointF(499, 218));
    points.append(QPointF(499, 210));
    points.append(QPointF(485, 210));
    points.append(QPointF(499, 206));

    dmgParts[SUSP_FRONT_LEFT].addPolygon(QPolygonF(points));

    mirrorPoints(CAR_IMAGE_X_CENTER, &points);

    dmgParts[SUSP_FRONT_RIGHT].addPolygon(QPolygonF(points));







    QPainter paint(this);

    paint.setPen(Qt::red);
    paint.setOpacity(0.5);

    for(size_t i = 0; i < sizeof(dmgParts)/sizeof(QPainterPath); i++)
    {
        paint.fillPath(dmgParts[i], QBrush(Qt::green));
    }
}






CarShape::mirrorPoints(qreal xMirror, QVector<QPointF> *points)
{
    for(int i = 0; i < points->size(); i++)
    {
        qreal x = points->at(i).x();
        //x = (512-x) + 513;
        x = (2*xMirror) - x;

        points->operator [](i).setX(x);
    }
}



CarShape::drawValue(parts carPart, int percent)
{

}

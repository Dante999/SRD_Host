#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

#include "pixmaps/defaultmonitor.h"

enum {
    tLast = 0,
    tBest,
    tDelta,
    tDeltaS1,
    tDeltaS2,
    tDeltaS3,
    tempMotor,
    tempWater,
    deltaBehind,
    deltaBefore,
    //-------

};






class Dashboard : public QWidget
{
    Q_OBJECT


private:
    QPixmap *pixmap;



public:
    Dashboard();

    void paintEvent(QPaintEvent *);

    void drawRect();
};

#endif // DASHBOARD_H

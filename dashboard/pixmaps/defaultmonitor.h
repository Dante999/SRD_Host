#ifndef DEFAULTMONITOR_H
#define DEFAULTMONITOR_H

#include <QPixmap>
#include "interfacemonitor.h"
#include "textframe.h"





enum
{
    STATUS_MSG = 0,
    GEAR,
    BEST_LAP,
    LAST_LAP,
    DELTA_LAP,
    DELTA_S1,
    DELTA_S2,
    DELTA_S3,
    TEMP_MOT,
    TEMP_WAT,
    PLACE1,
    POSITION,
    DELTA_BEHIND,
    DELTA_AHEAD,


    //------
    DES_MAX
};






class DefaultMonitor : public QPixmap, public InterfaceMonitor
{

private:

    TextFrame labels[DES_MAX];
    TextFrame values[DES_MAX];


    void calculateFrames();
    void drawLabels();
    void drawValues();
    void refresh();



public:
    DefaultMonitor();


};

#endif // DEFAULTMONITOR_H


#include "defaultmonitor.h"

#include "settings.h"
#include <QPainter>
#include <QRectF>
//#include "textframe.h"





DefaultMonitor::DefaultMonitor() : QPixmap(PIXMAP_WIDTH, PIXMAP_HEIGHT)
{
    this->fill(Qt::black);

    //labels = new TextFrame[DES_MAX];
    //values = new TextFrame[DES_MAX];

    for(size_t i = 0; i < sizeof(labels)/sizeof(TextFrame); i++)
    {
        values[i].setParameter(QFont(FONT, FONT_SIZE_TEXT), LABEL_LETTERS, textPos::RIGHT);
    }


    for(size_t i = 0; i < sizeof(values)/sizeof(TextFrame); i++)
    {
        values[i].setParameter(QFont(FONT, FONT_SIZE_TEXT), VALUE_LETTERS, textPos::RIGHT);
    }

    values[GEAR].setParameter(QFont(FONT, FONT_SIZE_GEAR), 1, textPos::CENTER);
    values[STATUS_MSG].setParameter(QFont(FONT, FONT_SIZE_STATUS), -1, textPos::CENTER);




    calculateFrames();
    drawLabels();
    drawValues();



}



void DefaultMonitor::calculateFrames()
{
    // STATUS-FRAME
    labels[STATUS_MSG].setTop(BORDER_SPACE);
    labels[STATUS_MSG].setBottom(FONT_SIZE_STATUS+BORDER_SPACE);
    labels[STATUS_MSG].setLeft(MIN_X);
    labels[STATUS_MSG].setRight(MAX_X);

    // GEAR-FRAME
    values[GEAR].setOriginCenter(PIXMAP_HEIGHT/2, PIXMAP_WIDTH/2);

    // TOP-LEFT
    labels[TEMP_MOT].setOriginTopLeft(MIN_Y, MIN_X);
    labels[TEMP_WAT].addUnder(&labels[TEMP_MOT]);
    labels[PLACE1].addUnder(&labels[TEMP_WAT]);

    values[TEMP_MOT].addRightFrom(&labels[TEMP_MOT]);
    values[TEMP_WAT].addRightFrom(&labels[TEMP_WAT]);
    values[PLACE1].addRightFrom(&labels[PLACE1]);

    // BOTTOM-LEFT
    labels[DELTA_AHEAD].setOriginBotLeft(MAX_Y, MIN_X);
    labels[DELTA_BEHIND].addAbove(&labels[DELTA_AHEAD]);
    labels[POSITION].addAbove(&labels[DELTA_BEHIND]);

    values[DELTA_AHEAD].addRightFrom(&labels[DELTA_AHEAD]);
    values[DELTA_BEHIND].addRightFrom(&labels[DELTA_BEHIND]);
    values[POSITION].addRightFrom(&labels[POSITION]);

    // TOP-RIGHT
    values[LAST_LAP].setOriginTopRight(MIN_Y, MAX_X);
    values[BEST_LAP].addUnder(&values[LAST_LAP]);
    values[DELTA_LAP].addUnder(&values[BEST_LAP]);

    labels[LAST_LAP].addLeftFrom(&values[LAST_LAP]);
    labels[BEST_LAP].addLeftFrom(&values[BEST_LAP]);
    labels[DELTA_LAP].addLeftFrom(&values[DELTA_LAP]);

    // TOP-BOTTOM
    values[DELTA_S3].setOriginBotRight(MAX_Y, MAX_X);
    values[DELTA_S2].addAbove(&values[DELTA_S3]);
    values[DELTA_S1].addAbove(&values[DELTA_S2]);

    labels[DELTA_S1].addLeftFrom(&values[DELTA_S1]);
    labels[DELTA_S2].addLeftFrom(&values[DELTA_S2]);
    labels[DELTA_S3].addLeftFrom(&values[DELTA_S3]);

}

void DefaultMonitor::drawLabels()
{
    for(size_t i = 0; i < sizeof(labels)/sizeof(TextFrame); i++)
    {
        labels[i].drawFrame(this);
    }

    labels[LAST_LAP].drawText(this, "tLast");
    labels[BEST_LAP].drawText(this, "tBest");
    labels[DELTA_LAP].drawText(this, "Delta");

    labels[DELTA_S1].drawText(this, "S1");
    labels[DELTA_S2].drawText(this, "S2");
    labels[DELTA_S3].drawText(this, "S3");

    labels[TEMP_MOT].drawText(this, "TOil");
    labels[TEMP_WAT].drawText(this, "TWat");
    labels[PLACE1].drawText(this, "-");

    labels[POSITION].drawText(this, "Pos");
    labels[DELTA_BEHIND].drawText(this, "tAhe");
    labels[DELTA_AHEAD].drawText(this, "tBeh");

    values[GEAR].drawText(this, "1");

}

void DefaultMonitor::drawValues()
{
    for(size_t i = 0; i < sizeof(values)/sizeof(TextFrame); i++)
    {
        values[i].drawFrame(this);
    }



    values[LAST_LAP].drawTime(this, 65.14552);
    values[LAST_LAP].drawTime(this, -65.14552);

}

void DefaultMonitor::refresh()
{

}

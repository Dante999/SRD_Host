#ifndef TEXTFRAME_H
#define TEXTFRAME_H

#include <QRectF>
#include <QPixmap>
#include <QFont>
#include "settings.h"

namespace textPos
{
    enum alignement{
        CENTER,
        LEFT,
        RIGHT
    };
}


class TextFrame : public QRectF
{

private:
    int letterWidth;
    int letterHeight;

    QFont font;
    int letterCount;
    textPos::alignement align;

public:
    TextFrame();


    void setParameter(QFont font, int letterCount, textPos::alignement align);

    void setOriginCenter(qreal y, qreal x);
    void setOriginTopLeft(qreal y, qreal x);
    void setOriginTopRight(qreal y, qreal x);
    void setOriginBotRight(qreal y, qreal x);
    void setOriginBotLeft(qreal y, qreal x);



    void addRightFrom(TextFrame *frame);
    void addLeftFrom(TextFrame *frame);
    void addUnder(TextFrame *frame);
    void addAbove(TextFrame *frame);




/*
    void setOriginCenter(qreal y, qreal x, int letterCount, int fontSize = fontSize);
    void setOriginTopLeft(qreal y, qreal x, int letterCount, int fontSize = fontSize);
    void setOriginTopRight(qreal y, qreal x, int letterCount, int fontSize = fontSize);
    void setOriginBotRight(qreal y, qreal x, int letterCount, int fontSize = fontSize);
    void setOriginBotLeft(qreal y, qreal x, int letterCount, int fontSize = fontSize);

    void setOriginTopLeft(QPointF corner, int letterCount, int fontSize = fontSize);
    void setOriginTopRight(QPointF corner, int letterCount, int fontSize = fontSize);
    void setOriginBotLeft(QPointF corner, int letterCount, int fontSize = fontSize);
    void setOriginBotRight(QPointF corner, int letterCount, int fontSize = fontSize);

    void addRightFrom(TextFrame *frame, int letterCount, int fontSize = fontSize);
    void addLeftFrom(TextFrame *frame, int letterCount, int fontSize = fontSize);
    void addUnder(TextFrame *frame, int letterCount, int fontSize = fontSize);
    void addAbove(TextFrame *frame, int letterCount, int fontSize = fontSize);
*/
    void drawText(QPixmap *target, QString text);
    void drawFrame(QPixmap *target);






};

#endif // TEXTFRAME_H


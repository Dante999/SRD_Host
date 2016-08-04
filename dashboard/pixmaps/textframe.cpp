#include "textframe.h"


#include <QPainter>

#define FONT_H  1.25
#define FONT_W  0.75



TextFrame::TextFrame()
{
    font.setFamily("Consolas");
    font.setPointSize(30);
    letterCount = 5;
    align = textPos::LEFT;

    letterWidth = FONT_W * font.pointSize();
    letterHeight = FONT_H * font.pointSize();
}

void TextFrame::setParameter(QFont font, int letterCount, textPos::alignement align)
{
    this->font = font;
    this->letterCount = letterCount;
    this->align = align;

    letterWidth = FONT_W * font.pointSize();
    letterHeight = FONT_H * font.pointSize();
}

void TextFrame::setOriginCenter(qreal y, qreal x)
{
    this->setLeft(x-(letterWidth*letterCount)/2);
    this->setRight(x+(letterWidth*letterCount)/2);
    this->setTop    (y-(letterHeight/2));
    this->setBottom (y+(letterHeight/2));
}



void TextFrame::setOriginTopLeft(qreal y, qreal x)
{
    this->setLeft(x);
    this->setTop(y);
    this->setRight(x+(letterWidth*letterCount));
    this->setBottom(y+letterHeight);
}

void TextFrame::setOriginTopRight(qreal y, qreal x)
{
    this->setRight(x);
    this->setTop(y);
    this->setLeft(x-(letterWidth*letterCount));
    this->setBottom(y+letterHeight);
}

void TextFrame::setOriginBotRight(qreal y, qreal x)
{
    this->setRight(x);
    this->setBottom(y);
    this->setLeft(x-(letterWidth*letterCount));
    this->setTop(y-letterHeight);
}

void TextFrame::setOriginBotLeft(qreal y, qreal x)
{
    this->setLeft(x);
    this->setBottom(y);
    this->setRight(x+(letterWidth*letterCount));
    this->setTop(y-letterHeight);
}


void TextFrame::addRightFrom(TextFrame *frame)
{
    this->setBottom(frame->bottom());
    this->setTop(this->bottom() - letterHeight);
    this->setLeft(frame->right() + BORDER_SPACE);
    this->setRight(this->left() + (letterWidth*letterCount));
}

void TextFrame::addLeftFrom(TextFrame *frame)
{
    this->setBottom(frame->bottom());
    this->setTop(this->bottom() - letterHeight);
    this->setRight(frame->left() - BORDER_SPACE);
    this->setLeft(this->right() - (letterWidth*letterCount));
}

void TextFrame::addUnder(TextFrame *frame)
{
    this->setLeft(frame->left());
    this->setRight(this->left() + (letterWidth*letterCount));
    this->setTop(frame->bottom() + BORDER_SPACE);
    this->setBottom(this->top() + letterHeight);
}

void TextFrame::addAbove(TextFrame *frame)
{
    this->setLeft(frame->left());
    this->setRight(this->left() + (letterWidth*letterCount));
    this->setBottom(frame->top() - BORDER_SPACE);
    this->setTop(this->bottom() - letterHeight);
}

void TextFrame::drawText(QPixmap *target, QString text)
{
    QPainter p(target);

    p.setPen(Qt::white);
    p.setFont(font);


    switch(align)
    {
        case textPos::LEFT:     p.drawText(this->toRect(), Qt::AlignLeft|Qt::AlignVCenter, text);
                                break;
        case textPos::CENTER:     p.drawText(this->toRect(), Qt::AlignCenter, text);
                                break;
        case textPos::RIGHT:     p.drawText(this->toRect(), Qt::AlignRight|Qt::AlignVCenter, text);
                                break;
    }

}

void TextFrame::drawFrame(QPixmap *target)
{
    QPainter p(target);
    p.setPen(Qt::white);
    p.drawRect(this->toRect());

}


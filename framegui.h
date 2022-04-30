#ifndef FRAMEGUI_H
#define FRAMEGUI_H

#include <gridgui.h>

class FrameGUI : public GridGUI
{
public:
    FrameGUI(uint8_t gridSize = 3, QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // FRAMEGUI_H

#ifndef FRAMEGUI_H
#define FRAMEGUI_H

#include "gridgui.h"

class FrameGUI : public GridGUI
{
public:
    FrameGUI(uint8_t gridSize, QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // FRAMEGUI_H

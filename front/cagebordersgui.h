#ifndef CAGEBORDERSGUI_H
#define CAGEBORDERSGUI_H

#include "gridgui.h"

class CageBordersGUI : public GridGUI
{
public:
    CageBordersGUI(uint8_t gridSize = 3, QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CAGEBORDERSGUI_H

#ifndef CAGEBORDERSGUI_H
#define CAGEBORDERSGUI_H

#include "gridgui.h"
#include "../back/cell.h"

class CageBordersGUI : public GridGUI
{
public:
    CageBordersGUI(uint8_t gridSize, cell *cells = Q_NULLPTR,
                   QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    cell *cells() const;
    void setCells(cell *cells);

private:
    uint8_t m_penWidth;
    cell *m_cells;
};

#endif // CAGEBORDERSGUI_H

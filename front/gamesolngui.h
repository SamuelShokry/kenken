#ifndef GAMESOLNGUI_H
#define GAMESOLNGUI_H

#include "gridgui.h"

#include "../back/cell.h"

class GameSolnGUI : public GridGUI
{
public:
    GameSolnGUI(quint8 gridSize, cell *cells = Q_NULLPTR,
                QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    cell *cells() const;
    void setCells(quint8 size, cell *cells); //assume always changes the cells

private:
    cell *m_cells;

    void drawValue(const quint8 index, const QPointF topleft,
                   const QPointF bottomRight, QPainter *painter);
};

#endif // GAMESOLNGUI_H

#ifndef TARGETGUI_H
#define TARGETGUI_H

#include "gridgui.h"

#include "../back/cage.h"
#include "../back/cell.h"

class TargetGUI : public GridGUI
{
public:
    TargetGUI(uint8_t gridSize, cage *cages, cell *cells, QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    cage *cages() const;
    void setCages(cage *cages); // assume that ALWAYS the cages are changed

    cell *cells() const;
    void setCells(cell *cells); // assume that ALWAYS the cells are changed

private:
    cage *m_cages;
    cell *m_cells;

    void drawTarget(const quint8 cageIndex, const QPointF center, QPainter *painter);
};

#endif // TARGETGUI_H

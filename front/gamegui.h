#ifndef GAMEGUI_H
#define GAMEGUI_H

#include "gridgui.h"
#include "framegui.h"
#include "cagebordersgui.h"
#include "targetgui.h"
#include "gamesolngui.h"

#include "../back/grid.h"

class GameGUI : public GridGUI
{
public:
    GameGUI(quint8 gridSize, grid *grid, QGraphicsItem *parent = Q_NULLPTR);
    ~GameGUI();

    void setGrid(quint8 size, grid *grid);
    void drawSoln(quint8 size, cell *cells);
private:
    FrameGUI *m_frame;
    CageBordersGUI *m_cageBorders;
    TargetGUI *m_targets;
    GameSolnGUI *m_soln;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GAMEGUI_H

#include "gamegui.h"

GameGUI::GameGUI(quint8 gridSize, grid *grid, QGraphicsItem *parent)
    : GridGUI(gridSize, parent),
      m_frame(new FrameGUI(0, this)),
      m_cageBorders(new CageBordersGUI(0, Q_NULLPTR, this)),
      m_targets(new TargetGUI(0, Q_NULLPTR, Q_NULLPTR, this))
{
    setGrid(gridSize, grid);
}

GameGUI::~GameGUI()
{
    delete m_frame;
    delete m_cageBorders;
    delete m_targets;
}

void GameGUI::setGrid(quint8 size, grid *grid)
{
    setGridSize(size);

    m_frame->setGridSize(size);
    m_cageBorders->setGridSize(size);
    m_targets->setGridSize(size);

    if (grid) {
        cage *cages = grid->get_cages_ptr();
        cell *cells = grid->get_cells_ptr();

        m_cageBorders->setCells(cells);

        m_targets->setCages(cages);
        m_targets->setCells(cells);
    }
}


void GameGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

#include "targetgui.h"

#include <QPainter>

TargetGUI::TargetGUI(uint8_t gridSize, cage *cages, cell *cells, QGraphicsItem *parent)
    : GridGUI(gridSize, parent),
      m_cages(cages),
      m_cells(cells)
{

}


void TargetGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QFont font = painter->font();
    font.setPixelSize(18);
    painter->setFont(font);

    quint8 cellIndex, cageIndex;
    QPointF iter(0, 0);
    const QPointF inX(cellSize(), 0), inY(0, cellSize());
    for (int i = 0; i < gridSize(); ++i) {
        for (int j = 0; j < gridSize(); ++j) {
            cellIndex = index(i, j);
            cageIndex = m_cells[cellIndex].get_cage_index();

            if (cellIndex == m_cages[cageIndex].get_first_cell_in_cage())
                drawTarget(cageIndex, iter, painter);

            iter += inX;
        }
        iter += inY;
        iter.setX(0);
    }
}

cage *TargetGUI::cages() const
{
    return m_cages;
}

void TargetGUI::setCages(cage *cages)
{
    prepareGeometryChange();
    m_cages = cages;
}

cell *TargetGUI::cells() const
{
    return m_cells;
}

void TargetGUI::setCells(cell *cells)
{
    prepareGeometryChange();
    m_cells = cells;
}

void TargetGUI::drawTarget(const quint8 cageIndex, const QPointF center, QPainter *painter)
{
    QString target = QString("%1%2")
            .arg(m_cages[cageIndex].get_target_value())
            .arg(m_cages[cageIndex].get_operation());
    QPointF c(center + QPointF(4, 18));

    painter->drawText(c, target);
}

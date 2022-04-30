#include "gridgui.h"

GridGUI::GridGUI(uint8_t gridSize, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_gridSize(gridSize),
      m_cellSize(70)
{

}

uint8_t GridGUI::gridSize() const
{
    return m_gridSize;
}

void GridGUI::setGridSize(const uint8_t gridSize)
{
    if (gridSize != m_gridSize) {
        prepareGeometryChange();
        m_gridSize = gridSize;
    }
}

uint8_t GridGUI::cellSize() const
{
    return m_cellSize;
}

void GridGUI::setCellSize(const uint8_t cellSize)
{
    if (cellSize != m_cellSize) {
        prepareGeometryChange();
        m_cellSize = cellSize;
    }
}

qreal GridGUI::length() const
{
    return qreal(gridSize()) * qreal(cellSize());
}

uint8_t GridGUI::index(uint8_t row, uint8_t col)
{
    return row * gridSize() + col;
}


QRectF GridGUI::boundingRect() const
{
    return QRectF(0, 0, length(), length());
}

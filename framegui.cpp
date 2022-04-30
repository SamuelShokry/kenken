#include "framegui.h"

#include <QPainter>
#include <QPen>

FrameGUI::FrameGUI(uint8_t gridSize, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_gridSize(gridSize),
      m_cellSize(70)
{

}


QRectF FrameGUI::boundingRect() const
{
    return QRectF(0, 0, m_gridSize*m_cellSize, m_gridSize*m_cellSize);
}

void FrameGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::lightGray);

    const qreal length = m_gridSize*m_cellSize;

    const QPointF horStep(0, m_cellSize);
    const QPointF verStep(m_cellSize, 0);

    QPointF horStart(0, 0), horEnd(length, 0);
    QPointF verStart(0, 0), verEnd(0, length);

    for (int i = 0; i <= m_gridSize; ++i) {
        painter->drawLine(horStart, horEnd);
        painter->drawLine(verStart, verEnd);

        horStart += horStep;
        horEnd += horStep;

        verStart += verStep;
        verEnd += verStep;
    }
}

uint8_t FrameGUI::gridSize() const
{
    return m_gridSize;
}

void FrameGUI::setGridSize(const uint8_t gridSize)
{
    if (gridSize != m_gridSize) {
        prepareGeometryChange();
        m_gridSize = gridSize;
    }
}

uint8_t FrameGUI::cellSize() const
{
    return m_cellSize;
}

void FrameGUI::setCellSize(const uint8_t cellSize)
{
    if (cellSize != m_cellSize) {
        prepareGeometryChange();
        m_cellSize = cellSize;
    }
}

#include "gamesolngui.h"

#include <QPainter>

GameSolnGUI::GameSolnGUI(quint8 gridSize, cell *cells, QGraphicsItem *parent)
    : GridGUI(gridSize, parent),
      m_cells(cells)
{

}


void GameSolnGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (m_cells == Q_NULLPTR) return;

    quint8 cellIndex;
    QPointF iter(0, 0);
    const QPointF inX(cellSize(), 0), inY(0, cellSize());

    QFont font = painter->font();
    font.setPixelSize(27);
    painter->setFont(font);

    for (uint8_t i = 0; i < gridSize(); ++i) {
        for (uint8_t j = 0; j < gridSize(); ++j) {
            cellIndex = index(i, j);
            drawValue(cellIndex, iter, iter+inY+inX, painter);
            iter += inX;
        }
        iter += inY;
        iter.setX(0);
    }
}

cell *GameSolnGUI::cells() const
{
    return m_cells;
}

void GameSolnGUI::setCells(quint8 size, cell *cells)
{
    prepareGeometryChange();
    m_gridSize = size;
    m_cells = cells;
}

void GameSolnGUI::drawValue(const quint8 index, const QPointF topleft,
                            const QPointF bottomRight, QPainter *painter)
{
    const int v = m_cells[index].get_cell_value();
    QString value(QString("%1").arg(v));
    assert(v >= 0 && v <= 9);

    QRectF *rect = new QRectF(topleft, bottomRight);
    painter->drawText(*rect, Qt::AlignCenter, value, rect);
}

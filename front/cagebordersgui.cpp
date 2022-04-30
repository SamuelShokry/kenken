#include "cagebordersgui.h"

#include <QPainter>
#include <QVector>
#include <QLine>

CageBordersGUI::CageBordersGUI(uint8_t gridSize, cell *cells, QGraphicsItem *parent)
    : GridGUI(gridSize, parent),
      m_penWidth(4),
      m_cells(cells)
{

}

void CageBordersGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen = painter->pen();
    pen.setColor(Qt::black);
    pen.setWidth(m_penWidth);
    painter->setPen(pen);

    //Draw the main borders
    painter->drawLine(0, 0, length(), 0);   // top horizontal
    painter->drawLine(0, 0, 0, length());   // left veritcal
    painter->drawLine(0, length(), length(), length());   // bottom horizontal
    painter->drawLine(length(), 0, length(), length());   // right veritcal

    if (m_cells == Q_NULLPTR) return;

    //Draw the inline borders
    QPointF iter(cellSize(), cellSize()), inX(cellSize(), 0), inY(0, cellSize());
    QLine line;
    QVector<QLineF> lines;

    int cage, cageRight, cageBottom;
    for (uint8_t i = 0; i < gridSize(); ++i) {
        for (uint8_t j = 0; j < gridSize(); ++j) {
            cage = m_cells[index(i, j)].get_cage_index();

            cageBottom = ((i+1) == gridSize()) ?
                        cage :
                        m_cells[index(i+1, j)].get_cage_index();

            cageRight = ((j+1) == gridSize()) ?
                        cage :
                        m_cells[index(i, j+1)].get_cage_index();

            if (cageBottom != cage)
                lines.push_back(QLineF(iter, iter-inX));

            if (cageRight != cage)
                lines.push_back(QLineF(iter, iter-inY));

            iter += inX;
        }
        iter += inY;
        iter.setX(cellSize());
    }

    painter->drawLines(lines);
}

cell *CageBordersGUI::cells() const
{
    return m_cells;
}

void CageBordersGUI::setCells(cell *cells)
{
    m_cells = cells;
}

void CageBordersGUI::cellChanged()
{
    prepareGeometryChange();
}


QRectF CageBordersGUI::boundingRect() const
{
    static const qreal margin = m_penWidth/2;
    return QRectF(-margin,
                  -margin,
                  length()+margin,
                  length()+margin);
}

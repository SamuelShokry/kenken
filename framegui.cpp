#include "framegui.h"

#include <QPainter>
#include <QPen>

FrameGUI::FrameGUI(uint8_t gridSize, QGraphicsItem *parent)
    : GridGUI(gridSize, parent)
{

}


QRectF FrameGUI::boundingRect() const
{
    return QRectF(0, 0, length(), length());
}

void FrameGUI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::lightGray);

    const QPointF horStep(0, cellSize());
    const QPointF verStep(cellSize(), 0);

    QPointF horStart(0, 0), horEnd(length(), 0);
    QPointF verStart(0, 0), verEnd(0, length());

    for (int i = 0; i <= gridSize(); ++i) {
        painter->drawLine(horStart, horEnd);
        painter->drawLine(verStart, verEnd);

        horStart += horStep;
        horEnd += horStep;

        verStart += verStep;
        verEnd += verStep;
    }
}

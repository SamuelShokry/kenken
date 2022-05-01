#include "gameview.h"

#include <QWheelEvent>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setRenderHints(QPainter::Antialiasing);
}


void GameView::wheelEvent(QWheelEvent *event)
{
    qreal ds = 0.1 * (event->angleDelta().y() > 0 ? 1 : -1);
    scale(1 + ds, 1 + ds);
    event->accept();
}

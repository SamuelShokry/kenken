#ifndef FRAMEGUI_H
#define FRAMEGUI_H

#include <QGraphicsItem>

class FrameGUI : public QGraphicsItem
{
public:
    FrameGUI(uint8_t gridSize = 3, QGraphicsItem *parent = Q_NULLPTR);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    uint8_t gridSize() const;
    void setGridSize(const uint8_t gridSize);

    uint8_t cellSize() const;
    void setCellSize(const uint8_t cellSize);

private:
    uint8_t m_gridSize;
    uint8_t m_cellSize;
};

#endif // FRAMEGUI_H

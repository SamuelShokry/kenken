#ifndef GRIDGUI_H
#define GRIDGUI_H

#include <QGraphicsItem>

class GridGUI : public QGraphicsItem
{
public:
    GridGUI(uint8_t gridSize = 3, QGraphicsItem *parent = Q_NULLPTR);

    uint8_t gridSize() const;
    void setGridSize(const uint8_t gridSize);

    uint8_t cellSize() const;
    void setCellSize(const uint8_t cellSize);

    qreal length() const;

protected:
    uint8_t index(uint8_t row, uint8_t col);

private:
    uint8_t m_gridSize;
    uint8_t m_cellSize;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
};

#endif // GRIDGUI_H

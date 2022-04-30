#ifndef GRIDINFOGUI_H
#define GRIDINFOGUI_H

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

private:
    uint8_t m_gridSize;
    uint8_t m_cellSize;
};

#endif // GRIDINFOGUI_H

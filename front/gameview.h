#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class GameView : public QGraphicsView
{
public:
    GameView(QWidget *parent = Q_NULLPTR);

    // QWidget interface
protected:
    virtual void wheelEvent(QWheelEvent *event) override;
};

#endif // GAMEVIEW_H

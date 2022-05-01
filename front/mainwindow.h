#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "framegui.h"
//#include "cagebordersgui.h"
//#include "targetgui.h"

#include "gamegui.h"

#include "../back/cell.h"
#include "../back/kenken.h"
#include "../back/draw.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //The function generates randomly a gridSize if it is zero
    void generateGame(uint8_t gridSize = 0, operation op = ALL_OPERATIONS);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    uint8_t m_gridSize;

    GameGUI *m_gameGUI;

    kenken *m_game;
    draw y;
};

#endif // MAINWINDOW_H

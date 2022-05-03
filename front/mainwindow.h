#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

//#include "framegui.h"
//#include "cagebordersgui.h"
//#include "targetgui.h"

#include "gamegui.h"

#include "../back/cell.h"
#include "../back/kenken.h"
#include "../back/draw.h"

const QString extension = ".kenken";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum State{NoGame, UnsolvedGame, BeingSolved, SolvedGame};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  

signals:
    void stateChanged();

private slots:
    void generateAction();

    //Different solution methods
    void solveGame();
    void handleSolvedGame();

    //Read & write
    void saveGame();
    void loadGame();

private:
    Ui::MainWindow *ui;
    uint8_t m_gridSize;
    GameGUI *m_gameGUI;
    kenken *m_game;
    draw y;
    State m_state, m_nextState;
    QElapsedTimer m_time;
    int m_elapsed;

    //The function generates randomly a gridSize if it is zero
    void generateGame(uint8_t gridSize = 0, operation op = ALL_OPERATIONS);
    void setGeneratedGame();

    void clearGame();
    void clearSoln();

    //Possible transitions:
    //NoGame --> UnsolvedGame

    //UnsolvedGame --> NoGame
    //UnsolvedGame --> BeingSolved

    //BeingSolved --> SolvedGame

    //SolvedGame --> NoGame
    //SolvedGame --> UnsolvedGame
    void setState(const State state);
    void fsm();
    void setSolveButtonsEnabled(const bool isEnabled);
    void setControlButtonsEnabled(const bool enableGenerate,
                                  const bool enableClearGame,
                                  const bool enableClearSoln);
};

#endif // MAINWINDOW_H

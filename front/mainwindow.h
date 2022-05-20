#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFutureWatcher>
#include <QElapsedTimer>

//#include "framegui.h"
//#include "cagebordersgui.h"
//#include "targetgui.h"

#include "gamegui.h"

#include "../back/cell.h"
#include "../back/kenken.h"
#include "../back/draw.h"
#include "../back/comparator.h"

const QString extension = ".kenken";

typedef QVector<kenken*> GamesArr;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum State{NoGame, UnsolvedGame, BeingSolved, SolvedGame};
    enum CompareState{NoCompare, BeingCompared, Paused, Resumed, Cancelled};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  

signals:
    void stateChanged();
    void stateCompareChanged();

private slots:
    void generateAction();

    //Different solution methods
    void solveGame();
    void handleSolvedGame();

    //Read & write
    void saveGame();
    void loadGame();

    //Compare
    void compareAlgo();
    void handleCompareAlgo();
    void handleNoCompare();
    void handleProgressed(int value);
    void handlePaused();
    void handleResumed();
    void handleCancelled();

private:
    Ui::MainWindow *ui;
    uint8_t m_gridSize;
    GameGUI *m_gameGUI;
    GameGUI *m_gameGUIComp;
    kenken *m_game;
    draw y;
    State m_state, m_nextState;
    QElapsedTimer m_time;
    size_t m_elapsed;
    QFutureWatcher<void> m_watcher, m_watchCompare;

    Comparator m_comparator;
    CompareState m_compareState, m_nextCompareState;

    //The function generates randomly a gridSize if it is zero
    void generateGame(uint8_t gridSize = 0, operation op = ALL_OPERATIONS);
    void setGeneratedGame();

    void clearGame();
    void clearSoln();

    void drawComparedGame(const int value);

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

    void setCompareState(const CompareState state);
    void fsmCompare();

    void setActivateMainGame(const bool enabled);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gridSize(3),
    m_gameGUI(new GameGUI(0, Q_NULLPTR, Q_NULLPTR)),
    m_game(Q_NULLPTR),
    m_state(NoGame),
    m_nextState(NoGame),
    m_elapsed(0)

{
    ui->setupUi(this);

    ui->operationTypeComboBox->addItem("PLUS");
    ui->operationTypeComboBox->addItem("PLUS_MINUS");
    ui->operationTypeComboBox->addItem("TIMES_DIVIDED");
    ui->operationTypeComboBox->addItem("ALL_OPERATIONS");

    ui->graphicsView->setScene(new QGraphicsScene());
    ui->graphicsView->scene()->addItem(m_gameGUI);

    connect(ui->generatePB, &QPushButton::clicked,
            this, &MainWindow::generateAction);
    connect(ui->clearGamePB, &QPushButton::clicked,
            this, &MainWindow::clearGame);
    connect(ui->clearSolnPB, &QPushButton::clicked,
            this, &MainWindow::clearSoln);

    connect(ui->backtrackingPB, &QPushButton::clicked,
            this, &MainWindow::solveGame);
    connect(ui->forwardPB, &QPushButton::clicked,
            this, &MainWindow::solveGame);
    connect(ui->arcPB, &QPushButton::clicked,
            this, &MainWindow::solveGame);

    connect(this, &MainWindow::stateChanged, this, &MainWindow::fsm);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_gameGUI;
    delete m_game;
}

void MainWindow::generateGame(uint8_t gridSize, operation op)
{
    clearGame();

    if (gridSize)
        m_gridSize = gridSize;
    else
        m_gridSize = 3 + rand()%7;

    m_game = new kenken(m_gridSize, op);
    m_game->generate_game();

    QtConcurrent::run(&y, &draw::print, m_game->get_game_grid_ptr());

    m_gameGUI->setGrid(m_gridSize, m_game->get_game_grid_ptr());

    ui->graphicsView->scene()->setSceneRect(0, 0,
                                            m_gameGUI->length(),
                                            m_gameGUI->length());

    setState(UnsolvedGame);
}

void MainWindow::generateAction()
{
    operation op = static_cast<operation>(ui->operationTypeComboBox->currentIndex());
    quint8 size = ui->gameSizeSpinBox->value();

    generateGame(size, op);
}

void MainWindow::solveGame()
{
    setState(BeingSolved);

    //TODO: call the actual solving function
    if (sender() == ui->backtrackingPB) {
        m_time.start();
        QThread::sleep(1);
    } else if (sender() == ui->forwardPB) {
        m_time.start();
        QThread::sleep(2);
    } else if (sender() == ui->arcPB) {
        m_time.start();
        QThread::sleep(3);
    }
    handleSolvedGame();
}

void MainWindow::handleSolvedGame()
{
    m_elapsed = m_time.elapsed();
    m_gameGUI->drawSoln(m_gridSize,
                        m_game->get_game_grid_ptr()->get_cells_ptr());
    setState(SolvedGame);
}

void MainWindow::setSolveButtonsEnabled(const bool isEnabled)
{
    ui->backtrackingPB->setEnabled(isEnabled);
    ui->forwardPB->setEnabled(isEnabled);
    ui->arcPB->setEnabled(isEnabled);
}

void MainWindow::setControlButtonsEnabled(const bool enableGenerate,
                                          const bool enableClearGame,
                                          const bool enableClearSoln)
{
    ui->generatePB->setEnabled(enableGenerate);
    ui->clearGamePB->setEnabled(enableClearGame);
    ui->clearSolnPB->setEnabled(enableClearSoln);
}

void MainWindow::clearGame()
{
    if (m_game)
        delete m_game;

    m_game = nullptr;
    m_gameGUI->setGrid(0, nullptr);

    setState(NoGame);
}

void MainWindow::clearSoln()
{
    //TODO: clear the actual data

    m_gameGUI->drawSoln(0, Q_NULLPTR);
    setState(UnsolvedGame);
}

void MainWindow::setState(const MainWindow::State state)
{
    if (state != m_nextState) {
        m_nextState = state;
        emit stateChanged();
    }
}

void MainWindow::fsm()
{
    assert(m_state != m_nextState);

    switch(m_nextState) {
    case NoGame:
        setSolveButtonsEnabled(false);
        setControlButtonsEnabled(true, false, false);
        if (m_state != NoGame)
            ui->statusBar->showMessage(tr("Game has been cleared"));
        break;

    case UnsolvedGame:
        setSolveButtonsEnabled(true);
        setControlButtonsEnabled(true, true, false);
        if (m_state == SolvedGame)
            ui->statusBar->showMessage(tr("Game solution has been erased"));
        else
            ui->statusBar->showMessage(tr("New game has been generated"));
        break;

    case BeingSolved:
        setSolveButtonsEnabled(false);
        setControlButtonsEnabled(false, false, false);
        ui->statusBar->showMessage("Game is being solved. Please, wait.");
        break;

    case SolvedGame:
        setSolveButtonsEnabled(false);
        setControlButtonsEnabled(true, true, true);
        ui->statusBar->showMessage(tr("Game has been solved in %1 millisecond")
                                   .arg(m_elapsed));
        break;
    }

    m_state = m_nextState;
}

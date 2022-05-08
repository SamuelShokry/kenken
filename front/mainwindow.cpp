#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../back/kenkenwriter.h"
#include "../back/kenkenreader.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QFileDialog>
#include <QMessageBox>

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

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadGame);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveGame);

    connect(&m_watcher, &QFutureWatcher<void>::finished,
            this, &MainWindow::handleSolvedGame);
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
    setGeneratedGame();
}

void MainWindow::setGeneratedGame()
{
    m_gridSize = m_game->get_game_grid_ptr()->get_grid_size();
    QtConcurrent::run(&y, &draw::print, m_game->get_game_grid_ptr());

    m_gameGUI->setGrid(m_gridSize,
                       m_game->get_game_grid_ptr());

    ui->graphicsView->scene()->setSceneRect(0, 0,
                                            m_gameGUI->length(),
                                            m_gameGUI->length());

    if (m_game->get_is_solved()) {
        handleSolvedGame();
        setState(SolvedGame);
    }
    else
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

    if (sender() == ui->backtrackingPB) {
        m_time.start();
        m_watcher.setFuture(QtConcurrent::run(m_game, &kenken::solve, BACKTRACKING));
    } else if (sender() == ui->forwardPB) {
        m_time.start();
        m_watcher.setFuture(QtConcurrent::run(m_game, &kenken::solve, BACKTRACKING_WITH_FORWARD_CHECKING));
    } else if (sender() == ui->arcPB) {
        m_time.start();
        QThread::sleep(3);  //TODO: call the actual solving function
    }
}

void MainWindow::handleSolvedGame()
{
    m_elapsed = m_time.elapsed();
    m_gameGUI->drawSoln(m_gridSize,
                        m_game->get_game_grid_ptr()->get_cells_ptr());
    setState(SolvedGame);
}

void MainWindow::saveGame()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Choose where to save"),
                                                    QString(),
                                                    tr("*") + extension);

    if (!filename.isEmpty()) {
        filename += extension;
        KenkenWriter writer;
        QString err;
        err.fromStdString(writer.write(*m_game, filename.toStdString()));

        if (!err.isEmpty()) {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 err);
        } else {
            ui->statusBar->showMessage("Game has been saved successfully");
        }
    }
}

void MainWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Choose a game to load"),
                                                    QString(),
                                                    tr("*") + extension);
    if (!filename.isEmpty()) {
        KenkenReader reader;
        QString err;
        kenken *game = new kenken(0, PLUS);
        err.fromStdString(reader.read(*game, filename.toStdString()));

        if (!err.isEmpty()) {
            QMessageBox::warning(this,
                                 tr("Error"),
                                 err);
        } else {
            ui->statusBar->hide();
            if (m_state != NoGame)
                clearGame();
            m_game = game;
            setGeneratedGame();
            ui->statusBar->showMessage("Game has been loaded successfully");
            ui->statusBar->show();
        }
    }
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
    m_game->clear_solution();
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

        ui->actionSave_as->setEnabled(false);
        ui->actionOpen->setEnabled(true);

        if (m_state != NoGame)
            ui->statusBar->showMessage(tr("Game has been cleared"));
        break;

    case UnsolvedGame:
        setSolveButtonsEnabled(true);
        setControlButtonsEnabled(true, true, false);

        ui->actionSave_as->setEnabled(true);
        ui->actionOpen->setEnabled(true);

        if (m_state == SolvedGame)
            ui->statusBar->showMessage(tr("Game solution has been erased"));
        else
            ui->statusBar->showMessage(tr("New game has been generated"));
        break;

    case BeingSolved:
        setSolveButtonsEnabled(false);
        setControlButtonsEnabled(false, false, false);

        ui->actionOpen->setEnabled(false);
        ui->actionSave_as->setEnabled(false);

        ui->statusBar->showMessage("Game is being solved. Please, wait.");
        break;

    case SolvedGame:
        setSolveButtonsEnabled(false);
        setControlButtonsEnabled(true, true, true);

        ui->actionOpen->setEnabled(true);
        ui->actionSave_as->setEnabled(true);

        ui->statusBar->showMessage(tr("Game has been solved in %1 millisecond")
                                   .arg(m_elapsed));
        break;
    }

    m_state = m_nextState;
}

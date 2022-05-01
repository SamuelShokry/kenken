#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gridSize(3),
    m_gameGUI(new GameGUI(0, Q_NULLPTR, Q_NULLPTR)),
    m_game(new kenken(m_gridSize, ALL_OPERATIONS))
{
    ui->setupUi(this);
    m_game->generate_game();

    ui->graphicsView->setScene(new QGraphicsScene());

    m_gameGUI->setGrid(m_gridSize, m_game->get_game_grid_ptr());
    ui->graphicsView->scene()->addItem(m_gameGUI);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_gameGUI;
    delete m_game;
}

void MainWindow::generateGame(uint8_t gridSize, operation op)
{
    if (m_game)
        delete m_game;

    if (gridSize)
        m_gridSize = gridSize;
    else
        m_gridSize = 3 + rand()%7;

    m_game = new kenken(m_gridSize, op);
    m_game->generate_game();

    QtConcurrent::run(&y, &draw::print, m_game->get_game_grid_ptr());

    m_gameGUI->setGrid(m_gridSize, m_game->get_game_grid_ptr());

    ui->graphicsView->centerOn(m_gameGUI->length()/2, m_gameGUI->length()/2);
}

void MainWindow::on_pushButton_clicked()
{
    generateGame();
}

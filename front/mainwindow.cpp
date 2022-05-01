#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gridSize(3),
    m_game(new kenken(m_gridSize, ALL_OPERATIONS))
{
    ui->setupUi(this);
    m_game->generate_game();

    ui->graphicsView->setScene(new QGraphicsScene());

    m_frame = new FrameGUI(m_gridSize);
    m_cageBorders = new CageBordersGUI(m_gridSize, m_game->get_game_grid_ptr()->get_cells_ptr());
    m_targets = new TargetGUI(m_gridSize,
                              m_game->get_game_grid_ptr()->get_cages_ptr(),
                              m_game->get_game_grid_ptr()->get_cells_ptr());

    ui->graphicsView->scene()->addItem(m_frame);
    ui->graphicsView->scene()->addItem(m_cageBorders);
    ui->graphicsView->scene()->addItem(m_targets);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_frame;
    delete m_cageBorders;
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

    m_frame->setGridSize(m_gridSize);

    m_cageBorders->setGridSize(m_gridSize);
    m_cageBorders->setCells(m_game->get_game_grid_ptr()->get_cells_ptr());

    m_targets->setGridSize(m_gridSize);
    m_targets->setCages(m_game->get_game_grid_ptr()->get_cages_ptr());
    m_targets->setCells(m_game->get_game_grid_ptr()->get_cells_ptr());

    ui->graphicsView->centerOn(m_frame->length()/2, m_frame->length()/2);
}

void MainWindow::on_pushButton_clicked()
{
    generateGame();
}

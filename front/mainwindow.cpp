#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_game(new kenken(3, ALL_OPERATIONS))
{
    ui->setupUi(this);
    srand (time(NULL));

    int m_gridSize = 3;
    m_game->generate_game();

//    y.print(m_game.get_game_grid_ptr());
    QtConcurrent::run(&y, &draw::print, m_game->get_game_grid_ptr());

    ui->graphicsView->setScene(new QGraphicsScene());

    m_frame = new FrameGUI(m_gridSize);
    m_cageBorders = new CageBordersGUI(m_gridSize, m_game->get_game_grid_ptr()->get_cells_ptr());

    ui->graphicsView->scene()->addItem(m_frame);
    ui->graphicsView->scene()->addItem(m_cageBorders);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_frame;
    delete m_cageBorders;
}

void MainWindow::on_pushButton_clicked()
{
//    ui->graphicsView->scene()->clear();
    delete m_game;

    int size = (3 + (rand() % 6));
//    int size = 7;
    m_game = new kenken(size, ALL_OPERATIONS);
    m_game->generate_game();

//    QtConcurrent::run(&y, &draw::print, m_game->get_game_grid_ptr());

    m_frame->setGridSize(size);
    m_cageBorders->setGridSize(size);
    m_cageBorders->setCells(m_game->get_game_grid_ptr()->get_cells_ptr());

//    ui->graphicsView->scene()->addItem(m_frame);
//    ui->graphicsView->scene()->addItem(m_cageBorders);
}

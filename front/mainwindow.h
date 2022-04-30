#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "framegui.h"
#include "cagebordersgui.h"

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    FrameGUI *m_frame;
    CageBordersGUI *m_cageBorders;

    kenken *m_game;
    draw y;
};

#endif // MAINWINDOW_H

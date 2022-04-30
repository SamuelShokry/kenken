#define GUI

#ifdef GUI
#include "front/mainwindow.h"
#include <QApplication>
#else
#include "back/kenken.h"
#include "back/draw.h"
#endif

/*---------------- Operations Categories ------------------
 *  1- PLUS
 *  2- PLUS_MINUS
 *  3- TIMES_DIVIDED
 *  4- ALL_OPERATIONS
 * */

int main(int argc, char *argv[])
{
#ifdef GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
#else
    srand (time(NULL));
    int Size = (3 + (rand() % 6));
    kenken x(Size, ALL_OPERATIONS);
    x.generate_game();
    draw y;
    y.print(x.get_game_grid_ptr());
    x.delete_game();

    return 0;
#endif
}

//#define GUI

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
    std::cout << "Started\n";
    srand (time(NULL));
    int Size;
    for(int i=0; i<100; i++)
    {
        std::cout << "i = " << i << std::endl;
        Size = 3;
        draw y;
        kenken x(Size, ALL_OPERATIONS);
        x.generate_game();
        x.solve(BACKTRACKING);
        y.print(x.get_game_grid_ptr());
        x.clear_solution();     /* Used to clear the solution before using another technique. */
        x.delete_game();
        std::cout << std::endl;
    }

    return 0;
#endif
}

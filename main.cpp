#define GUI
//#define CONSOLE
//#define TEST_CORRECTNESS

#ifdef GUI
#include "front/mainwindow.h"
#include <QApplication>
#else
#include "back/kenken.h"
#include "back/draw.h"
#include "back/kenkenreader.h"
#include "back/kenkenwriter.h"
#include "back/comparator.h"

#include <QThread>
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
    srand (0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
#endif

#ifdef CONSOLE
    std::cout << "Started\n";
    srand (0);
    int Size;

    double t1 =0, t2 =0, t3 =0;
    clock_t c1 = 0, c2 = 0;

    for(int i=0; i<100; i++)
    {
        std::cout << "i = " << i << std::endl;
        Size = 9;
        draw y;
        kenken x(Size, ALL_OPERATIONS);
        x.generate_game();
        printf("Game generated\n");
        std::cout << std::flush;
        //First Method
        c1 = clock();
        x.solve(BACKTRACKING);
        c2 = clock();
        t1 += ((double(c2 - c1)*1000)/CLOCKS_PER_SEC);
        x.clear_solution(); //clear the solution.

        //second Method
        c1 = clock();
        x.solve(BACKTRACKING_WITH_FORWARD_CHECKING);
        c2 = clock();
        t2 += ((double(c2 - c1)*1000)/CLOCKS_PER_SEC);
        x.clear_solution(); //clear the solution.

        // second Method/
        c1 = clock();
        x.solve(BACKTRACKING_WITH_FORWARDCHECKING_AND_ARC_CONSISTENCY);
        c2 = clock();
        t3 += ((double(c2 - c1)*1000)/CLOCKS_PER_SEC);

        y.print(x.get_game_grid_ptr());
        printf("t1 = %lf, t2 = %lf, t3 = %lf\n", t1, t2, t3);
        x.delete_game();
        //		std::cout << std::endl;
    }

    std::cout << "-------------------------- Finish ------------------------------" << std::endl;
    std::cout << "Backtracking Time = " << t1 << std::endl;
    std::cout << "Backtracking with Forward Time = " << t2 << std::endl;
    std::cout << "Backtracking with Forward and Arc Consistabcy Time = " << t3 << std::endl;
#endif

#ifdef TEST_CORRECTNESS

    KenkenReader reader;
    KenkenWriter writer;
    Comparator comp;
    Modes modes;
    QFutureWatcher<void> watcher;
    double results[MODES_COUNT];

    for (int Size = 3; Size < 10; ++Size) {
        for (int i = 0; i < 100; ++i) {
            for (int op = 0; op < 4; ++op) {
                //                printf("i=%d, Size=%d, op=%d\n", i, Size, op);
                //                std::cout << std::flush;


                for (int j = 1; j <= 3; ++j) {
                    printf("i=%d, Size=%d, op=%d, j =%d\n", i, Size, op, j);
                    std::cout << std::flush;

                    modes[0] = (j&1) != 0;
                    modes[1] = (j&2) != 0;
                    modes[2] = (j&4) != 0;

                    comp.setCount(i+1);
                    comp.setOp(static_cast<operation>(op));
                    comp.setSize(Size);
                    comp.setModes(modes);


                    comp.compare(watcher);
                    watcher.future().waitForFinished();
                    assert(watcher.future().isFinished());
                    //                    do {
                    //                        watcher.future().waitForFinished();
                    //                        std::cout << watcher.future().isFinished() << "\n" << std::flush;
                    //                    } while (!watcher.future().isFinished());

                    comp.aggregateResults(results);

                    for (size_t k = 0; k < MODES_COUNT; ++k) {
                        if (comp.modes()[k]) {
                            QString msg = QString("It took %1 seconds").arg(results[k]);
                            msg += " to solve the required games using ";
                            if (k == 0)
                                msg += "Backtracing";
                            if (k == 1)
                                msg += "Backtracing with Forward Checking";
                            if (k == 2)
                                msg += "Backtracing with Forward Checking and Arc Consistency";
                            std::cout << msg.toStdString() << "\n" << std::flush;
                        }
                    }

                    comp.clear();
                }

                kenken x(Size, static_cast<operation>(op));

                x.generate_game();

                writer.write(x, "test.kenken");
                x.delete_game();

                reader.read(x, "test.kenken");

                //First Method
                x.solve(BACKTRACKING);
                x.clear_solution(); //clear the solution.

                // second Method/
                x.solve(BACKTRACKING_WITH_FORWARD_CHECKING);
                x.clear_solution(); //clear the solution.

                x.delete_game();
            }
        }
    }
#endif

    return 0;
}

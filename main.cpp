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
#endif

#ifdef CONSOLE
	std::cout << "Started\n";
    srand (0);
	int Size;

	double t1 =0, t2 =0;
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

		// second Method/
		c1 = clock();
		x.solve(BACKTRACKING_WITH_FORWARD_CHECKING);
		c2 = clock();
		t2 += ((double(c2 - c1)*1000)/CLOCKS_PER_SEC);
        y.print(x.get_game_grid_ptr());
        printf("t1 = %lf, t2 = %lf\n", t1, t2);
		x.delete_game();
//		std::cout << std::endl;
	}

	std::cout << "-------------------------- Finish ------------------------------" << std::endl;
	std::cout << "Backtracking Time = " << t1 << std::endl;
	std::cout << "Backtracking with Forward Time = " << t2 << std::endl;
#endif

#ifdef TEST_CORRECTNESS

    KenkenReader reader;
    KenkenWriter writer;

    for (int Size = 3; Size < 10; ++Size) {
        for (int i = 0; i < 100; ++i) {
            for (int op = 0; op < 4; ++op) {
                printf("i=%d, Size=%d, op=%d\n", i, Size, op);
                std::cout << std::flush;

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

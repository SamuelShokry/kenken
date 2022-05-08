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

	double t1 =0, t2 =0;
	clock_t c1 = 0, c2 = 0;

	for(int i=0; i<100; i++)
	{
		std::cout << "i = " << i << std::endl;
		Size =3;
		draw y;
		kenken x(Size, ALL_OPERATIONS);
		x.generate_game();
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
		x.delete_game();
		std::cout << std::endl;
	}

	std::cout << "-------------------------- Finish ------------------------------" << std::endl;
	std::cout << "Backtracking Time = " << t1 << std::endl;
	std::cout << "Backtracking with Forward Time = " << t2 << std::endl;

	return 0;
#endif
}

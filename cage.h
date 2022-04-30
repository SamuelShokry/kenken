#ifndef CAGE_H_
#define CAGE_H_

#include "cell.h"

class cage
{
private:
	int numberOfCells;		//number of cells in the cage.
	int	targetValue;		//target value of the cage.
	cell** cageCells;   	//array of pointers to the grid cells included in the cage.
	char operation;			//the operation that will be done in the cage.
	int firstCellInCage;  	//index of the first cell in this cage (used for printing the target value and the operation).

public:
	void set_number_of_cells(int n);

	void set_target_value(int n);

	void set_operation(char op);

	void set_cage_cell_value(int index, int value);

	void set_cage_cell_ptr(int index, cell* ptr);

	void set_first_cell_in_cage(int index);

	int get_number_of_cells(void);

	int get_target_value(void);

	char get_operation(void);

	int get_cage_cell_value(int index);

	int get_first_cell_in_cage(void);

	bool cheak_cage(void);

	void delete_cage_cells_Ptr(void);

};




#endif /* CAGE_H_ */

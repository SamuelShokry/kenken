#include "cage.h"


void cage::set_number_of_cells(int n)
{
	numberOfCells = n;
	cageCells = new cell*[numberOfCells];
}

void cage::set_target_value(int n)
{
	targetValue = n;
}

void cage::set_operation(char op)
{
	operation = op;
}

void cage::set_cage_cell_value(int index, int value)
{
	cageCells[index]->set_cell_value(value);
}

void cage::set_cage_cell_ptr(int index, cell* ptr)
{
	cageCells[index] = ptr;
}

void cage::set_first_cell_in_cage(int index)
{
	firstCellInCage = index;
}

int cage::get_number_of_cells(void)
{
	return numberOfCells;
}

int cage::get_target_value(void)
{
	return targetValue;
}

char cage::get_operation(void)
{
	return operation;
}

int cage::get_cage_cell_value(int index)
{
	return cageCells[index]->get_cell_value();
}

int cage::get_first_cell_in_cage(void)
{
	return firstCellInCage;
}

bool cage::cheak_cage(void)
{
	int temp = 0;
	for(int i=0; i<numberOfCells; i++)
	{
		switch(operation)
		{
			case '+':
				temp += cageCells[i]->get_cell_value();
				break;
			case '-':
				temp -= cageCells[i]->get_cell_value();
				break;
			case '*':
				temp *= cageCells[i]->get_cell_value();
				break;
			case '/':
				if(cageCells[i]->get_cell_value() != 0)
				{
					temp /= cageCells[i]->get_cell_value();;
				}
				break;
		}
	}

	if(temp == targetValue)
		return true;
	else
		return false;
}

void cage::delete_cage_cells_Ptr(void)
{
	delete cageCells;
}

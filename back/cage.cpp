#include "cage.h"


void cage::set_number_of_cells(int n)
{
	numberOfCells = n;
	cageCells = new cell*[numberOfCells];
    for (int i = 0; i < n; ++i) {
        cageCells[i] = nullptr;
    }
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

int cage::get_number_of_cells(void) const
{
	return numberOfCells;
}

int cage::get_target_value(void) const
{
	return targetValue;
}

char cage::get_operation(void) const
{
	return operation;
}

int cage::get_cage_cell_value(int index)
{
	return cageCells[index]->get_cell_value();
}

int cage::get_first_cell_in_cage(void) const
{
    return firstCellInCage;
}

cell **cage::get_cage_cells_ptr() const
{
    return cageCells;
}

bool cage::cheak_cage(void)
{
	int temp;
	int filledCells = 0;

	if(operation == '+')
	{
		temp = 0;

		for(int i=0; i<numberOfCells; i++)
		{
			int value = cageCells[i]->get_cell_value();

			if(value == 0)
			{
				continue;
			}
			temp += value;
			filledCells ++;
		}

		if(filledCells == numberOfCells)
		{
			if(temp != targetValue)
				return false;
		}
		else
		{
			if(temp >= targetValue)
			{
				return false;
			}
		}
	}
	else if(operation == '*')
	{
		temp = 1;

		for(int i=0; i<numberOfCells; i++)
		{
			int value = cageCells[i]->get_cell_value();

			if(value == 0)
			{
				continue;
			}
			temp *= value;
			filledCells ++;
		}

		if(filledCells == numberOfCells)
		{
			if(temp != targetValue)
				return false;
		}
		else
		{
			if(temp > targetValue)
			{
				return false;
			}
		}
	}
	else if(operation == '-')
	{
		int value1 = cageCells[0]->get_cell_value();
		int value2 = cageCells[1]->get_cell_value();

		if(value1 != 0 && value2 != 0)
		{
			if(abs(value1 - value2) != targetValue)
			{
				return false;
			}
		}
	}
	else if(operation == '/')
	{
		int value1 = cageCells[0]->get_cell_value();
		int value2 = cageCells[1]->get_cell_value();

		if(value1 != 0 && value2 != 0)
		{
			int division = std::max(value1, value2) / std::min(value1, value2);
			int reminder =  std::max(value1, value2) % std::min(value1, value2);

			if(division == targetValue && reminder == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if(targetValue != cageCells[0]->get_cell_value())
		{
			return false;
		}
	}

	return true;
}

void cage::delete_cage_cells_Ptr(void)
{
    if (cageCells) {
//        for (int i = 0; i < numberOfCells; ++i)
//            if (cageCells[i])
//                delete cageCells[i];
//        std::cout << "deleting cageCells in delete_cage_cells_Ptr\n";
        delete[] cageCells;
        cageCells = nullptr;
    }
}

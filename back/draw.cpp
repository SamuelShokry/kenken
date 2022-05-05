#include "draw.h"

#define ROW_MAXIMIZE 3
#define COLUMN_MAXIMIZE 6

bool check_target_value_position(grid* x, int row, int col, bool* printedArray, int* targetValue)
{

	cell* cells = x->get_cells_ptr();
	cage* grid_cages = x->get_cages_ptr();

	if(grid_cages[cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()].get_first_cell_in_cage() ==
			((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE))
	{
		if(printedArray[cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()] == false)
		{
			std::cout << grid_cages[cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()].get_target_value();
			std::cout << grid_cages[cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()].get_operation();

			printedArray[cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()] = true;

			*targetValue = grid_cages[cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()].get_target_value();

			return true;
		}
	}
	return false;
}

void draw::print(grid* x)
{
	cell* cells = x->get_cells_ptr();

	bool *printedUnsolvedArray = new bool[x->get_number_of_cages()];
	bool *printedSolvedArray = new bool[x->get_number_of_cages()];

	int rowValueIndex = ROW_MAXIMIZE/2;
	int colValueIndex;

	if(ROW_MAXIMIZE % 2 == 0)
	{
		rowValueIndex -=1;
	}

	for(int i=0; i<x->get_number_of_cages(); i++)
	{
		printedUnsolvedArray[i] = false;
		printedSolvedArray[i] = false;
	}

	std::cout << "Size: " << x->get_grid_size() << "x" << x->get_grid_size() << std::endl;

	std::cout << "number of cages: " << x->get_number_of_cages() << std::endl;

	std::cout << "Cages: ";
	for(int i=0; i< x->get_number_of_cages(); i++)
		std::cout << x->get_cages_ptr()[i].get_number_of_cells() << " ";

	std::cout << std::endl;

	/*---------------------------- Grid Printing ------------------------------------------*/
	for(int i=0; i<= x->get_grid_size() * COLUMN_MAXIMIZE; i++)
	{
		std::cout << "_";
	}

	std::cout << "      ";

	for(int i=0; i<= x->get_grid_size() * COLUMN_MAXIMIZE; i++)
	{
		std::cout << "_";
	}

	/*---------------------------------- Unsolved Grid -----------------------------------------*/
	for(int row = 0; row < x->get_grid_size() * ROW_MAXIMIZE; row++)
	{
		std::cout << std::endl;
		std::cout << "|";

		for(int col =0; col < (x->get_grid_size() * COLUMN_MAXIMIZE); col++)
		{
			int target_value;

			if(check_target_value_position(x, row, col, printedUnsolvedArray, &target_value))
			{
				col++;

				if(target_value > 999999)
				{col+=6;}
				else if(target_value > 99999)
				{col+=5;}
				else if(target_value > 9999)
				{col+=4;}
				else if(target_value > 999)
				{col+=3;}
				else if(target_value > 99)
				{col += 2;}
				else if(target_value > 9)
				{col++;}
			}
			/* Last Column */
			else if((col+1) == (x->get_grid_size() * COLUMN_MAXIMIZE))
			{
				std::cout << "|";
			}
			/*Middle Columns*/
			else if((col+1) % COLUMN_MAXIMIZE == 0)
			{
				if((cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + ((col+1)/COLUMN_MAXIMIZE)].get_cage_index() ==
						cells[(row/ROW_MAXIMIZE) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()))
				{
					/* Last Row */
					if((row + 1) == (x->get_grid_size() * ROW_MAXIMIZE))
					{
						std::cout << "_";
					}
					/* Middle Rows */
					else if((row + 1) % ROW_MAXIMIZE == 0)
					{
						if((cells[((row/ROW_MAXIMIZE)+1) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index() ==
								cells[(row/ROW_MAXIMIZE) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()))
						{
							std::cout << " ";
						}
						else
						{
							std::cout << "_";
						}
					}
					else
					{
						std::cout << " ";
					}
				}
				else
				{
					std::cout << "|";
					if(check_target_value_position(x, row, col+1, printedUnsolvedArray, &target_value))
					{
						col+=2;

						if(target_value > 999999)
						{col+=6;}
						else if(target_value > 99999)
						{col+=5;}
						else if(target_value > 9999)
						{col+=4;}
						else if(target_value > 999)
						{col+=3;}
						else if(target_value > 99)
						{col += 2;}
						else if(target_value > 9)
						{col++;}
					}
				}
			}
			else
			{
				/* Middle Rows */
				if((row + 1) % ROW_MAXIMIZE == 0)
				{
					if((cells[((row/ROW_MAXIMIZE)+1) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index() ==
							cells[(row/ROW_MAXIMIZE) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()))
					{
						std::cout << " ";
					}
					else
					{
						std::cout << "_";
					}
				}
				else
				{
					std::cout << " ";
				}
			}
		}

		/*------------------------------------ Solved Grid -----------------------------------------------*/

		std::cout << "      |";

		colValueIndex = COLUMN_MAXIMIZE/2;
		if(COLUMN_MAXIMIZE % 2 == 0)
		{
			colValueIndex -=1;
		}

		for(int col =0; col < (x->get_grid_size() * COLUMN_MAXIMIZE); col++)
		{
			int target_value;
			if(rowValueIndex == row && colValueIndex == col)
			{
				std::cout << cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + ((col+1)/COLUMN_MAXIMIZE)].get_cell_value();
				colValueIndex += COLUMN_MAXIMIZE;
			}
			else if(check_target_value_position(x, row, col, printedSolvedArray, &target_value))
			{
				col++;

				if(target_value > 999999)
				{col+=6;}
				else if(target_value > 99999)
				{col+=5;}
				else if(target_value > 9999)
				{col+=4;}
				else if(target_value > 999)
				{col+=3;}
				else if(target_value > 99)
				{col += 2;}
				else if(target_value > 9)
				{col++;}
			}
			/* Last Column */
			else if((col+1) == (x->get_grid_size() * COLUMN_MAXIMIZE))
			{
				std::cout << "|";
			}
			/*Middle Columns*/
			else if((col+1) % COLUMN_MAXIMIZE == 0)
			{
				if((cells[((row/ROW_MAXIMIZE)) * x->get_grid_size() + ((col+1)/COLUMN_MAXIMIZE)].get_cage_index() ==
						cells[(row/ROW_MAXIMIZE) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()))
				{
					/* Last Row */
					if((row + 1) == (x->get_grid_size() * ROW_MAXIMIZE))
					{
						std::cout << "_";
					}
					/* Middle Rows */
					else if((row + 1) % ROW_MAXIMIZE == 0)
					{
						if((cells[((row/ROW_MAXIMIZE)+1) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index() ==
								cells[(row/ROW_MAXIMIZE) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()))
						{
							std::cout << " ";
						}
						else
						{
							std::cout << "_";
						}
					}
					else
					{
						std::cout << " ";
					}
				}
				else
				{
					std::cout << "|";
					if(check_target_value_position(x, row, col+1, printedSolvedArray, &target_value))
					{
						col+=2;

						if(target_value > 999999)
						{col+=6;}
						else if(target_value > 99999)
						{col+=5;}
						else if(target_value > 9999)
						{col+=4;}
						else if(target_value > 999)
						{col+=3;}
						else if(target_value > 99)
						{col += 2;}
						else if(target_value > 9)
						{col++;}
					}
				}
			}
			else
			{
				/* Middle Rows */
				if((row + 1) % ROW_MAXIMIZE == 0)
				{
					if((cells[((row/ROW_MAXIMIZE)+1) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index() ==
							cells[(row/ROW_MAXIMIZE) * x->get_grid_size() + (col/COLUMN_MAXIMIZE)].get_cage_index()))
					{
						std::cout << " ";
					}
					else
					{
						std::cout << "_";
					}
				}
				else
				{
					std::cout << " ";
				}
			}
		}
		if(row > rowValueIndex)
		{
			rowValueIndex += ROW_MAXIMIZE;
		}
	}
	std::cout << std::endl;
    std::cout << std::flush;    // to ensure that the entire game is printed
	delete(printedUnsolvedArray);
}


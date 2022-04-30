#include "grid.h"

void grid::set_grid_size(int s)
{
	gridSize = s;
}

int grid::get_grid_size(void)
{
	return gridSize;
}

int grid::get_number_of_cages(void)
{
	return numberOfCages;
}

cage* grid::get_cages_ptr(void)
{
	return cages;
}

cell* grid::get_cells_ptr(void)
{
	return gridCells;
}

void grid::generate_grid(void)
{
	/********************* Grid class initialization. *****************/
	/* Initialize the number of cages to be a random value between
	 * the size of the grid and 2 x size of the grid. */
	numberOfCages = 2 * gridSize + (rand() % (gridSize));
	cages = new cage[numberOfCages];
	gridCells = new cell[gridSize*gridSize];

	//Array to hold the size of each cage.
	int tempArray[gridSize*gridSize]; /* = new int[numberOfCages] */;
	//Variable to hold the remaining number of unused cells.
	//At the beginning each cage has one cell.
	int remainingGridSize = (gridSize * gridSize);
	//Variable to hold the random number of cells to the current cage.
	int cageCellsRandomSize;
	//Variable used to count the number of used cells by the cages.
	int deservedCellsCounter =0;
	//counter to avoid infinite loop.
	int infinite = 0;

	/****************** Cage cells number generation *****************/
	//Initialize the temp array with the one cell it owns.
	for(int i=0; i<numberOfCages; i++)
	{

		if(i < (gridSize * gridSize) / 3)
		{
			tempArray[i] = 2;
			remainingGridSize -= 2;
		}
		else
		{
			tempArray[i] = 1;
			remainingGridSize -= 1;
		}
	}

	for(int i=0; i<(gridSize * gridSize) / 3; i+=2)
	{
		int swapVar = tempArray[i];
		tempArray[i] = tempArray[numberOfCages - i -1];
		tempArray[numberOfCages - i -1] = swapVar;
	}

	//Distribute the remaining cells randomly through the cages.
	while(remainingGridSize != 0)
	{
		int index;
		//generate the random cage cells number.
		cageCellsRandomSize = 1 + (rand() % std::min(remainingGridSize, 5));

		infinite = 0;
		do
		{
			index = rand() % numberOfCages;
			infinite ++;
			if(infinite == 20)
			{
				index = (index + 1) % numberOfCages;
				break;
			}
		}while((tempArray[index] + cageCellsRandomSize) > 6);

		tempArray[index] += cageCellsRandomSize;
		remainingGridSize -= cageCellsRandomSize;
	}
	//loop through all cages.
	for(int i=0; i<numberOfCages; i++)
	{
		/* Variables to navigate through the grid in Zizag shape. */
		int rowIndex = 0;
		int columnIndex =0;
		int cellIndex = 0;

		//initializing the cage:
		cages[i].set_number_of_cells(tempArray[i]);

		//determining of the cage cells.
		for(int j=0; j<tempArray[i]; j++)
		{
			rowIndex = deservedCellsCounter / gridSize;
			columnIndex = deservedCellsCounter % gridSize;
			if(rowIndex % 2 == 0)
			{
				cellIndex = (rowIndex * gridSize) + columnIndex;
			}
			else
			{
				cellIndex = (rowIndex * gridSize) + gridSize - columnIndex -1;
			}

			if(j==0)
			{
				if(rowIndex % 2 == 0)
				{
					cages[i].set_first_cell_in_cage(cellIndex);
				}
				else
				{
					int t = (cellIndex%gridSize) + 1 - tempArray[i];
					if(t <0)
					{
						cages[i].set_first_cell_in_cage(rowIndex * gridSize);
					}
					else
					{
						cages[i].set_first_cell_in_cage(rowIndex * gridSize + t);
					}
				}
			}
			//make the cage pointers points to the desired cells.
			cages[i].set_cage_cell_ptr(j, gridCells + cellIndex);
			//set the current cell's cage index.
			gridCells[cellIndex].set_cage_index(i);
			deservedCellsCounter ++;
		}
	}

	//delete tempArray;
}

void grid::delete_grid(void)
{
    if (cages) {
        delete[] cages;
        cages = nullptr;
    }
    if (gridCells) {
        delete[] gridCells;
        gridCells = nullptr;
    }
}

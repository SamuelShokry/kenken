#include "kenken.h"

kenken::kenken(int gameSize, operation op)
{
	gameGrid.set_grid_size(gameSize);
	gameOperation.set_category_name(op);
    isSolved = false;
}

void kenken::set_is_solved(bool flag)
{
    isSolved = flag;
}

grid* kenken::get_game_grid_ptr (void)
{
	return &gameGrid;
}

operationsCategory* kenken::get_game_operation_ptr(void)
{
	return &gameOperation;
}

bool kenken::get_is_solved()
{
    return isSolved;
}

void kenken::generate_game(void)
{
    /* Generate a new grid to be used in the game. */
    gameGrid.generate_grid();

	/* variables to get the grid data. */
	int gameSize = gameGrid.get_grid_size();
	cell* cellPtr = gameGrid.get_cells_ptr();
	cage* cagePtr =gameGrid.get_cages_ptr();

	/* choosing a random row index to start from it. */
	int startrowIndex = rand() % gameSize;
	/* choosing a random column index in the first row to start from it. */
	int* randomColArrIndex= new int[gameSize];
	/* Iterators to loop through all rows and columns. */
	int rowIterator = 0;
	int columnIterator = 0;
	/* Row array of random distinct values. */
	int* randomRowArrValues = new int[gameSize];

	/* Initialize the random raw from 1 to the grid size. */
	for(int i=1; i<=gameSize; i++)
	{
		randomRowArrValues[i-1] = i;
		randomColArrIndex[i-1] = i-1;

	}
	/* Generate a random distinct row values and a random distinct column index. */
	for(int i=0; i< gameSize; i++)
	{
		/* Pick a random number r between i and game size */
		int r = i + rand() % (gameSize - i);
		/* Swap randomRowArr[r] and randomRowArr[i] */
		int temp = randomRowArrValues[r];
		randomRowArrValues[r] = randomRowArrValues[i];
		randomRowArrValues[i] = temp;

		r = i + rand() % (gameSize - i);
		temp = randomColArrIndex[r];
		randomColArrIndex[r] = randomColArrIndex[i];
		randomColArrIndex[i] = temp;
	}

	/* Fill the Grid with a random distinct values. */
	for(int row = startrowIndex; rowIterator < gameSize; row = (row+1) % gameSize)
	{
		columnIterator = 0;
		for(int col = randomColArrIndex[rowIterator]; columnIterator < gameSize; col = (col+1) % gameSize)
		{
			cellPtr[(row * gameSize) + col].set_cell_value(randomRowArrValues[columnIterator]);
			columnIterator++;
		}
		rowIterator++;
	}

	/* Fill each cage with its target value. */
	for(int cageIndex =0; cageIndex < gameGrid.get_number_of_cages(); cageIndex++)
	{
		int minValue, maxValue;
		char op = gameOperation.get_random_operation(cagePtr[cageIndex].get_number_of_cells());
		int value = cagePtr[cageIndex].get_cage_cell_value(0);

		for (int i = 1; i < cagePtr[cageIndex].get_number_of_cells(); i++)
		{
			switch(op)
			{
			case '+':
				value += cagePtr[cageIndex].get_cage_cell_value(i);
				break;
			case '-':
				value = abs(value - cagePtr[cageIndex].get_cage_cell_value(i));
				break;
			case '*':
				value *= cagePtr[cageIndex].get_cage_cell_value(i);
				break;
			case '/':
				minValue = std::min(value, cagePtr[cageIndex].get_cage_cell_value(i));
				maxValue = std::max(value, cagePtr[cageIndex].get_cage_cell_value(i));
				if(maxValue % minValue == 0)
				{
					value = maxValue / minValue;
				}
				else
				{
					value = minValue * maxValue;
					op = '*';
				}
				break;
			default:
				value = cagePtr[cageIndex].get_cage_cell_value(i);
			}
		}

		cagePtr[cageIndex].set_operation(op);

		if(value == 0)
		{
			for (int i = 0; i < cagePtr[cageIndex].get_number_of_cells(); i++)
			{
				value += cagePtr[cageIndex].get_cage_cell_value(i);
			}
			cagePtr[cageIndex].set_operation('+');
		}


		cagePtr[cageIndex].set_target_value(value);
	}

    delete[] randomColArrIndex;
    delete[] randomRowArrValues;
}

void kenken::delete_game(void)
{
	gameGrid.delete_grid();
	gameOperation.delete_operationArray();
}

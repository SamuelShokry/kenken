#include "backtrackingfch.h"

BacktrackingFCH::BacktrackingFCH(grid* gridPtr)
{
	int gameSize = gridPtr->get_grid_size();
	variables = gridPtr;
	domain = new bool[gameSize * gameSize * gameSize];
}

grid* BacktrackingFCH::get_backtrackingFCH_variables()
{
	return variables;
}

bool* BacktrackingFCH::get_backtrackingFCH_domain_ptr()
{
	return domain;
}

void BacktrackingFCH::initialize_domain(std::vector <std::vector <int>>* Domains)
{
	int gameSize = variables->get_grid_size();
	cell* cells = variables->get_cells_ptr();
	cage* cages = variables->get_cages_ptr();
	int *optimizedArray = variables->get_optimization_cell_array_ptr();

	//No External Domain (Didn't run Arc Consistency before).
	if(Domains == nullptr)
	{
		for(int i=0; i<(gameSize * gameSize * gameSize); i++)
		{
			domain[i] = true;
		}

		for(int i = 0; i<gameSize * gameSize; i++)
		{
			int index = optimizedArray[i];
			int nextindex = optimizedArray[i+1];
			int cageIndex = cells[index].get_cage_index();

			if(cageIndex == cells[nextindex]. get_cage_index())
			{
				break;
			}
			for(int j=0; j<gameSize; j++)
			{
				if(j+1 != cages[cageIndex].get_target_value())
					domain[(index*gameSize) + j] = false;
			}
		}
	}
	else
	{
		for(int i=0; i < gameSize * gameSize; i++)
		{
			int currentCell = optimizedArray[i];
			int domainSize = (*Domains)[currentCell].size();

			for(int j=0; j < gameSize; j++)
				domain[(currentCell*gameSize) + j] = false;

			for(int j = 0; j<domainSize; j++)
			{
				domain[(currentCell*gameSize) + (*Domains)[currentCell][j] -1] = true;
			}
		}
	}
}

void BacktrackingFCH::changing_domain(int cellIndex, int domainIndex, bool value)
{
	int gridSize = variables->get_grid_size();
	int row = cellIndex / gridSize;
	int col = cellIndex % gridSize;

	//Row_Checking
	int desiredCellRow = (row * gridSize); // first cell in the current row;
	int desiredCellCol = col; // first cell in the current column;
	for(int i=0; i<gridSize; i++)
	{
		if(desiredCellRow != cellIndex)
			domain[(desiredCellRow * gridSize) + domainIndex] = value;

		if(desiredCellCol != cellIndex)
			domain[(desiredCellCol * gridSize) + domainIndex] = value;

		desiredCellRow += 1;
		desiredCellCol += gridSize;

	}
}

bool BacktrackingFCH::check_constraints(int cellIndex)
{
	int gridSize = variables->get_grid_size();
	int row = cellIndex / gridSize;
	int col = cellIndex % gridSize;

	cell * const cellsPtr = variables->get_cells_ptr();
	const int currentCellValue = cellsPtr[cellIndex].get_cell_value();

	//CheckCages
	int cageNum = cellsPtr[cellIndex].get_cage_index();
	if(!(variables->get_cages_ptr()[cageNum].cheak_cage()))
		return false;

	//Row_Checking
	int desiredCell = (row * gridSize); // first cell in the current row;
	for(int i=0; i<gridSize; i++)
	{
		if(desiredCell == cellIndex)
		{
			desiredCell += 1;
			continue;
		}
		if(currentCellValue == cellsPtr[desiredCell].get_cell_value())
		{
			return false;
		}
		desiredCell += 1;
	}

	//Coulmn_Checking
	desiredCell = col; // first cell in the current column;
	for(int i=0; i<gridSize; i++)
	{
		if(desiredCell == cellIndex)
		{
			desiredCell += gridSize;
			continue;
		}
		if(currentCellValue == cellsPtr[desiredCell].get_cell_value())
		{
			return false;
		}
		desiredCell += gridSize;
	}

	return true;
}


bool BacktrackingFCH::solve(int index)
{
	//If assignment A is complete then return A
	if(index == variables->get_grid_size() * variables->get_grid_size())
	{
		return true;
	}
	//X select a variable not in A (X is the current cell).
	//get pointer to the grid cells.
	cell *cellsPtr = variables->get_cells_ptr();
	// get the current cell index from the optimization array.
	const int cellIndex = variables->get_optimization_cell_array_ptr()[index];

	//D select an ordering on the domain of X (domain is the grid size).
	//If a variable has an empty domain then return failure
	//	if(numberOfDomainsPerVariable[cellIndex] == 0)
	//		return false;
	//Iterator to loop through the domain of the current cell to check if it is valid to be used or not.
	const int gameSize = variables->get_grid_size();

	//    for(int i=0; (i <= numberOfDomainsPerVariable[cellIndex]); i++)
	//	{
	//		//Loop through all the domains. stop when reach first unused.
	//		for(int j= domainIndex + 1; j<gameSize; j++)
	//		{
	//			if(domain[(cellIndex * gameSize) +  j] == true)
	//			{
	//				domainIndex = j;
	//				break;
	//			}
	//		}

	int domainIndex = cellIndex * gameSize;

	for(int i = 0; i < gameSize; ++i, ++domainIndex) {
		if(!domain[domainIndex])
			continue;

		cellsPtr[cellIndex].set_cell_value(i + 1);
		//		bool result = this->check_constraints(cellIndex);

		if(this->check_constraints(cellIndex))
		{
			this->changing_domain(cellIndex, i, false);

			//			std:: cout << "Trial:";
			//			for(int i=0; i<gameSize*gameSize; i++)
			//				std:: cout << cellsPtr[i].get_cell_value() << " ";
			//			std:: cout <<  std::endl;

			//			result = this->solve(index+1);
			if(this->solve(index+1))
			{
				return true;
			}
			else
			{
				this->changing_domain(cellIndex, i, true);
			}
		}
		//		domainIndex ++;
	}
	cellsPtr[cellIndex].set_cell_value(0);
	return false;
}

void BacktrackingFCH::delete_BacktrackingFCH()
{
	if(domain)
	{
		delete[] domain;
		domain = nullptr;
	}
	//	if(numberOfDomainsPerVariable)
	//	{
	//		delete[] numberOfDomainsPerVariable;
	//		numberOfDomainsPerVariable = nullptr;
	//	}
	variables = nullptr;
}

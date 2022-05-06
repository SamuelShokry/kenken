#include "backtracking.h"

Backtracking::Backtracking(grid* gridPtr)
{
    int gridSize = gridPtr->get_grid_size();
    variables = gridPtr;
    domain = gridSize;
}

int Backtracking::get_backtracking_domain()
{
    return domain;
}

grid* Backtracking::get_backtracking_variables()
{
    return variables;
}

bool Backtracking::check_constraints(int cellIndex)
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

bool Backtracking::solve(int index)
{
    //If assignment A is complete then return A
    if(index == variables->get_grid_size() * variables->get_grid_size())
    {
        return true;
    }
    //X select a variable not in A (X is the current cell).
    //D select an ordering on the domain of X (domain is the grid size).

    cell *cellsPtr = variables->get_cells_ptr();
    int cellIndex = variables->get_optimization_cell_array_ptr()[index];

    for(int i=1; i<= domain; i++)
    {
        cellsPtr[cellIndex].set_cell_value(i);
        bool result = this->check_constraints(cellIndex);

        if(result == true)
        {
            result = this->solve(index+1);
            if(result == true)
            {
                return true;
            }
        }
    }
    cellsPtr[cellIndex].set_cell_value(0);
    return false;
}

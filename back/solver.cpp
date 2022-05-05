#include "solver.h"
#include "backtracking.h"
#include "backtrackingfch.h"
#include "backtrackingfchac.h"

void solver::set_game_solving_technique(solving_technique technique)
{
    gameSolvingTechnique = technique;
}

void solver::set_is_solved(bool flag)
{
    isSolved = flag;
}

solving_technique solver::get_game_solving_technique()
{
    return gameSolvingTechnique;
}

void* solver::get_solver_ptr()
{
    return solverPtr;
}

bool solver::get_is_solved()
{
    return isSolved;
}

void solver::solve(grid* gridPtr)
{
    switch(gameSolvingTechnique)
    {
    case BACKTRACKING:
        solverPtr = new Backtracking(gridPtr);
        static_cast<Backtracking*>(solverPtr)->solve(0);
        break;

    case BACKTRACKING_WITH_FORWARD_CHECKING:
        solverPtr = new Backtracking(gridPtr);
        break;

    case BACKTRACKING_WITH_FORWARDCHECKING_AND_ARC_CONSISTENCY:
        solverPtr = new Backtracking(gridPtr);
        break;
    }

    isSolved = true;
}

void solver::clear_solution(grid* gridPtr)
{
	int gridSize = gridPtr->get_grid_size();
	for(int i=0; i<(gridSize*gridSize); i++)
	{
		gridPtr->get_cells_ptr()[i].set_cell_value(0);
	}
}

void solver::delete_solver()
{
    isSolved = false;

    switch(gameSolvingTechnique)
    {
    case BACKTRACKING:
        delete((Backtracking*) solverPtr);
        break;

    case BACKTRACKING_WITH_FORWARD_CHECKING:
        delete((BacktrackingFCH*) solverPtr);
        break;

    case BACKTRACKING_WITH_FORWARDCHECKING_AND_ARC_CONSISTENCY:
        delete((BacktrackingFCHAC*) solverPtr);
        break;
    }
}

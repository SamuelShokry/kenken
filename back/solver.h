#ifndef SOLVER_H
#define SOLVER_H

#include <bits/stdc++.h>
#include "grid.h"
#include "operationsCategory.h"

enum solving_technique{BACKTRACKING, BACKTRACKING_WITH_FORWARD_CHECKING, BACKTRACKING_WITH_FORWARDCHECKING_AND_ARC_CONSISTENCY};

class solver
{
private:
    solving_technique gameSolvingTechnique; //The desired solving technique.
    void* solverPtr = NULL;                 //Solver pointer to points to the desired solving technique.
    bool isSolved;                          //Flag to indicates is the game is sloved or not.

public:
    void set_game_solving_technique(solving_technique technique);

    void set_is_solved(bool flag);

    solving_technique get_game_solving_technique();

    void* get_solver_ptr();

    bool get_is_solved();

    void solve(grid* gridPtr);

    void clear_solution(grid* gridPtr);

    void delete_solver();
};

#endif // SOLVER_H

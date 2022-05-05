#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "grid.h"
#include "operationsCategory.h"

class Backtracking{
private:
    grid* variables;     //Is a set of variables, {X1, …, Xn}.
    int domain;          /* Is a set of domains, {D1, …, Dn}, one for each variable.
                            Implemented as a number of the grid size to loop through it.*/

public:
    Backtracking(grid* gridPtr);

    grid* get_backtracking_variables();

    int get_backtracking_domain();

    bool check_constraints(int cellIndex);

    bool solve(int index);
};

#endif // BACKTRACKING_H

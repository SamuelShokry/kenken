#ifndef BACKTRACKINGFCH_H
#define BACKTRACKINGFCH_H

#include "grid.h"
#include "operationsCategory.h"

class BacktrackingFCH
{
    grid* variables = nullptr;                  //Is a set of variables, {X1, …, Xn}.
    bool* domain = nullptr;                     /* Is a set of domains, {D1, …, Dn}, one for each variable.
                                                   Implemented as a number of the grid size to loop through it.*/
//    int* numberOfDomainsPerVariable = nullptr;

public:
    BacktrackingFCH(grid* gridPtr);

    grid* get_backtrackingFCH_variables();

    bool* get_backtrackingFCH_domain_ptr();

    void initialize_domain(std::vector <std::vector <int>>* Domains = nullptr);

    bool check_constraints(int cellIndex);

    void changing_domain(int cellIndex, int domainIndex, bool value);

    bool solve(int index);

    void delete_BacktrackingFCH();
};

#endif // BACKTRACKINGFCH_H

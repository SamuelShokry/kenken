#ifndef KENKEN_H_
#define KENKEN_H_

#include "grid.h"
#include "operationsCategory.h"
#include "solver.h"

class KenkenReader;

class kenken{
private:
	grid gameGrid;						//Random generated grid to be used in the game
	operationsCategory gameOperation;	//Classifying the operation used.
    solver gameSolver;                  //Solver to solve the game by the desired solving technique.
    bool isSolved;                      //Solving Flag to indicates if the game is solved or not.

public:
	kenken(int gameSize, operation op);
    ~kenken() {delete_game();}

    grid* get_game_grid_ptr (void);
    const grid* get_game_grid_ptr (void) const; //To be used for a const kenken

    operationsCategory* get_game_operation_ptr(void);
    const operationsCategory* get_game_operation_ptr(void) const; //To be used for a const kenken

    solver* get_game_solver_ptr(void);
    const solver* get_game_solver_ptr(void) const; //To be used for a const kenken

    bool get_is_solved() const;

	void generate_game(void);

    void solve(solving_technique technique);

    void clear_solution(void);

	void delete_game(void);

    friend class KenkenReader;
};



#endif /* KENKEN_H_ */

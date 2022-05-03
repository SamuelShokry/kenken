#ifndef KENKEN_H_
#define KENKEN_H_

#include "grid.h"
#include "operationsCategory.h"

class KenkenReader;

class kenken{
private:
	grid gameGrid;						//Random generated grid to be used in the game
	operationsCategory gameOperation;	//Classifying the operation used.
    bool isSolved;                      //Flag to indicates is the game is sloved or not.

public:
	kenken(int gameSize, operation op);
    ~kenken() {delete_game();}

    grid* get_game_grid_ptr (void);
    const grid* get_game_grid_ptr (void) const; //To be used for a const kenken

    void set_is_solved(bool flag);

    operationsCategory* get_game_operation_ptr(void);
    const operationsCategory* get_game_operation_ptr(void) const; //To be used for a const kenken

    bool get_is_solved() const;

	void generate_game(void);

	void delete_game(void);

    friend class KenkenReader;
};



#endif /* KENKEN_H_ */

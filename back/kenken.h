#ifndef KENKEN_H_
#define KENKEN_H_

#include "grid.h"
#include "operationsCategory.h"

class kenken{
private:
	grid gameGrid;						//Random generated grid to be used in the game
	operationsCategory gameOperation;	//Classifying the operation used.

public:
	kenken(int gameSize, operation op);
    ~kenken() {delete_game();}

	grid* get_game_grid_ptr (void);

	operationsCategory* get_game_operation_ptr(void);

	void generate_game(void);

	void delete_game(void);
};



#endif /* KENKEN_H_ */

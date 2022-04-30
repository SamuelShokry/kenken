#ifndef GRID_H_
#define GRID_H_

#include "cage.h"

class grid{
private:
	int gridSize = 0;			//Grid size that will be determined by the user.
	int numberOfCages = 0;		//A random number of cages that will be generated.
	cage* cages = NULL;			//pointer to a generated cages.
	cell* gridCells = NULL;		//The grid cells.

public:
    ~grid() { delete_grid(); }

	void set_grid_size(int s);

	int get_grid_size(void);

	int get_number_of_cages(void);

	cage* get_cages_ptr(void);

	cell* get_cells_ptr(void);

	void generate_grid(void);

	void delete_grid(void);
};




#endif /* GRID_H_ */

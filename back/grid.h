#ifndef GRID_H_
#define GRID_H_

#include "cage.h"

class KenkenReader;

class grid{
private:
    int gridSize = 0;                   //Grid size that will be determined by the user.
    int numberOfCages = 0;              //A random number of cages that will be generated.
    cage* cages = NULL;                 //pointer to a generated cages.
    cell* gridCells = NULL;             //The grid cells.
    int* OptimizationCellArray = NULL;  //Array to hold the Optimized order of cell indexes.

public:
    ~grid() { delete_grid(); }

	void set_grid_size(int s);

    int get_grid_size(void) const;

    int get_number_of_cages(void) const;

    cage* get_cages_ptr(void) const;

    cell* get_cells_ptr(void) const;

    int* get_optimization_cell_array_ptr() const;

	void generate_grid(void);

	void delete_grid(void);

    friend class KenkenReader;
};




#endif /* GRID_H_ */

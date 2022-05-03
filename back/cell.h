#ifndef CELL_H_
#define CELL_H_

#include <bits/stdc++.h>

class KenkenReader;

class cell {
private:
	int value =0; 		//Default value to be zero (empty).
	int cageIndex;		//To indicates this cell belongs to a specific cage.

public:
	void set_cell_value(int n);

	void set_cage_index(int n);

	int get_cell_value(void);

	int get_cage_index(void);

    friend class KenkenReader;
};


#endif /* CELL_H_ */

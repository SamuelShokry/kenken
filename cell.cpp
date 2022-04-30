#include "cell.h"

void cell::set_cell_value(int n)
{
	value = n;
}

void cell::set_cage_index(int n)
{
	cageIndex = n;
}

int cell::get_cell_value(void)
{
	return value;
}

int cell::get_cage_index(void)
{
	return cageIndex;
}

#include "operationsCategory.h"

void operationsCategory::set_category_name (operation name)
{
	categoryName = name;

	if(categoryName == PLUS)
	{
		operationsSize = 1;
        operationsArray = new char[operationsSize];
		operationsArray[0] = '+';
	}
	else if(categoryName == PLUS_MINUS)
	{
		operationsSize = 2;
        operationsArray = new char[operationsSize];
		operationsArray[0] = '+';
		operationsArray[1] = '-';
	}
	else if(categoryName == TIMES_DIVIDED)
	{
		operationsSize = 2;
        operationsArray = new char[operationsSize];
		operationsArray[0] = '*';
		operationsArray[1] = '/';
	}
	else if(categoryName == ALL_OPERATIONS)
	{
		operationsSize = 4;
        operationsArray = new char[operationsSize];
		operationsArray[0] = '+';
		operationsArray[1] = '-';
		operationsArray[2] = '*';
		operationsArray[3] = '/';
	}
}

operation operationsCategory::get_category_name(void) const
{
	return categoryName;
}

int operationsCategory::get_operations_Size (void) const
{
	return operationsSize;
}

char* operationsCategory::get_operations_array(void) const
{
	return operationsArray;
}

//const char* operationsCategory::get_operations_array(void) const
//{
//    return operationsArray;
//}

char operationsCategory::get_random_operation(int numberOfCells)
{
    assert(operationsSize > 0);
	int op = rand() % operationsSize;
	if(numberOfCells == 1)
	{
		return ' ';
	}
	else if(numberOfCells > 2)
	{
		if(op % 2 == 1 && operationsSize > 1)
		{
			op--;
		}
	}
	return operationsArray[op];

}

void operationsCategory::delete_operationArray(void)
{
    if (operationsArray) {
        delete[] operationsArray;
        operationsArray = nullptr;
    }
}

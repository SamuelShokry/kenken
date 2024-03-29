#ifndef OPERATIONSCATEGORY_H_
#define OPERATIONSCATEGORY_H_

#include <bits/stdc++.h>

class KenkenReader;

enum operation{PLUS, PLUS_MINUS, TIMES_DIVIDED, ALL_OPERATIONS};

class operationsCategory
{
private:
	operation categoryName;	//Input name of operations category.
	int operationsSize;		//Number of allowed operations.
    char* operationsArray = nullptr;	//Array of the allowed operations.

public:
	void set_category_name (operation name);

    operation get_category_name(void) const;

    int get_operations_Size (void) const;

    char* get_operations_array(void) const;

	char get_random_operation(int numberOfCells);

	void delete_operationArray(void);

    ~operationsCategory() {delete_operationArray();}

    friend class KenkenReader;
};



#endif /* OPERATIONSCATEGORY_H_ */

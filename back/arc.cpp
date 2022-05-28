#include "arc.h"

void Arc::set_arc(int cell1, int cell2, char c, int value)
{
    firstCell = cell1;
    secondCell = cell2;
    constraintChar = c;
    constraintValue = value;
}

int Arc::get_first_cell(void)
{
    return firstCell;
}

int Arc::get_second_cell(void)
{
    return secondCell;
}

char Arc::get_constraint_char(void)
{
    return constraintChar;
}

int Arc::get_constraint_value(void)
{
    return constraintValue;
}

bool Arc::remove_inconsistant_values(std::vector <int>* firstDomain, std::vector <int>* secondDomain)
{
    int size1 = firstDomain->size();
    int size2 = secondDomain->size();
    bool result = false;
    bool foundedFlag = false;
    std::vector <int> changedVector;

    switch(this->constraintChar)
    {
    case' ':
        for(int i=0; i<size1; i++)
        {
            if((*firstDomain)[i] == constraintValue)
            {
                changedVector.push_back((*firstDomain)[i]);
            }
            else
            {
                result = true;
            }
        }
        break;
    case '!':
        for(int i=0; i<size1; i++)
        {
            for(int j=0; j<size2; j++)
            {
                if((*firstDomain)[i] != (*secondDomain)[j])
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*firstDomain)[i]);
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '+':
        for(int i=0; i<size1; i++)
        {
            for(int j=0; j<size2; j++)
            {
                if((*firstDomain)[i] + (*secondDomain)[j] <= constraintValue)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*firstDomain)[i]);
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '*':
        for(int i=0; i<size1; i++)
        {
            for(int j=0; j<size2; j++)
            {
                if((*firstDomain)[i] * (*secondDomain)[j] <= constraintValue)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*firstDomain)[i]);
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '-':
        for(int i=0; i<size1; i++)
        {
            for(int j=0; j<size2; j++)
            {
                if(std::abs((*firstDomain)[i] - (*secondDomain)[j]) == constraintValue)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*firstDomain)[i]);
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '/':
        for(int i=0; i<size1; i++)
        {
            for(int j=0; j<size2; j++)
            {
                int minValue = std::min((*firstDomain)[i], (*secondDomain)[j]);
                int maxValue = std::max((*firstDomain)[i], (*secondDomain)[j]);
                if((maxValue/minValue) == constraintValue && (maxValue % minValue) == 0)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*firstDomain)[i]);
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    }

    if(result)
    {
        (*firstDomain) = changedVector;
    }

    return result;
}

bool Arc::is_equal(Arc x)
{
    int cell1 = x.get_first_cell();
    int cell2 = x.get_second_cell();
    char c = x.get_constraint_char();
    if(cell1 == firstCell && cell2 == secondCell && c == constraintChar)
        return true;
    return false;
}

void Arc::swap_cells(void)
{
    int temp = firstCell;
    firstCell = secondCell;
    secondCell = temp;
}

void Arc::print_arc(void)
{
	std::cout << firstCell <<' ' << secondCell << ' ' << constraintChar << ' ' << constraintValue << std::endl;
}

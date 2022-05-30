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
    bool result = false;
    bool foundedFlag = false;

    auto iter1 = firstDomain->begin();
    auto begin2 = secondDomain->begin();

    auto end1 = firstDomain->end();
    auto end2 = secondDomain->end();

    std::vector <int> changedVector;
    changedVector.reserve(firstDomain->size()<<1);

    switch(this->constraintChar)
    {
    case' ':
        for(; iter1 != end1; ++iter1)
        {
            if((*iter1) == constraintValue)
            {
                changedVector.push_back((*iter1));
            }
            else
            {
                result = true;
            }
        }
        break;
    case '!':
        for(; iter1 != end1; ++iter1)
        {
            for(auto iter2 = begin2; iter2 != end2; ++iter2)
            {
                if((*iter1) != (*iter2))
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*iter1));
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '+':
        for(; iter1 != end1; ++iter1)
        {
            for(auto iter2 = begin2; iter2 != end2; ++iter2)
            {
                if((*iter1) + (*iter2) <= constraintValue)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*iter1));
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '*':
        for(; iter1 != end1; ++iter1)
        {
            for(auto iter2 = begin2; iter2 != end2; ++iter2)
            {
                if((*iter1) * (*iter2) <= constraintValue)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*iter1));
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '-':
        for(; iter1 != end1; ++iter1)
        {
            for(auto iter2 = begin2; iter2 != end2; ++iter2)
            {
                if(std::abs((*iter1) - (*iter2)) == constraintValue)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*iter1));
                foundedFlag = false;
            }
            else
            {
                result = true;
            }
        }
        break;
    case '/':
        for(; iter1 != end1; ++iter1)
        {
            for(auto iter2 = begin2; iter2 != end2; ++iter2)
            {
                int minValue = std::min((*iter1), (*iter2));
                int maxValue = std::max((*iter1), (*iter2));
                if((maxValue/minValue) == constraintValue && (maxValue % minValue) == 0)
                {
                    foundedFlag = true;
                    break;
                }
            }
            if(foundedFlag)
            {
                changedVector.push_back((*iter1));
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

bool Arc::is_equal(Arc &x)
{
    return (x.get_first_cell() == firstCell
            && x.get_second_cell() == secondCell
            && x.get_constraint_char() == constraintChar);
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

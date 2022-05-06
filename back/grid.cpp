#include "grid.h"

void grid::set_grid_size(int s)
{
    gridSize = s;
}

int grid::get_grid_size(void) const
{
    return gridSize;
}

int grid::get_number_of_cages(void) const
{
    return numberOfCages;
}

cage* grid::get_cages_ptr(void) const
{
    return cages;
}

cell* grid::get_cells_ptr(void) const
{
    return gridCells;
}

int* grid::get_optimization_cell_array_ptr() const
{
    return OptimizationCellArray;
}

void grid::generate_grid(void)
{
    /********************* Grid class initialization. *****************/
    /* Initialize the number of cages to be a random value between
     * the size of the grid and 2 x size of the grid. */
    if(gridSize<5)  // [1-2]*gridSize
    {
        numberOfCages = gridSize + (rand() % (gridSize));
    }
    else if (gridSize < 7) //[2-3]*gridSize
    {
        numberOfCages = 2 * gridSize + (rand() % (gridSize));
    }
    else if (gridSize < 8) //[3-4]*gridSize
    {
        numberOfCages = 3 * gridSize + (rand() % (gridSize));
    }
    else    //[4-5]*gridSize
    {
        numberOfCages = 4 * gridSize + (rand() % (gridSize));
    }
    cages = new cage[numberOfCages];
    gridCells = new cell[gridSize*gridSize];
    OptimizationCellArray = new int[gridSize*gridSize];

    //Array to hold the size of each cage.
    int* tempArray = new int[numberOfCages];
    //Array to hold the cages in a descinding orders.
    int* orderedTempArray = new int[numberOfCages];
    //Variable to hold the remaining number of unused cells.
    //At the beginning each cage has one cell.
    int remainingGridSize = (gridSize * gridSize);
    //Variable to hold the random number of cells to the current cage.
    int cageCellsRandomSize;
    //Variable used to count the number of used cells by the cages.
    int deservedCellsCounter =0;
    //counter to avoid infinite loop.
    int infinite = 0;

    /****************** Cage cells number generation *****************/
    //Initialize the temp array with the one cell it owns.
    for(int i=0; i<numberOfCages; i++)
    {

        if(i < (gridSize * gridSize) / 3)
        {
            tempArray[i] = 2;
            remainingGridSize -= 2;
        }
        else
        {
            tempArray[i] = 1;
            remainingGridSize -= 1;
        }
        assert(remainingGridSize > -1);
    }

    //Distribute the remaining cells randomly through the cages.
    while(remainingGridSize != 0)
    {
        assert(remainingGridSize > -1);
        int index;
        //generate the random cage cells number.
        cageCellsRandomSize = 1 + (rand() % std::min(remainingGridSize, 5));

        infinite = 0;
        do
        {
            index = rand() % numberOfCages;
            infinite ++;
            if(infinite == 20)
            {
                index = (index + 1) % numberOfCages;
                break;
            }
        }while((tempArray[index] + cageCellsRandomSize) > 4);

        tempArray[index] += cageCellsRandomSize;
        remainingGridSize -= cageCellsRandomSize;
    }

    for(int i=0; i<numberOfCages; i++)
    {
        int randIndex = rand() % numberOfCages;
        int swapVar = tempArray[i];
        tempArray[i] = tempArray[randIndex];
        tempArray[randIndex] = swapVar;
    }

    //loop through all cages.
    for(int i=0; i<numberOfCages; i++)
    {
        /* Variables to navigate through the grid in Zizag shape. */
        int rowIndex = 0;
        int columnIndex =0;
        int cellIndex = 0;

        //initializing the cage:
        cages[i].set_number_of_cells(tempArray[i]);

        //determining of the cage cells.
        for(int j=0; j<tempArray[i]; j++)
        {
            rowIndex = deservedCellsCounter / gridSize;
            columnIndex = deservedCellsCounter % gridSize;
            if(rowIndex % 2 == 0)
            {
                cellIndex = (rowIndex * gridSize) + columnIndex;
            }
            else
            {
                cellIndex = (rowIndex * gridSize) + gridSize - columnIndex -1;
            }

            if(j==0)
            {
                if(rowIndex % 2 == 0)
                {
                    cages[i].set_first_cell_in_cage(cellIndex);
                }
                else
                {
                    int t = (cellIndex%gridSize) + 1 - tempArray[i];
                    if(t <0)
                    {
                        cages[i].set_first_cell_in_cage(rowIndex * gridSize);
                    }
                    else
                    {
                        cages[i].set_first_cell_in_cage(rowIndex * gridSize + t);
                    }
                }
            }
            //make the cage pointers points to the desired cells.
            cages[i].set_cage_cell_ptr(j, gridCells + cellIndex);
            //set the current cell's cage index.
            gridCells[cellIndex].set_cage_index(i);
            deservedCellsCounter ++;
        }
    }

    for(int i=0; i<numberOfCages; i++)
        orderedTempArray[i] = i;

    // One by one move boundary of unsorted subarray
    for (int x = 0; x < numberOfCages-1; x++)
    {
        // Find the minimum element in unsorted array
        int min_idx = x;
        for (int y = x+1; y < numberOfCages; y++)
            if (tempArray[y] < tempArray[min_idx])
                min_idx = y;

        // Swap the found minimum element with the first element
        std::swap(tempArray[min_idx], tempArray[x]);
        std::swap(orderedTempArray[min_idx], orderedTempArray[x]);
    }

    int cellCounter = 0;
    for(int i=0; i<numberOfCages; i++)
    {
        cage* currentCage = &cages[orderedTempArray[i]];
        int cageCellNumber = currentCage->get_number_of_cells();
        for(int j=0; j<cageCellNumber; j++)
        {
            int index = (currentCage->get_cage_cells_ptr()[j]) - gridCells;
            OptimizationCellArray[cellCounter] = index;
            cellCounter++;
        }
    }

    delete[] orderedTempArray;
    delete[] tempArray;
}

void grid::delete_grid(void)
{
    if (cages) {
        delete[] cages;
        cages = nullptr;
    }
    if (gridCells) {
        delete[] gridCells;
        gridCells = nullptr;
    }
    if(OptimizationCellArray)
    {
        delete[] OptimizationCellArray;
        OptimizationCellArray = nullptr;
    }
}

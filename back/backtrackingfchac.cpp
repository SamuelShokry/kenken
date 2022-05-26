#include "backtrackingfchac.h"

BacktrackingFCHAC::BacktrackingFCHAC(grid* gridPtr)
{
    int gridSize = gridPtr->get_grid_size();
    cell* cells = gridPtr->get_cells_ptr();
    cage* cages = gridPtr->get_cages_ptr();
    std::vector <int> d;    //temp vector for domain of each cell.

    //Initializing the domain vector from 1 to gridSize;
    for(int i=1; i<= gridSize; i++)
        d.push_back(i);

    //Loop through all the cells in the grid.
    for(int i=0; i<(gridSize * gridSize); i++)
    {
        std::vector <Arc> arcs; //temp vector to hold all the arcs to the current cell;
        std::vector <bool> arcsF; //temp vector to hold all the arcs flags to the current cell;
        int row = i / gridSize;
        int col = i % gridSize;

        //Row Arc Creating.
        int desiredCell = (row * gridSize); // first cell in the current row.
        for(int j = 0; j < gridSize; j++)
        {
            if(desiredCell != i) //If the Iterator Index isn't at the same cell.
            {
                Arc temp;
                temp.set_arc(i, desiredCell, '!', 0); //Creating a new Arc.
                //Push the arc to the qeue to be used by AC-3 Algorithm.
                this->q.push(temp);
                //Push the arc to the vector of arcs to be used in the search for arcs.
                arcs.push_back(temp);
                //set the current arc flag to be true which means that the arc is in the queue.
                arcsF.push_back(true);
            }
            desiredCell ++;         //Move to another cell in the same row.
        }

        //Column Arc Creating.
        desiredCell = col;               // first cell in the current column.
        for(int j = 0; j < gridSize; j++)
        {
            if(desiredCell != i)    //If the Iterator Index isn't at the same cell.
            {
                Arc temp;
                temp.set_arc(i, desiredCell, '!', 0);   //Creating a new Arc.
                //Push the arc to the qeue to be used by AC-3 Algorithm.
                this->q.push(temp);
                //Push the arc to the vector of arcs to be used in the search for arcs.
                arcs.push_back(temp);
                //set the current arc flag to be true which means that the arc is in the queue.
                arcsF.push_back(true);
            }
            desiredCell += gridSize;  //Move to another cell in the same col.
        }

        //Cage Arc Creating
        int cageIndex = cells[i].get_cage_index();
        int cellsNumberPerCage = cages[cageIndex].get_number_of_cells();
        cell** cageCells = cages[cageIndex].get_cage_cells_ptr();
        //Loop through all cells in the current cage.
        for(int j=0; j<cellsNumberPerCage; j++)
        {
            //Check if the current iterator index isn't the same cell.
            if(cageCells[j] != (cells + i))
            {
                Arc temp;
                //Creating a new Arc.
                temp.set_arc(i, (cells - cageCells[j]), cages[cageIndex].get_operation() , cages[cageIndex].get_target_value());
                //Push the arc to the qeue to be used by AC-3 Algorithm.
                this->q.push(temp);
                //Push the arc to the vector of arcs to be used in the search for arcs.
                arcs.push_back(temp);
                //set the current arc flag to be true which means that the arc is in the queue.
                arcsF.push_back(true);
            }
        }
        //Push the current cell domain to the domain vector of the all cells.
        this->Domains.push_back(d);
        //Push the current cell arcs to the arcs vector of the all cells.
        arcsPerCell.push_back(arcs);
        //Push the current cell arcs flags to the arcs flags vector of the all cells.
        arcsFlag.push_back(arcsF);
    }
}

bool BacktrackingFCHAC::AC_3()
{
    while(!(this->q.empty()))
    {
        Arc currentArc = this->q.front();
        this->q.pop();
        int celli = currentArc.get_first_cell();
        int cellj = currentArc.get_second_cell();

        //Loop through all the arcs of the celli to find the index of the arc with cellj to put it false.
        int arcsIsize = arcsPerCell[celli].size();
        for(int i =0; i < arcsIsize; i++)
        {
            if(currentArc.is_equal(arcsPerCell[celli][i]))
            {
                arcsFlag[celli][i] = false;                     //Delete the arc.
            }
        }

        if(currentArc.remove_inconsistant_values(&Domains[celli], &Domains[cellj]))
        {
            if(Domains[celli].empty())
                return false;
            int arcsSize = arcsPerCell[celli].size();  //Number of arcs to the celli.
            //Loop through all cell1 neighbors (get all cell1 arcs from arcsPerCell vector).
            for(int i=0; i < arcsSize; i++)
            {
                Arc tempArc = arcsPerCell[celli][i];     //get the first arr of celli arcs.
                int cellk = tempArc.get_second_cell();   //get the neighbor cell in this arc.

                if(cellk != cellj)                       //check if the current arc isn't the removed arc in the first algorithm.
                {
                    //swap the arc
                    tempArc.swap_cells();
                    int arcsKsize = arcsPerCell[cellk].size();  //Number of arcs to the cellk.
                    //Loop through all the arcs of the cellk to find the index of the arc with celli

                    for(int arcIndex =0; arcIndex < arcsKsize; arcIndex++)
                    {
                        if(tempArc.is_equal(arcsPerCell[cellk][arcIndex]))
                        {
                            if(arcsFlag[cellk][arcIndex] == false)
                            {
                                q.push(tempArc);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void BacktrackingFCHAC::solve(grid* gridPtr)
{
    if(this->AC_3())
    {

    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
}

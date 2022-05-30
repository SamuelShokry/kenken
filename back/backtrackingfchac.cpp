#include "backtrackingfchac.h"
#include "backtrackingfch.h"

BacktrackingFCHAC::BacktrackingFCHAC(grid* gridPtr)
{
	int gridSize = gridPtr->get_grid_size();
	cell* cells = gridPtr->get_cells_ptr();
	cage* cages = gridPtr->get_cages_ptr();
    std::vector <int> d(gridSize);    //temp vector for domain of each cell.

	//Initializing the domain vector from 1 to gridSize;
    for(int i=1; i<= gridSize; ++i)
        d[i-1] = i;

	//Loop through all the cells in the grid.
    const int gridSizeSquared = (gridSize * gridSize);
    arcsPerCell.resize(gridSizeSquared);
    arcsFlag.resize(gridSizeSquared);
    for(int i=0; i<gridSizeSquared; ++i)
	{
		std::vector <Arc> arcs; //temp vector to hold all the arcs to the current cell;
		std::vector <bool> arcsF; //temp vector to hold all the arcs flags to the current cell;
        arcs.reserve(gridSize << 2);
        arcsF.reserve(gridSize << 2);
		int row = i / gridSize;
		int col = i % gridSize;

		//Row Arc Creating.
        int desiredCell = (row * gridSize); // first cell in the current row.
        //Column Arc Creating.
        int desiredCellCol = col;               // first cell in the current column.

        // Merge the for loops for both rows and columns
        for(int j = 0; j < gridSize; ++j)
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
            ++desiredCell;         //Move to another cell in the same row.

            if(desiredCellCol != i)    //If the Iterator Index isn't at the same cell.
            {
                Arc temp;
                temp.set_arc(i, desiredCellCol, '!', 0);   //Creating a new Arc.
                //Push the arc to the qeue to be used by AC-3 Algorithm.
                this->q.push(temp);
                //Push the arc to the vector of arcs to be used in the search for arcs.
                arcs.push_back(temp);
                //set the current arc flag to be true which means that the arc is in the queue.
                arcsF.push_back(true);
            }
            desiredCellCol += gridSize;  //Move to another cell in the same col.
        }

		//Cage Arc Creating
		int cageIndex = cells[i].get_cage_index();
		int cellsNumberPerCage = cages[cageIndex].get_number_of_cells();
		//Cage of only one cell.
		if(cellsNumberPerCage == 1)
		{
			Arc temp;
			//Creating a new Arc.
			temp.set_arc(i, i, ' ' , cages[cageIndex].get_target_value());
			//Push the arc to the qeue to be used by AC-3 Algorithm.
			this->q.push(temp);
			//Push the arc to the vector of arcs to be used in the search for arcs.
			arcs.push_back(temp);
			//set the current arc flag to be true which means that the arc is in the queue.
			arcsF.push_back(true);
		}
		//Cage of more than one cell.
		else
		{
			cell** cageCells = cages[cageIndex].get_cage_cells_ptr();
			//Loop through all cells in the current cage.
            for(int j=0; j<cellsNumberPerCage; ++j, ++cageCells)
			{
				//Check if the current iterator index isn't the same cell.
                if(*cageCells != (cells + i))
				{
					Arc temp;
					//Creating a new Arc.
                    temp.set_arc(i, std::abs(cells - *cageCells), cages[cageIndex].get_operation() , cages[cageIndex].get_target_value());
					//Push the arc to the qeue to be used by AC-3 Algorithm.
					this->q.push(temp);
					//Push the arc to the vector of arcs to be used in the search for arcs.
					arcs.push_back(temp);
					//set the current arc flag to be true which means that the arc is in the queue.
					arcsF.push_back(true);
				}
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
        auto begin = arcsPerCell[celli].begin();
        auto end = arcsPerCell[celli].end();
        for (auto it = begin; it != end; ++it)
		{
            if(currentArc.is_equal(*it))
			{
                arcsFlag[celli][it - begin] = false; //Delete the arc.
			}
		}

		if(currentArc.remove_inconsistant_values(&Domains[celli], &Domains[cellj]))
		{
			if(Domains[celli].empty())
				return false;
            //int arcsSize = arcsPerCell[celli].size();  //Number of arcs to the celli.
			//Loop through all cell1 neighbors (get all cell1 arcs from arcsPerCell vector).
            for(auto iter = begin; iter != end; ++iter)
			{
                //Arc tempArc = arcsPerCell[celli][i];     //get the first arr of celli arcs.
                int cellk = iter->get_second_cell();   //get the neighbor cell in this arc.
				if(cellk != cellj)                       //check if the current arc isn't the removed arc in the first algorithm.
				{
					//swap the arc
                    iter->swap_cells();
                    //int arcsKsize = arcsPerCell[cellk].size();  //Number of arcs to the cellk.
					//Loop through all the arcs of the cellk to find the index of the arc with celli
                    auto beginK = arcsPerCell[cellk].begin();
                    auto endK = arcsPerCell[cellk].end();
                    for(auto iterK = beginK; iterK != endK; ++iterK)
					{
                        if(iter->is_equal(*iterK))
						{
                            if(arcsFlag[cellk][iterK - beginK] == false)
							{
                                q.push(*iter);
							}
							break;
						}
					}
                    iter->swap_cells();
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
		BacktrackingFCH x(gridPtr);
		x.initialize_domain(&Domains);
		x.solve(0);
		x.delete_BacktrackingFCH();
	}
}

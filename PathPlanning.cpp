#include "PathPlanning.h"

PathPlanning::PathPlanning(uint32_t p_map_heigth, uint32_t p_map_width) : map_heigth(p_map_heigth), map_width(p_map_width)
{
    map = new int8_t[p_map_heigth * p_map_width];
}

std::vector<Cell*>* PathPlanning::FindPath(Cell p_begin, Cell p_end)
{
    std::map<uint32_t, Quadrant*> l_open_list;
    std::map<uint32_t, Quadrant*> l_closed_list;

    uint32_t l_key_begin = ToKey(p_begin);
    uint32_t l_key_end = ToKey(p_end);

    Quadrant* l_quadrant_begin = new Quadrant;
    l_quadrant_begin->position = p_begin;
    l_quadrant_begin->g = 0;
    l_quadrant_begin->h = ComputeManhattan(p_begin, p_end);
    l_quadrant_begin->f = l_quadrant_begin->g + l_quadrant_begin->h;
    l_quadrant_begin->father = nullptr;

    //It's inserting the initial quadrant to open list
    l_open_list.insert(std::make_pair(l_key_begin, l_quadrant_begin));

    Quadrant* l_current_quadrant;
    //While open list is not empty, or closed list not contain the end quadrant
    while ((l_open_list.size() > 0) && (l_closed_list.find(l_key_end) == l_closed_list.end())) {
        
        l_current_quadrant = FindLowestF(l_open_list); //Find quadrant that have the lowest value of 
        //F in the open list, so, insert in closed list
        l_closed_list.insert(std::make_pair(ToKey(l_current_quadrant->position), l_current_quadrant));

        //************ A little explanation about what i am doing below ******************
        //Now, look around the current quadrant (eight quadrants)
        //If quadrant is in the closed list or there is an obstacle just ignore, otherwise:
        //if quadrant is not in the open list just add and compute G, H and F, otherwise
        //Verify if way to passing by current quadrant is shorter than old way, so, in 
        //this case recalculate G and F 
        //**********************************************************************************

        uint32_t i = l_current_quadrant->position.x - 1;
        uint32_t j = l_current_quadrant->position.y - 1;
        uint32_t i_max = l_current_quadrant->position.x + 2;
        uint32_t j_max = l_current_quadrant->position.y + 2;

        for (; i < i_max; i++) {
            for (; j < j_max; j++) {

                Cell l_temporary_cell;
                l_temporary_cell.x = j;
                l_temporary_cell.y = i;
                uint32_t l_temporary_key = ToKey(l_temporary_cell);

                //It's verifying if position is valid
                bool valid = !((i == i_max - 2) && (j == j_max - 2)) &&
                        (i > 0) && (i < map_heigth) && (j > 0) &&
                        (j < map_width) && (map[i * map_width + j] == 0) &&
                        (l_closed_list.find(l_temporary_key) == l_closed_list.end());
                
                if (valid) {

                    Quadrant* l_temporary_quadrant = new Quadrant;

                    std::pair<std::map<uint32_t, Quadrant*>::iterator, bool> verification = l_open_list.insert(std::make_pair(l_temporary_key, l_temporary_quadrant));

                    //If it was inserted in the list
                    if (verification.second) {
                        l_temporary_quadrant->position = l_temporary_cell;
                        l_temporary_quadrant->father = l_current_quadrant;

                        //Verifying if is a diagonal quadrant
                        if ((i != i_max - 2) && (j != j_max - 2)) {
                            l_temporary_quadrant->g = l_current_quadrant->g + 14;
                        }
                        else {
                            l_temporary_quadrant->g = l_current_quadrant->g + 10;
                        }

                        l_temporary_quadrant->h = ComputeManhattan(l_temporary_cell, p_end);
                        l_temporary_quadrant->f = l_temporary_quadrant->g + l_temporary_quadrant->h;
                    }
                    else {

                        Quadrant* l_temporary_quadrant_to_modify = verification.first->second;
                        uint32_t l_temporary_g;
                        //Verifying if is a diagonal quadrant
                        if ((i != i_max - 2) && (j != j_max - 2))
                            l_temporary_g = l_current_quadrant->g + 14;
                        else
                            l_temporary_g = l_current_quadrant->g + 10;

                        if (l_temporary_g < l_temporary_quadrant_to_modify->g) {
                            l_temporary_quadrant_to_modify->g = l_temporary_g;
                            l_temporary_quadrant_to_modify->father = l_current_quadrant;
                        }

                    }
                }
            }
        }

    }
    
    std::vector<Cell*>* l_path_inverse = new std::vector<Cell*>;
    std::vector<Cell*>* l_path_return = new std::vector<Cell*>;
    if (l_open_list.size() > 0)
    {
        Quadrant* l_it = l_closed_list.find(l_key_end)->second;
        while (l_it != nullptr)
        {
            l_path_inverse->push_back(&l_it->position);
            l_it = l_it->father;
        }
        
        for (uint32_t i = l_path_inverse->size() - 1; i >= 0; i--)
        {
            Cell* l_temporary_cell = new Cell;
            l_temporary_cell->x = l_path_inverse->at(i)->x;
            l_temporary_cell->y = l_path_inverse->at(i)->y;
            l_path_return->push_back(l_temporary_cell);
        }
    }
    
    for (auto elem : l_closed_list) {
        delete(elem.second);
    }

    for (auto elem : l_open_list) {
        delete(elem.second);
    }
    
    l_closed_list.clear();
    l_open_list.clear();
    
    return l_path_return;
}

inline uint32_t PathPlanning::ToKey(Cell& p_position)
{

    return ((p_position.x << 16) & 0xFFFF0000) | (p_position.y & 0x0000FFFF);
}

inline uint32_t PathPlanning::ComputeManhattan(Cell& p_current, Cell& p_end)
{
    unsigned int manhattan = abs(p_current.x - p_end.x) + abs(p_current.y - p_end.y);
    return manhattan;
}

inline Quadrant* PathPlanning::FindLowestF(std::map<uint32_t, Quadrant*>& p_open_list)
{
    Quadrant* lowest = p_open_list[0];

    for (auto elem : p_open_list) {
        if (elem.second->f < lowest->f)
            lowest = elem.second;
    }

    return lowest;
}
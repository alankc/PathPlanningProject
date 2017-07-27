#ifndef PATHPLANNING_H
#define PATHPLANNING_H

#include <map>
#include <vector>
#include "Quadrant.h"
#include "Cell.h"

class PathPlanning {
public:
    PathPlanning(uint32_t p_map_heigth, uint32_t p_map_width);
    std::vector<Cell*>* FindPath(Cell p_begin, Cell p_end);
private:
    int8_t* map;
    uint32_t map_heigth;
    uint32_t map_width;
    inline uint32_t ToKey(Cell& p_position);
    inline uint32_t ComputeManhattan(Cell& p_current, Cell& p_end);
    inline Quadrant* FindLowestF(std::map<uint32_t, Quadrant*>& p_open_list);
};

#endif /* PATHPLANNING_H */


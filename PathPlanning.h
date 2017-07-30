#ifndef PATHPLANNING_H
#define PATHPLANNING_H

#include <map>
#include <vector>
#include "Quadrant.h"
#include "Cell.h"
#include "Map.h"

class PathPlanning {
public:
    PathPlanning(Map& p_map) : map(p_map) {};
    std::vector<Cell*>* FindPath(Cell p_begin, Cell p_end);
private:
    Map map;
    inline uint32_t ToKey(Cell& p_position);
    inline uint32_t ComputeManhattan(Cell& p_current, Cell& p_end);
    inline Quadrant* FindLowestF(std::map<uint32_t, Quadrant*>& p_open_list);
};

#endif /* PATHPLANNING_H */


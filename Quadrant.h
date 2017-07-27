#ifndef QUADRANT_H
#define QUADRANT_H

#include "Cell.h"

typedef struct quadrant
{
    Cell position;
    uint32_t h;
    uint32_t g;
    uint64_t f;
    struct quadrant* father;
}Quadrant;

#endif /* QUADRANT_H */


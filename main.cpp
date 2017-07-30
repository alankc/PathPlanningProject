/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: x
 *
 * Created on 26 de Julho de 2017, 12:49
 */

#include "PathPlanning.h"
#include <iostream>

int main(int argc, char** argv) {

    Map* map = new Map;
    map->map_heigth = 500;
    map->map_width = 500;
    map->cells = new int8_t[map->map_heigth * map->map_width];
    
    PathPlanning pp(*map);
    
    Cell begin;
    begin.y = 0;
    begin.x = 0;
    
    Cell end;
    end.y = 178;
    end.x = 257;
    
            
    std::vector<Cell*>* path = pp.FindPath(begin, end);
    std::cout << "--------------------------------" << std::endl;
    for (uint32_t i = 0; i < path->size(); i++)
    {
        std::cout << path->at(i)->x << " " << path->at(i)->y << "\n";
    }

    
    return 0;
}


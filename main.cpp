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

    Map map;
    map.map_heigth = 30;
    map.map_width = 200;
    map.cells = new int8_t[map.map_heigth * map.map_width];
    
    for (uint32_t i = 2; i < map.map_heigth - 2; i++)
        map.cells[i * map.map_width + map.map_width / 2] = 1;
   
    for (uint32_t i = 2; i < map.map_width - 2; i++)
        map.cells[i + map.map_width * map.map_heigth/ 2] = 1;
    
    PathPlanning pp(map);
    
    Cell begin;
    begin.y = 15;
    begin.x = 175;
    
    Cell end;
    end.y = 1;
    end.x = 2;
    
            
    std::vector<Cell*>* path = pp.FindPath(begin, end);
    std::cout << "--------------------------------" << std::endl;
    for (uint32_t i = 0; i < map.map_heigth; i++)
    {
        std::cout << std::endl;
        for (uint32_t j = 0; j < map.map_width; j++)
        {
            if ((map.cells[i * map.map_width + j] == 0))
            {
                bool tst = true;
                for (uint32_t k = 0; k < path->size(); k++)
                {
                    if ((path->at(k)->x == j) && (path->at(k)->y == i))
                    {
                        std::cout << " ";
                        tst = false;
                        break;
                    }
                }
                if (tst)
                    std::cout << "#";  
            }  
            else
                std::cout << "O";
        }
    }
    std::cout << "\n******* Size: " << path->size() << " *******\n";
    for (uint32_t i = 0; i < path->size(); i++)
    {
        std::cout << "(" << path->at(i)->y << "," << path->at(i)->x << ")\n";
    }
    
    return 0;
}


#ifndef _MY_GRIDS_
#define _MY_GRIDS_

//#define DEBUG 

// stdlib includes first
#include <vector>
#include <array>
#include <random>
#include <iostream>
// Then project specific includes
#include "ships.hpp"

namespace BattleShip {

    constexpr int GRID_SIZE = 10;
    constexpr int GRID_SIZE_PADDED = 12;
    constexpr int MAX_ITER_PLACEMENT = 1000;
    enum letter {a=1,b,c,d,e,f,g,h,i,l};

    struct Grid {
        std::array<int,(GRID_SIZE_PADDED)*(GRID_SIZE_PADDED)>  grid; // padded for convenience
        std::random_device dev; 
        std::mt19937 e;
        std::uniform_int_distribution<int> dist_pt, dist_dir;
        Grid(){ // initialise empty grid
            e = std::mt19937{dev()};
            dist_pt  = std::uniform_int_distribution<int>{0, (GRID_SIZE-1)*(GRID_SIZE-1)};
            dist_dir = std::uniform_int_distribution<int>{0, 2};
            #pragma omp parallel for
            for(int i = 0; i < GRID_SIZE_PADDED ; i++) for(int j =0; j < GRID_SIZE_PADDED; j++) {
                grid[i + (GRID_SIZE_PADDED)*j] = 0;
            }
        }
        void place_ship(shiptypes t);

        void display(){
            std::cout << "\t\t";
            for(int j =0; j < GRID_SIZE_PADDED; j++) { std::cout << j << "\t"; }
            std::cout << std::endl << std::endl << "\t";
            for(int i = 0; i < GRID_SIZE_PADDED ; i++) {
                std::cout << i << "| \t" ;
                for(int j =0; j < GRID_SIZE_PADDED; j++) {
                std::cout  << grid[j + i*GRID_SIZE_PADDED] << "\t";
                if(j==GRID_SIZE_PADDED-1) std::cout << std::endl << std::endl << "\t"  ;
            }}
            std::cout << std::endl ;
        }
    };
    inline int pad_index(const int index);
    inline int coordinates(const unsigned int i, letter j) { return GRID_SIZE_PADDED*(i + 1) + j; }
    void Grid::place_ship(shiptypes t){
        int length = ship_length[t-1];
        bool done = false;
        int iter = 0;
        while(!done){
            iter ++ ;
            if (iter > MAX_ITER_PLACEMENT) done = true;
            int dir   = dist_dir(e); // direction 
            #ifdef DEBUG
            std::cout << "Direction: " << (dir?"Vert":"Hor") << std::endl;
            #endif 
            int index = dist_pt(e);  // position on the playing field
            int index_p = pad_index(index); // position on the padded grid
            int i = 1 + index / GRID_SIZE; // i j just for convenience
            int j = 1 + index % GRID_SIZE;
            #ifdef DEBUG
            std::cout << "index i j: " << index << " " << i << " " << j << std::endl;
            #endif 
            // check if there's enough space around it ! 
            if(dir){ // horizontal
                if(j+length - 1 > GRID_SIZE) continue;
                int tmp = 0;
                for(int j_loc = -1; j_loc<=length; j_loc++) {
                    tmp += grid[index_p+j_loc] + grid[index_p + GRID_SIZE_PADDED +j_loc] + \
                    grid[index_p - GRID_SIZE_PADDED +j_loc] ;
                }
                if(tmp) continue;
                for(int j_loc = 0; j_loc<length; j_loc++) grid[index_p+j_loc] = t;
                done = true;
            }   
            // vertical placement
            if(i+length - 1 > GRID_SIZE) continue;
            int tmp = 0;
            for(int i_loc = -1; i_loc<=length; i_loc++) {
                tmp += grid[index_p+ GRID_SIZE_PADDED * i_loc] + grid[index_p + GRID_SIZE_PADDED * i_loc + 1] + \
                grid[index_p - GRID_SIZE_PADDED * i_loc - 1] ;
            }
            if(tmp) continue;
            for(int i_loc = 0; i_loc<length; i_loc++) grid[index_p+GRID_SIZE_PADDED*i_loc] = t;
            done =  true;
        }
        #ifdef DEBUG
        std::cout << "Iterations: " << iter << std::endl ;
        #endif 
    }

    inline int pad_index(const int index) {
        int i = 1 + index / GRID_SIZE; // i j just for convenience
        int j = 1 + index % GRID_SIZE;
        return (GRID_SIZE_PADDED * i + j) ;
    }

}
#endif
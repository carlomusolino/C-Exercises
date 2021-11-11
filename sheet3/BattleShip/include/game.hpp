#ifndef _MY_BATTLESHIP_GAME_
#define _MY_BATTLESHIP_GAME_
// stdlib includes first
#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <map>
#include <string>
// Then project specific includes
#include "ships.hpp"
#include "grids.hpp"

namespace BattleShip{
    enum gridpoint_status { miss=-1, null, hit, sunk  };
    static const std::array<std::string,NUM_SHIPS> status_indicator { "x", "~", "o", "*" };
    class BattleShipGame {
        Grid playing_field;
        Grid hidden_field;
        bool playing;
        int active_ships;
        public:
        // constructors
        BattleShipGame(std::array<int,NUM_SHIPS>& ship_numbers): playing(true), playing_field{Grid()}, hidden_field{Grid()}, active_ships(0) {
            for(int i = 1; i <= 5; i++){
                shiptypes ship = static_cast<shiptypes>(i);
                for (int n=0; n<ship_numbers[i]; n++) {
                    hidden_field.place_ship(ship);
                    active_ships++;
                }
            }
        }
        void play();
        inline void shoot(const int i, const letter j) {
            int index = coordinates(i,j);
            if(hidden_field.grid[index]){
             int tmp = playing_field.grid[index - 1] * playing_field.grid[index + 1] * playing_field.grid[index - GRID_SIZE_PADDED] * playing_field.grid[index + GRID_SIZE_PADDED];
             if (tmp>0){
                 playing_field.grid[index]=sunk ; 
                 active_ships--;
             }
             else playing_field.grid[index]=hit ; 
            }
             else playing_field.grid[index]=miss ;
        }
        inline void display_playing_field(){
            std::cout << std::endl << std::endl << "\t";
            for(int i = 0; i < GRID_SIZE_PADDED ; i++) for(int j =0; j < GRID_SIZE_PADDED; j++) {
                int status = playing_field.grid[j + i*GRID_SIZE_PADDED] ;
                std::cout  << status_indicator[status+1] << "\t";
                if(j==GRID_SIZE_PADDED-1) std::cout << std::endl << std::endl << "\t"  ;
            }
            std::cout << std::endl << std::endl ;
        }
        inline void update_status(){
            if(!active_ships) playing = false;
        }
    };
    void BattleShipGame::play(){
        
    }
}

#endif
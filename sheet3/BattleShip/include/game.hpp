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
        bool convert_to_letter(const std::string in, letter& out);
        bool is_sunk(const int index){
            bool sunk = true;
            int tmpindex = index - 1;
            if (hidden_field.grid[tmpindex]){
                if((!playing_field.grid[tmpindex]>0)) sunk = false;
            }
            tmpindex = index + 1;
            if (hidden_field.grid[tmpindex]){
                if((!playing_field.grid[tmpindex]>0)) sunk = false;
            }
            tmpindex = index + GRID_SIZE_PADDED;
            if (hidden_field.grid[tmpindex]){
                if((!playing_field.grid[tmpindex]>0)) sunk = false;
            }
            tmpindex = index - GRID_SIZE_PADDED;
            if (hidden_field.grid[tmpindex]){
                if((!playing_field.grid[tmpindex]>0)) sunk = false;
            }
            return sunk;
        }
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
        inline void display_playing_field(){
            std::cout << std::endl << std::endl << "\t";
            for(int i = 0; i < GRID_SIZE ; i++) for(int j =0; j < GRID_SIZE; j++) {
                int index = pad_index(j + i*GRID_SIZE);
                int status = playing_field.grid[index] ;
                std::cout  << status_indicator[status+1] << "\t";
                if(j==GRID_SIZE-1) std::cout << std::endl << std::endl << "\t"  ;
            }
            std::cout << std::endl << std::endl ;
        }
        inline void update_status(){
            if(!active_ships) playing = false;
        }
        void play();
        inline void shoot(const int i, const letter j) {
            int index = coordinates(i,j);
            if(hidden_field.grid[index]){
             //int tmp = playing_field.grid[index - 1] * playing_field.grid[index + 1] * playing_field.grid[index - GRID_SIZE_PADDED] * playing_field.grid[index + GRID_SIZE_PADDED];
             if (is_sunk(index)){
                std::cout << "\t\t***** Hit and sunk! *****\t\t" << std::endl;
                playing_field.grid[index]=sunk ; 
                active_ships--;
             }
             else{
                std::cout << "\t\t***** Hit! *****\t\t" << std::endl;
                playing_field.grid[index]=hit ; 
             }
            }
             else{
                std::cout << "\t\t***** Miss. *****\t\t" << std::endl;
                playing_field.grid[index]=miss ;
             }
        }
    };
    void BattleShipGame::play(){
        while(playing)
        {
            display_playing_field();
            std::cout << "Please enter a letter coordinate:"<<std::endl;
            std::string tmp;
            letter j;
            if (!(std::cin>>tmp)){
                std::cout << "Out of range!" << std::endl;
                continue;
            } else if(!convert_to_letter(tmp,j)){
                std::cout << "Out of range!" << std::endl;
                continue;
            }
            std::cout << "Please enter a number coordinate: "<<std::endl;
            unsigned int i;
            if (!(std::cin>>i)){
                std::cout << "Out of range!" << std::endl;
                continue;
            } else if(i>GRID_SIZE){
                std::cout << "Out of range!" << std::endl;
                continue;
            }

            shoot(i,j);
            update_status();
        }
        std::cout << "Thanks for playing!" << std::endl;
    }

    bool BattleShipGame::convert_to_letter(const std::string in, letter& out){
        std::map<std::string,letter> m {{"a",a}, {"b",b}, {"c",c}, {"d",d}, {"e",e}, {"f",f}, {"g",g}, {"h",h}, {"i",i}, {"l",l}};
        std::map<std::string,letter>::iterator it = m.begin();
        while(it != m.end()){
            if(in==it->first){
                out = it->second;
                return true;
            }
            it++;
        }
        return false;
    }
}

#endif
#include<iostream>
#include<array>

#include"include/game.hpp"
#include"include/grids.hpp"
#include"include/ships.hpp"
using namespace BattleShip;
int main(){
    std::array<int,NUM_SHIPS> num_of_ships{5,4,3,2,1};

    BattleShipGame game = BattleShipGame(num_of_ships);
    game.play();
}
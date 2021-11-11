#include<iostream>
#include "../include/grids.hpp"
#include "../include/ships.hpp"

using namespace BattleShip;
using std::cout, std::endl;

int main(){

    // define a Grid
    Grid playing_field;

    playing_field.place_ship(CARRIER);
    playing_field.place_ship(CARRIER);
    playing_field.place_ship(SUBMARINE);

    playing_field.display();

}
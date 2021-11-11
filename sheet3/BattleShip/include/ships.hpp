#ifndef _MY_SHIPS_
#define _MY_SHIPS_


namespace BattleShip {
    constexpr int NUM_SHIPS = 5 ;
    enum shiptypes {
        CARRIER = 1,
        BATTLESHIP,
        CRUISER,
        DESTROYER,
        SUBMARINE,
    };
    constexpr std::array<int,NUM_SHIPS> ship_length {5, 4, 3, 2, 1}; // note that order matters here! 
}

#endif 
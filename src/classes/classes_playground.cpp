#include "Building.hpp"
#include "Road.hpp"

#include <iostream>
#include <string> 

int main(void) {
    coordinates coords1;
    coords1.x = 5;
    coords1.y = 12;
    Building b1(coords1,100,80);

    coordinates coords2;
    coords2.x = 8;
    coords2.y = 16;
    Building b2(coords2,100,80);

    Road<Building,Building> r(b2,b1);
    std::cout << std::to_string(r.CalculateLength()) << std::endl;
}
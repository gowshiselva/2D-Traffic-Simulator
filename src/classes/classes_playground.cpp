#include "Intersection.hpp"
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

    coordinates coords3;
    coords3.x = 5;
    coords3.y = 12;
    Intersection i1(coords3);
    std::cout << std::to_string(i1.GetCoordinates().x) << std::endl;

    Road<Intersection,Building> r(i1,b2);
    std::cout << std::to_string(r.CalculateLength()) << std::endl;
    

}
#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include "coordinates.h"
#include "Building.hpp"
#include "Intersection.hpp"
#include "Road.hpp"
#include "Passenger.hpp"

class Vehicle: public sf::RectangleShape
{
    public: 
    // color has to be defined as sf:: data e.g sf::Color::Blue
        Vehicle(coordinates coords, Passenger& passenger);
        bool destinationReached();
        void updatePosition();
        coordinates GetCoordinates() const;
        void SetDestination(Building dest);
        Building GetDestination();
        Passenger GetPassenger();
        std::vector<Intersection> GetPath(Building start, Building end, std::vector<Intersection> intersections, std::vector<SideRoad> side_roads, std::vector<MainRoad> main_roads);

    private:
        void constructPath();
        bool destReached=false;
        coordinates coordinates_;
        Building destination_;
        Passenger passenger_;
   
    
};
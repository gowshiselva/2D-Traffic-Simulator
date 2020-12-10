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
        void SetCoordinates(coordinates coords);
        void SetDestination(Building dest);
        Building GetDestination();
        Passenger GetPassenger();
        std::vector<Intersection> CalculatePath(Building start, Building end, std::vector<std::shared_ptr<Intersection>> intersections, std::vector<SideRoad> side_roads, std::vector<MainRoad> main_roads);
        void SetPath(std::vector<Intersection> path);
        std::vector<Intersection> GetPath();
        void SetLastIntersection(Intersection intersection);
        Intersection GetLastIntersection();
        void SetDrivingFromBuilding(bool b);
        bool GetDrivingFromBuilding();
        void SetStart(Building start);
        Building GetStart();
        bool Drive(int speed, Intersection start, Intersection end);
        void DriveToBuilding(int speed, Intersection start, Building end);
        void DriveFromBuilding(int speed, Building start, Intersection end);


    private:
        void constructPath();
        bool destReached=false;
        coordinates coordinates_;
        Building destination_;
        Building start_;
        Passenger passenger_;
        std::vector<Intersection> path_;
        Intersection last_intersection_;
        bool driving_from_building_;
   
    
};
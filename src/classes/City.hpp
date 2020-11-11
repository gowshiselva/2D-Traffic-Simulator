#pragma once
#include <vector>
#include <memory>

#include "coordinates.h"
#include "Building.hpp"
#include "Intersection.hpp"
#include "Passenger.hpp"
#include "Road.hpp"

class City {
    public:
        City(){}
        City(std::vector<std::shared_ptr<Building>> buildings,
            std::vector<std::shared_ptr<Intersection>> intersections,
            std::vector<std::shared_ptr<Passenger>> passengers,
            std::vector<std::shared_ptr<Road>> roads);

        std::vector<std::shared_ptr<Building>> GetBuildings() const;
        std::vector<std::shared_ptr<Intersection>> GetIntersections() const;
        std::vector<std::shared_ptr<Passenger>> GetPassengers() const;
        std::vector<std::shared_ptr<Road>> GetRoads() const;

    private:
        std::vector<std::shared_ptr<Building>> buildings_;
        std::vector<std::shared_ptr<Intersection>> intersections_;
        std::vector<std::shared_ptr<Passenger>> passengers_;
        std::vector<std::shared_ptr<Road>> roads_;
};
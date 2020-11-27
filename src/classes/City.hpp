#pragma once
#include <vector>
#include <memory>

#include "coordinates.h"
#include "Building.hpp"
#include "Intersection.hpp"
#include "Passenger.hpp"
#include "Road.hpp"

template <typename T1, typename T2>
class City {
    public:
        City(){}
        City(std::vector<std::shared_ptr<Building>> buildings,
            std::vector<std::shared_ptr<Intersection>> intersections,
            std::vector<std::shared_ptr<Passenger>> passengers,
            std::vector<std::shared_ptr<Road<T1,T2>>> roads)
            : buildings_(buildings), intersections_(intersections), passengers_(passengers), roads_(roads) {}

        std::vector<std::shared_ptr<Building>> GetBuildings() const {
            return buildings_;
        }

        std::vector<std::shared_ptr<Intersection>> GetIntersections() const {
            return intersections_;
        }

        std::vector<std::shared_ptr<Passenger>> GetPassengers() const {
            return passengers_;
        }

        std::vector<std::shared_ptr<Road<T1,T2>>> GetRoads() const {
            return roads_;
        }

    private:
        std::vector<std::shared_ptr<Building>> buildings_;
        std::vector<std::shared_ptr<Intersection>> intersections_;
        std::vector<std::shared_ptr<Passenger>> passengers_;
        std::vector<std::shared_ptr<Road<T1,T2>>> roads_;
};
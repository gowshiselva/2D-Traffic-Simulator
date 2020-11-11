#include<City.hpp>

City::City(std::vector<std::shared_ptr<Building>> buildings,
            std::vector<std::shared_ptr<Intersection>> intersections,
            std::vector<std::shared_ptr<Passenger>> passengers,
            std::vector<std::shared_ptr<Road>> roads)
    : buildings_(buildings), intersections_(intersections), passengers_(passengers), roads_(roads) {}

std::vector<std::shared_ptr<Building>> City::GetBuildings() const {
    return buildings_;
}

std::vector<std::shared_ptr<Intersection>> City::GetIntersections() const {
    return intersections_;
}

std::vector<std::shared_ptr<Passenger>> City::GetPassengers() const {
    return passengers_;
}

std::vector<std::shared_ptr<Road>> City::GetRoads() const {
    return roads_;
}
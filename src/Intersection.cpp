#include <vector>
#include "Intersection.hpp"
#include "Road.hpp"


Intersection::Intersection(int id, coordinates coords)
    : id_(id), coordinates_(coords) {}

int Intersection::GetId() const {
    return id_;
}

coordinates Intersection::GetCoordinates() const {
    return coordinates_;
}

std::vector<Intersection> Intersection::GetNeighbors(std::vector<MainRoad> main_roads) const {
    std::vector<Intersection> neighbors;
    for(auto road: main_roads) {
        if (road.GetStart().GetId() == GetId()) {
            neighbors.push_back(road.GetEnd());
        } else if(road.GetEnd().GetId() == GetId()) {
            neighbors.push_back(road.GetStart());
        }
    }
    return neighbors;
}
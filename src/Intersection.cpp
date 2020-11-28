#include "Intersection.hpp"

Intersection::Intersection(int id, coordinates coords)
    : id_(id), coordinates_(coords) {}

int Intersection::GetId() const {
    return id_;
}

coordinates Intersection::GetCoordinates() const {
    return coordinates_;
}

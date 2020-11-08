#include "Intersection.hpp"

Intersection::Intersection(coordinates coords)
    : coordinates_(coords) {}

coordinates Intersection::GetCoordinates() const {
    return coordinates_;
}

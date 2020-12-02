#pragma once
#include "coordinates.h"

class MainRoad;

class Intersection {
    public:
        Intersection(int id, coordinates coords);
        int GetId() const;
        coordinates GetCoordinates() const;
        std::vector<Intersection> GetNeighbors(std::vector<MainRoad> main_roads) const;

    private:
        int id_;
        coordinates coordinates_;
};
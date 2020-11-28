#pragma once
#include "coordinates.h"

class Intersection {
    public:
        Intersection(int id, coordinates coords);
        int GetId() const;
        coordinates GetCoordinates() const;

    private:
        coordinates coordinates_;
        int id_;
};
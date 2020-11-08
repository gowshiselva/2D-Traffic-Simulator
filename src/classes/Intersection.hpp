#pragma once
#include "coordinates.h"

class Intersection {
    public:
        Intersection(coordinates coords);
        
        coordinates GetCoordinates() const;

    private:
        coordinates coordinates_;
};
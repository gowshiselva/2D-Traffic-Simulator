#pragma once
#include "coordinates.h"
#include <cmath>
#include <memory>

template <typename T1, typename T2>
class Road {
    public:

    /*
    For Road class the methods are all defined here in the header file.
    This is because I had some trouble with the templates being in a separate file.
    */

        Road(T1 start, T2 end)
        : start_(std::make_shared<T1>(start)), end_(std::make_shared<T2>(end)) {}

        T1 GetStart() const {
            return *start_;
        }

        T2 GetEnd() const {
            return *end_;
        }

        double CalculateLength() {
            coordinates start_coords = GetStart().GetCoordinates();
            coordinates end_coords = GetEnd().GetCoordinates();
            return sqrt(pow(end_coords.x-start_coords.x,2)+pow(end_coords.y-start_coords.y,2));
        }

    private:
        std::shared_ptr<T1> start_;
        std::shared_ptr<T2> end_;
};
#pragma once
#include "coordinates.h"
#include <cmath>
#include <memory>

/* template <typename T1, typename T2>
class Road {
    public:

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
}; */

class MainRoad {
    public:

        MainRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Intersection> end)
        : start_(start), end_(end) {}

        Intersection GetStart() const {
            return *start_;
        }

        Intersection GetEnd() const {
            return *end_;
        }

        double CalculateLength() {
            coordinates start_coords = GetStart().GetCoordinates();
            coordinates end_coords = GetEnd().GetCoordinates();
            return sqrt(pow(end_coords.x-start_coords.x,2)+pow(end_coords.y-start_coords.y,2));
        }

    private:
        std::shared_ptr<Intersection> start_;
        std::shared_ptr<Intersection> end_;
};

class SideRoad {
    public:

        SideRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Building> end)
        : start_(start), end_(end) {}

        Intersection GetStart() const {
            return *start_;
        }

        Building GetEnd() const {
            return *end_;
        }

        double CalculateLength() {
            coordinates start_coords = GetStart().GetCoordinates();
            coordinates end_coords = GetEnd().GetCoordinates();
            return sqrt(pow(end_coords.x-start_coords.x,2)+pow(end_coords.y-start_coords.y,2));
        }

    private:
        std::shared_ptr<Intersection> start_;
        std::shared_ptr<Building> end_;
};
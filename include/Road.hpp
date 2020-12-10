#pragma once
#include "coordinates.h"
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>

class Intersection;
class Building;


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

class MainRoad: public sf::RectangleShape {
    public:

        MainRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Intersection> end, int id);

        Intersection GetStart() const;

        Intersection GetEnd() const;
        int GetId() const;
        std::vector<int> GetStatistics();
        std::vector<int> GetCarCounter();
        void IncrementCarCounter(int hour);
        double CalculateLength() const;

    private:
        std::shared_ptr<Intersection> start_;
        std::shared_ptr<Intersection> end_;
        int id_;
        std::vector<int> car_counter_;
};

class SideRoad: public sf::RectangleShape {
    public:

        SideRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Building> end);

        Intersection GetStart() const;

        Building GetEnd() const;

        double CalculateLength() const;
    private:
        std::shared_ptr<Intersection> start_;
        std::shared_ptr<Building> end_;
};
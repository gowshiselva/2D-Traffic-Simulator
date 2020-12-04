#pragma once
#include "coordinates.h"
#include <cmath>
#include <memory>
#include "Building.hpp"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

class Intersection;


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

        MainRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Intersection> end)
        :RectangleShape(sf::Vector2f(0, 0)), start_(start), end_(end) {
            coordinates startc = start->GetCoordinates();
            coordinates endc = end->GetCoordinates();
            int startX = std::min(startc.x, endc.x);
            int startY = std::min(startc.y, endc.y);
            int endX = std::max(startc.x, endc.x);
            int endY = std::max(startc.y, endc.y);
            int width = endX - startX; 
            int height = endY - startY;
            if(width == 0) width += 5;
            if(height == 0) height += 5;
            this->setSize(sf::Vector2f(width, height));
            this->setFillColor(sf::Color(100, 250, 50));
            this->setPosition((float)startX, (float)startY);
        }

        Intersection GetStart() const {
            return *start_;
        }

        Intersection GetEnd() const {
            return *end_;
        }

        std::vector<int> GetStatistics(){
            return std::vector<int>{1,2,3,4,3,2,1};
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

class SideRoad: public sf::RectangleShape {
    public:

        SideRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Building> end)
        :RectangleShape(sf::Vector2f(0, 0)), start_(start), end_(end) {
            coordinates startc = start->GetCoordinates();
            coordinates endc = end->GetCoordinates();
            int startX = std::min(startc.x, endc.x);
            int startY = std::min(startc.y, endc.y);
            int endX = std::max(startc.x, endc.x);
            int endY = std::max(startc.y, endc.y);
            int width = endX - startX; 
            int height = endY - startY;
            if(width == 0) width += 2;
            if(height == 0) height += 2;

            this->setSize(sf::Vector2f(width, height));
            this->setFillColor(sf::Color(250, 0, 0));
            this->setPosition((float)startX, (float)startY);
        }

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
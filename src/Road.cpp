#include "coordinates.h"
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "Road.hpp"
#include "Building.hpp"
#include "Intersection.hpp"


MainRoad::MainRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Intersection> end, int id)
        :RectangleShape(sf::Vector2f(0, 0)), start_(start), end_(end), id_(id), car_counter_(std::vector<int> (24)) {
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

Intersection MainRoad::GetStart() const {
    return *start_;
}

Intersection MainRoad::GetEnd() const {
    return *end_;
}

int MainRoad::GetId() const {
    return id_;
}

double MainRoad::CalculateLength() const{
    coordinates start_coords = GetStart().GetCoordinates();
    coordinates end_coords = GetEnd().GetCoordinates();
    return sqrt(pow(end_coords.x-start_coords.x,2)+pow(end_coords.y-start_coords.y,2));
}

std::vector<int> MainRoad::GetCarCounter() {
    return car_counter_;
}

void MainRoad::IncrementCarCounter(int hour) {
    car_counter_[hour]++;
}


SideRoad::SideRoad(std::shared_ptr<Intersection> start, std::shared_ptr<Building> end)
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

Intersection SideRoad::GetStart() const {
    return *start_;
}

Building SideRoad::GetEnd() const {
    return *end_;
}

double SideRoad::CalculateLength() const {
    coordinates start_coords = GetStart().GetCoordinates();
    coordinates end_coords = GetEnd().GetCoordinates();
    return sqrt(pow(end_coords.x-start_coords.x,2)+pow(end_coords.y-start_coords.y,2));
}

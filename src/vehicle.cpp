#include "vehicle.h"
#include <SFML/Graphics.hpp>

Vehicle::Vehicle(coordinates coords, Passenger& passenger):
    RectangleShape(sf::Vector2f(5, 5)), coordinates_(coords), passenger_(passenger)
    {
        this->setFillColor(sf::Color(50, 50, 250));
        this->setPosition(coords.x, (coords.y));
    }

coordinates Vehicle::GetCoordinates() const {
    return coordinates_;
}

bool Vehicle::destinationReached()
{
  return destReached;
}

void Vehicle::SetDestination(Building dest){
  this->destination_ = dest;
}

Building Vehicle::GetDestination(){
  return this->destination_;
}

Passenger Vehicle::GetPassenger(){
  return this->passenger_;
}
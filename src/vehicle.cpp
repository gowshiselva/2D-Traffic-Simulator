#include "vehicle.h"
#include <SFML/Graphics.hpp>

Vehicle::Vehicle(unsigned int height, unsigned int width, sf::Color color):
    height_(height), width_(width), color_(color), m_size(width, height)
{
  update();
}
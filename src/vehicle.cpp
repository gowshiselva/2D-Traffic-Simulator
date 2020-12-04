#include "vehicle.h"
#include <SFML/Graphics.hpp>

Vehicle::Vehicle(unsigned int height, unsigned int width, sf::Color color):
    height_(height), width_(width), color_(color), m_size(width, height)
{
  update();  
}

void Vehicle::setColor(color)
{
  color_=color;
}

bool Vehicle::destinationReached()
{
  return destReached;
}

void Vehicle::setSize(sf::Vector2f size)
{
  m_size=sf::Vector2f(size);
}

void Vehicle::Draw(sf::RenderTarget& window)
{
    Next();
    window.draw(this);
}


#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
class Vehicle:public sf::Shape
{
    public: 
    // color has to be defined as sf:: data e.g sf::Color::Blue
    Vehicle(unsigned int height, unsigned int width, sf::Color color=sf::Color::Blue);
    void setSize();
    void setColor();
    bool destinationReached();
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    void updatePosition();

    private:
     void constructPath();
     unsigned int height_;
     unsigned int width_;
     sf::Color color_;
     sf::Vector2f m_size;
     bool destReached=false;
     //route
     //previous node
     //current node
     //next node
    
};
#include "map.h"
#include <SFML/Graphics.hpp>
#include <memory.h>
#include <stdio.h>
#include <iostream>
Map::Map(unsigned int width, unsigned int height, std::string message):width_(width), height_(height), message_(message)
{
    this->initMap();

    
}

void Map::initMap()   
{
  
  /*
  create a sfml window to create the map
  */
    this->window_ = new sf::RenderWindow(sf::VideoMode(width_, height_), "SFML window");
    this->roads_ = std::vector<sf::RectangleShape*>();

    sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(120.f, 50.f));
    rectangle->setFillColor(sf::Color(100, 250, 50));
    rectangle->setPosition(5.f, 5.f);
    this->roads_.push_back(rectangle);
   
}

void Map::run()
{
  while(this->window_->isOpen())
     {
       this->update();
       this->render();
     }
}

void Map::update()
{
    this->updateSFMLEvent();

}

void Map::render()
{
    this->window_->clear();

    for(auto road: this->roads_){
        this->window_->draw(*road);
    }

    this->window_->display();

}
void Map::updateSFMLEvent()
{
    while(this->window_->pollEvent(this->event_))
        {
            if(this->event_.type==sf::Event::Closed)
            {
                this->window_->close();
            }
            if (this->event_.type == sf::Event::MouseButtonPressed)
            {
                if (this->event_.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    sf::Vector2i localPosition =sf::Mouse::getPosition(*this->window_);
                    for(auto shape: this->roads_){
                        sf::FloatRect bounds = shape->getLocalBounds();
                        if(localPosition.x > bounds.left && localPosition.x < bounds.left+bounds.width && localPosition.y > bounds.top && localPosition.y < bounds.top + bounds.height){
                            if(shape->getFillColor() == sf::Color(100, 250, 50)){
                                shape->setFillColor(sf::Color(250, 250, 250));
                                std::cout << "set color1" <<  std::endl;
                            }else{
                                shape->setFillColor(sf::Color(100, 250, 50));
                                std::cout << "set color2" <<  std::endl;
                            }
                            //std::cout << "rect clicked" <<  std::endl;
                        }   
                    }
                    
                }
            }
            
        }
}
Map::~Map()
{
    delete this->window_;
}



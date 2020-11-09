#include "map.h"
#include <SFML/Graphics.hpp>
#include <memory.h>
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
            
        }
}
Map::~Map()
{
    delete this->window_;
}



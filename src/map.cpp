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
    rectangle->setPosition(10.f, 10.f);
    this->roads_.push_back(rectangle);
    //this->addVehicle();
}



void Map::addCity(City& city){
    //std::cout << "Adding city, roads: " << city.GetMainRoads().size() << std::endl;
    this->city_ = city;
    for(auto road: city.GetMainRoads()){
        coordinates start = road.GetStart().GetCoordinates();
        coordinates end = road.GetEnd().GetCoordinates();
        int startX = std::min(start.x, end.x);
        int startY = std::min(start.y, end.y);
        int endX = std::max(start.x, end.x);
        int endY = std::max(start.y, end.y);
        int width = endX - startX; 
        int height = endY - startY;
        if(width == 0) width += 5;
        if(height == 0) height += 5;

        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(width, height));
        rectangle->setFillColor(sf::Color(100, 250, 50));
        std::cout << "added main road at" << startX << "," <<startY << ","<< width << ","<< height << std::endl;
        rectangle->setPosition((float)startX, (float)startY);
        this->roads_.push_back(rectangle);
    }

    for(auto road: city.GetSideRoads()){
        coordinates start = road.GetStart().GetCoordinates();
        coordinates end = road.GetEnd().GetCoordinates();
        int startX = std::min(start.x, end.x);
        int startY = std::min(start.y, end.y);
        int endX = std::max(start.x, end.x);
        int endY = std::max(start.y, end.y);
        int width = endX - startX; 
        int height = endY - startY;
        if(width == 0) width += 2;
        if(height == 0) height += 2;

        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(width, height));
        rectangle->setFillColor(sf::Color(250, 0, 0));
        std::cout << "added side road at" << startX << "," <<startY << ","<< width << ","<< height << std::endl;
        rectangle->setPosition((float)startX, (float)startY);
        this->roads_.push_back(rectangle);
    }
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
    
    //std::cout << "drawing roads: " << this->roads_.size() << std::endl;
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
                    sf::Vector2i localPosition =sf::Mouse::getPosition(*this->window_);
                    //std::cout << "the left button was pressed at "<< localPosition.x << "," <<  localPosition.y << std::endl;
                    for(auto shape: this->roads_){
                        sf::FloatRect bounds = shape->getGlobalBounds();
                        if(localPosition.x > bounds.left && localPosition.x < bounds.left+bounds.width && localPosition.y > bounds.top && localPosition.y < bounds.top + bounds.height){
                            
                            if(shape->getFillColor() == sf::Color(100, 250, 50)){
                                shape->setFillColor(sf::Color(250, 250, 250));
                            }else if(shape->getFillColor() == sf::Color(250, 250, 250)){
                                shape->setFillColor(sf::Color(100, 250, 50));
                            }else if(shape->getFillColor() == sf::Color(250, 0, 0)){
                                shape->setFillColor(sf::Color(100, 50, 250));
                            }else if(shape->getFillColor() == sf::Color(100, 50, 250)){
                                shape->setFillColor(sf::Color(250, 0, 0));
                            }
                            std::cout << "road clicked" <<  std::endl;
                        }   
                    }
                    
                }
            }
            
        }
}

/*void Map::addVehicle(const Vehicle& v)
{
  this->window_->draw(v);
}*/
Map::~Map()
{
    delete this->window_;
}



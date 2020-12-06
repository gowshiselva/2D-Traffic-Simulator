#include "map.h"
#include <SFML/Graphics.hpp>
#include <memory.h>
#include <stdio.h>
#include <iostream>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
Map::Map(unsigned int width, unsigned int height, std::string message):width_(width), height_(height), message_(message), vehicles_()
{

    this->initMap();
    
}

void Map::initMap()   
{
  
  /*
  create a sfml window to create the map
  */
    this->window_ = new sf::RenderWindow(sf::VideoMode(width_, height_), "SFML window");

    //this->addVehicle();
}



void Map::addCity(City& city){
    //std::cout << "Adding city, roads: " << city.GetMainRoads().size() << std::endl;
    this->city_ = city;
}

void Map::addVehicle(Vehicle* veh){
    this->vehicles_.push_back(veh);
}


void Map::removeVehicle(Vehicle* veh){
    std::vector<Vehicle*>::iterator position = std::find(this->vehicles_.begin(), this->vehicles_.end(), veh);
    if (position != this->vehicles_.end()) // == myVector.end() means the element was not found
        this->vehicles_.erase(position);
}

std::vector<Vehicle*> Map::getVehicles(){
    return this->vehicles_;
}

void Map::update()
{
    this->updateSFMLEvent();
    this->render();

}

void Map::render()
{
    this->window_->clear();
    
    for(auto road: this->city_.GetMainRoads()){
        this->window_->draw(road);
    }
    for(auto road: this->city_.GetSideRoads()){
        this->window_->draw(road);
    }
    
    for (auto vehicle :this->vehicles_)
    {   
        this->window_->draw(*vehicle);
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
                    for(auto road: this->city_.GetMainRoads()){
                        sf::FloatRect bounds = road.getGlobalBounds();
                        if(localPosition.x > bounds.left && localPosition.x < bounds.left+bounds.width && localPosition.y > bounds.top && localPosition.y < bounds.top + bounds.height){
                            
                            std::vector<int> stats = road.GetStatistics();
                            if(road.getFillColor() == sf::Color(100, 250, 50)){
                                road.setFillColor(sf::Color(250, 250, 250));
                            }else if(road.getFillColor() == sf::Color(250, 250, 250)){
                                road.setFillColor(sf::Color(100, 250, 50));
                            }else if(road.getFillColor() == sf::Color(250, 0, 0)){
                                road.setFillColor(sf::Color(100, 50, 250));
                            }else if(road.getFillColor() == sf::Color(100, 50, 250)){
                                road.setFillColor(sf::Color(250, 0, 0));
                            }
                            plt::plot(road.GetStatistics());
                            plt::show();
                            
                        }   
                    }
                    
                }
            }
            
        }
}

sf::RenderWindow* Map::getWindow(){
    return this->window_;
}


Map::~Map()
{
    delete this->window_;
}



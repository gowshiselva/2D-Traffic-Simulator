#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vehicle.h>
#include <string>
#include <memory.h>
#include <map>
#include <node.hpp>

class Map 
{

public:
    Map(unsigned int width=1000, unsigned int height=10000, std::string message="traffic simulator"  );
    void initMap();
    void render();
    void run();
    void update();
    void updateSFMLEvent();
    void makeCoordinates(); // divide the map into squares and derive coordinates
    //void closeMap();
    //void removeCar();
    //void updateMap();

    //void addVehicle();
   
    ~Map();
    unsigned int width_;
    unsigned int height_;
    std::string message_;
    private:
    //std::unique_ptr<sf::RenderWindow> window_;
    sf::RenderWindow *window_;
    std::vector<sf::RectangleShape*> roads_;
    sf::Event event_;
    sf::Clock clock_;
    float dt_;
    std::vector<std::unique_ptr<Vehicle>> vehicles_;
   // Vechicle v;
  //  std::map<int, Point*> coordinates_;
    //std::map<int car_id,std::unique_ptr<Car>> cars_; // store list of cars in the map
};

#endif
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vehicle.h>
#include <string>
#include <memory.h>
#include <map>
#include <node.hpp>
#include <City.hpp>

class Map 
{
  public:
      Map(unsigned int width=1000, unsigned int height=10000, std::string message="traffic simulator"  );
      void initMap();
      void render();
      void update();
      void updateSFMLEvent();
      void addRectangle(sf::RectangleShape*, int, int, int, int);
      void addCity(City*);
      void addVehicle(Vehicle*);
      void removeVehicle(Vehicle*);
      void incrementHoursPassed(int);
      std::vector<Vehicle*> getVehicles();
      void makeCoordinates(); // divide the map into squares and derive coordinates
      sf::RenderWindow* getWindow();
      ~Map();
      unsigned int width_;
      unsigned int height_;
      std::string message_;

      // Converts point on map to point on screen (coordinate -> pixel)
    sf::Vector2i convertCoordinateToPixel(const sf::Vector2f &point) const { return window_->mapCoordsToPixel(point); }
    // Converts point on screen to point on map (pixel -> coordinate)
    sf::Vector2f convertPixelToCoordinate(const sf::Vector2i &point) const { return window_->mapPixelToCoords(point); }
  private:
    //std::unique_ptr<sf::RenderWindow> window_;
    sf::RenderWindow *window_;
    City* city_;
    sf::Event event_;
    sf::Clock clock_;
    float dt_;
    std::vector<Vehicle*> vehicles_;
    std::vector<int> hours_passed_;
   
};

#endif
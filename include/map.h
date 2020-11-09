#include <SFML/Graphics.hpp>
#include <vehicle.h>
#include <string>
#include <memory.h>
class Map 
{

public:
    Map(unsigned int width=600, unsigned int height=600, std::string message="traffic simulator"  );
    void initMap();
    void render();
    void run();
    void update();
    void updateSFMLEvent();
    //void closeMap();
    //void removeCar();
    //void updateMap();

    //void addVehicle(const Vehicle& v)
   
    ~Map();
    unsigned int width_;
    unsigned int height_;
    std::string message_;
    private:
    //std::unique_ptr<sf::RenderWindow> window_;
    sf::RenderWindow *window_;
    sf::Event event_;
    sf::Clock clock_;
    float dt_;
    //std::map<int car_id,std::unique_ptr<Car>> cars_; // store list of cars in the map
};

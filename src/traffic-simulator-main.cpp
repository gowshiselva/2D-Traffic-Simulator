#include <iostream>
#include <string> 

#include <unistd.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "map.h"

#include "json2city.hpp"
#include "input2json.hpp"
#include <stdio.h>
#include <iostream>
#include <memory>
#define SPEED 4

using namespace std;
 int main(int argc, char *argv[])
{
  /* Open JSON file from either user command line input (e.g. ./traffic-simulator-main my_json_city.json)
     or if no user input generate a new json file based on information in the src/input_file.txt file. */
  /* From the JSON file create a city object containing all other objects (passengers, roads, etc.). */
  City city;
  if(argc>1) {
    std::string user_json_file(argv[1]);
    city = json2city(true, user_json_file);
  } else {
    city = json2city(false, "");
  }
  
  /* Map object is used for graphical rendering via SFML*/
  Map tf(city.GetCitySize().x, city.GetCitySize().y, "traffic simulator"); // tf: traffic simulator
  tf.addCity(&city);

  /* Main loop. */
  int time = 0; // The time in the city in minutes.
  std::cout << "running simulation with " << city.GetPassengers().size() << " passengers" << std::endl;
  std::vector<Intersection> path;

  /*Closing the window results in the program stopping.*/
  while(tf.getWindow()->isOpen()) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    tf.update();

    /*Cycle through all the passengers.*/
    for(uint16_t j=0; j<city.GetPassengers().size(); j++) {
      Passenger passenger = city.GetPassengers()[j];
      int go_work_time = passenger.GetLeaveHomeTime();
      int go_home_time = passenger.GetLeaveWorkTime();

      /*If passenger intends to go home at this time, they hop into a car and drive home.*/
      if(time == go_work_time && (passenger.GetPosition() == "home" || passenger.GetPosition() == "shop")) {
        city.SetPassengerPosition(passenger.GetId(), "travel_work");
        /*Create a new car object. We destroy the object once it has arrived to it's destination.*/
        Vehicle* car = new Vehicle(passenger.GetHome().GetCoordinates(), passenger);
        car->setColor(sf::Color::Red);
        car->SetDestination(passenger.GetWorkplace());
        /*Either going home from work or from the shop.*/
        if(passenger.GetPosition() == "home") {
          path = car->CalculatePath(passenger.GetHome(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
        } else {
          car->SetCoordinates(passenger.GetShop().GetCoordinates());
          path = car->CalculatePath(passenger.GetShop(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
        }
        car->SetPath(path);
        tf.addVehicle(car);
        /*Going to work*/
      } else if(time == go_home_time && (passenger.GetPosition() == "work" || passenger.GetPosition() == "shop")) {
        city.SetPassengerPosition(passenger.GetId(), "travel_home");
        Vehicle* car = new Vehicle(passenger.GetWorkplace().GetCoordinates(), passenger);
        car->setColor(sf::Color::Blue);
        car->SetDestination(passenger.GetHome());
        /*Again two possible starting locations.*/
        if(passenger.GetPosition() == "work") {
          path = car->CalculatePath(passenger.GetWorkplace(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
        } else {
          car->SetCoordinates(passenger.GetShop().GetCoordinates());
          path = car->CalculatePath(passenger.GetShop(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
        }
        car->SetPath(path);
        tf.addVehicle(car);
      /*Going shopping is the last alternative. This happens randomly (1:1000 chance to go shoppping each minute of the day).*/
      /*If the passenger is already on their way somewhere else, they don't go shopping.*/
      } else {
        if((passenger.GetPosition() == "work" || passenger.GetPosition() == "home") && passenger.GetShop().GetId() != passenger.GetWorkplace().GetId()) {
          float rand = RandomNumberGenerator();
          if (static_cast<int>(rand*1000) == 42) {
            city.SetPassengerPosition(passenger.GetId(), "travel_shop");
            Vehicle* car = new Vehicle(passenger.GetWorkplace().GetCoordinates(), passenger);
            car->setColor(sf::Color(11,111,0));
            car->SetDestination(passenger.GetShop());
            if(passenger.GetPosition() == "work") {
              path = car->CalculatePath(passenger.GetWorkplace(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
            } else {
              car->SetCoordinates(passenger.GetHome().GetCoordinates());
              path = car->CalculatePath(passenger.GetHome(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
            }
            car->SetPath(path);
            tf.addVehicle(car);
          }
        }
      }
    }
    /*Now cycle through all the cars on their way somewhere.*/
    for(auto car: tf.getVehicles()){
      coordinates position = car->GetCoordinates();      
      coordinates destination = car->GetDestination().GetCoordinates();
      /*If hasn't reached destination yet.*/
      if(position.x != destination.x || position.y != destination.y) {
        /*Path is a vetor of intersections.*/
        path = car->GetPath();
        for(uint16_t i=0; i<path.size(); ++i) {
          Intersection intersection = path[i];
          if(intersection.GetId() == car->GetLastIntersection().GetId()) {
            if(car->GetDrivingFromBuilding() == true) {
              /*Three types of driving from/to building and between intersections.*/
              car->DriveFromBuilding(SPEED,car->GetStart(),car->GetLastIntersection());
              break;
            }
            if(i>=path.size()-1) {
              car->DriveToBuilding(SPEED,car->GetLastIntersection(),car->GetDestination());
              break;
            }
            Intersection next_intersection = path[i+1];
            bool reached_next = car->Drive(SPEED,car->GetLastIntersection(),next_intersection);
            /*If reached next intersections from the path...*/
            if (reached_next == true) {
              int road_id = car->GetRoad(intersection, next_intersection, city.GetMainRoads());   
              int hour = static_cast<int>(std::floor(time/60));
              /*Increment road counter for the analytics tool. This happens when the car leaves the road.*/
              city.IncrementRoadCarCounter(road_id,hour);
              car->SetLastIntersection(next_intersection);
            }
            break;
          }
        }
      }else{
        /*The car has arrived to it's destination.*/
        city.SetPassengerPosition(car->GetPassenger().GetId(), "arrived");
        tf.removeVehicle(car);
      }
    }
    /*Print hour of the day.*/
    if(time%60 == 0){
      std::cout << "Time is: "<< time/60 << ":00" << std::endl;
      tf.incrementHoursPassed(time/60);
    }
    /*Dynamically sleep the program for smoother simulation.*/
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    long diff = 30000L-(long)std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
    long sleep = std::max(0L,diff);
    if(time>=1439) {
      time = 0;
      usleep(sleep);
      std::cout << "a day has passed" << std::endl;
    } else {
      time++;
      usleep(sleep);
    }
    
  }

}






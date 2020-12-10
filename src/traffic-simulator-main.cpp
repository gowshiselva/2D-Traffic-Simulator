#include <iostream>
#include <string> 
//#include "map.h"

#include <unistd.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include "map.h"

#include "json2city.hpp"
#include "input2json.hpp"
#include <stdio.h>
#include <iostream>

#define SPEED 4

using namespace std;
 int main(int argc, char *argv[])
{
  /* Open JSON file from either user command line input (e.g. ./traffic-simulator-main "my_json_city.json")
     or if no user input generate a new json file from the src/input_file.txt file. */
  /* From the JSON file create a city object containing all other objects (passengers, roads, etc.). */
  City city;
  if(argc>1) {
    std::string user_json_file(argv[1]);
    city = json2city(true, user_json_file);
  } else {
    city = json2city(false, "");
  }
  
  Map tf(city.GetCitySize().x, city.GetCitySize().y, "traffic simulator"); // tf: traffic simulator
  tf.addCity(&city);

  /* coordinates coords;
  coords.x = 10;
  coords.y = 10;
  Vehicle vehicle(coords,city.GetPassengers()[0]);
  Building a = *(city.GetBuildings()[0]);
  Building b = *(city.GetBuildings()[10]);
  std::vector<Intersection> path = vehicle.GetPath(a,b, city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());

  for(auto intersection: path) {
    std::cout << intersection.GetCoordinates().x << "," << intersection.GetCoordinates().y << std::endl;
  } */
  

    /* Main loop. */
  int time = 0; // The time in the city in minutes.
  std::cout << "running simulation with " << city.GetPassengers().size() << " passengers" << std::endl;
  std::vector<Intersection> path;
  while(tf.getWindow()->isOpen()) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    tf.update();
    for(uint16_t j=0; j<city.GetPassengers().size(); j++) {
      Passenger passenger = city.GetPassengers()[j];
      int leave_home_time = passenger.GetLeaveHomeTime();
      int leave_work_time = passenger.GetLeaveWorkTime();

      if(time == leave_home_time) {
        city.SetPassengerPosition(passenger.GetId(), "travel_work");
        Vehicle* car = new Vehicle(passenger.GetHome().GetCoordinates(), passenger);
        car->setColor(sf::Color::Red);
        car->SetDestination(passenger.GetWorkplace());
        //std::cout << passenger.GetHome().GetCoordinates().x << "," << passenger.GetHome().GetCoordinates().y << std::endl;
        //std::cout << car->GetDestination().GetCoordinates().x << "," << car->GetDestination().GetCoordinates().y << std::endl;
        path = car->CalculatePath(passenger.GetHome(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
        car->SetPath(path);
        tf.addVehicle(car);

      } else if(time == leave_work_time) {
        city.SetPassengerPosition(passenger.GetId(), "travel_home");
        Vehicle* car = new Vehicle(passenger.GetWorkplace().GetCoordinates(), passenger);
        car->setColor(sf::Color::Blue);
        car->SetDestination(passenger.GetHome());
        path = car->CalculatePath(passenger.GetWorkplace(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
        car->SetPath(path);
        tf.addVehicle(car);

      } else {
        if((passenger.GetPosition() == "work" || passenger.GetPosition() == "home") && passenger.GetShop().GetId() != passenger.GetWorkplace().GetId()) {
          float rand = RandomNumberGenerator();
        if (static_cast<int>(rand*1000) == 42) {
          city.SetPassengerPosition(passenger.GetId(), "travel_shop");

          Vehicle* car = new Vehicle(passenger.GetWorkplace().GetCoordinates(), passenger);
          car->setColor(sf::Color(11,111,0));
          if(passenger.GetPosition() == "work") {
            car->SetDestination(passenger.GetShop());
            path = car->CalculatePath(passenger.GetWorkplace(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
          } else {
            car->SetCoordinates(passenger.GetHome().GetCoordinates());
            car->SetDestination(passenger.GetShop());
            path = car->CalculatePath(passenger.GetHome(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
          }
          car->SetPath(path);
          tf.addVehicle(car);
        }
        }
      }
    }
    
    for(auto car: tf.getVehicles()){
      coordinates position = car->GetCoordinates();      
      coordinates destination = car->GetDestination().GetCoordinates();
      if(position.x != destination.x || position.y != destination.y) {
        // AN ALGORITHM WHICH WILL CALCULATE HOW TO GET FROM ONE POINT TO ANOTHER USING ROADS
        //std::cout << position.x << "," << position.y << std::endl;
        //std::cout << destination.x << "," << destination.y << std::endl;

        path = car->GetPath();
        for(uint16_t i=0; i<path.size(); ++i) {
          Intersection intersection = path[i];
          if(intersection.GetId() == car->GetLastIntersection().GetId()) {
            if(car->GetDrivingFromBuilding() == true) {
              car->DriveFromBuilding(SPEED,car->GetStart(),car->GetLastIntersection());
              break;
            }
            if(i>=path.size()-1) {
              car->DriveToBuilding(SPEED,car->GetLastIntersection(),car->GetDestination());
              break;
            }
            Intersection next_intersection = path[i+1];
            bool reached_next = car->Drive(SPEED,car->GetLastIntersection(),next_intersection);
            if (reached_next == true) {
              int road_id = car->GetRoad(intersection, next_intersection, city.GetMainRoads());   
              //std::cout << "id" << road_id << std::endl;          
              int hour = static_cast<int>(std::floor(time/60));
              //std::cout << "hour" << hour << std::endl;
              city.IncrementRoadCarCounter(road_id,hour);
              car->SetLastIntersection(next_intersection);
            }
            break;
          }
        }
      }else{
        city.SetPassengerPosition(car->GetPassenger().GetId(), "arrived");
        tf.removeVehicle(car);
      }
    }
    if(time%60 == 0){
      tf.incrementHoursPassed(time/60);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    long diff = 30000L-(long)std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
    long sleep = std::max(0L,diff);
    std::cout << "sleeping for: " << diff << "," << sleep << std::endl;
    if(time>=1439) {
      time = 0;
      usleep(sleep);
    } else {
      time++;
      std::cout << time << std::endl;
      usleep(sleep);
    }
    
  }
}






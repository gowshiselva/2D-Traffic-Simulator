#include <iostream>
#include <string> 
//#include "map.h"
#include "map.h"

#include "json2city.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;
 int main(int argc, char *argv[])
{
  Map tf; // tf: traffic simulator
    
   

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
  tf.addCity(city);

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
    tf.update();
    for(auto passenger: city.GetPassengers()) {
      int leave_home_time = passenger.GetLeaveHomeTime();
      int leave_work_time = passenger.GetLeaveWorkTime();
      if(time == leave_home_time) {
        if(passenger.GetPosition() == "home") {
          passenger.SetPosition("travelling");
          passenger.LeaveBuilding("home");
          /* ENTER CAR */
          Vehicle* car = new Vehicle(passenger.GetHome().GetCoordinates(), passenger);
          car->SetDestination(passenger.GetWorkplace());
          path = car->CalculatePath(passenger.GetHome(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
          car->SetPath(path);
          tf.addVehicle(car);
        } else {
          ;
        }
      } else if(time == leave_work_time) {
        if(passenger.GetPosition() == "workplace") {
          passenger.LeaveBuilding("workplace");
          passenger.SetPosition("travelling");
          /* ENTER CAR */
          Vehicle* car = new Vehicle(passenger.GetWorkplace().GetCoordinates(), passenger);
          car->SetDestination(passenger.GetHome());
          path = car->CalculatePath(passenger.GetHome(), car->GetDestination() , city.GetIntersections(), city.GetSideRoads(), city.GetMainRoads());
          car->SetPath(path);
          tf.addVehicle(car);
        } else {
          ;
        }
      }
    }
    
    for(auto car: tf.getVehicles()){
      coordinates position = car->GetCoordinates(); 
      coordinates destination = car->GetDestination().GetCoordinates();
      if(position.x != destination.x || position.y != destination.y) {
        // TO BE DONE: AN ALGORITHM WHICH WILL CALCULATE HOW TO GET FROM ONE POINT TO ANOTHER USING ROADS
        path = car->GetPath();
        for(uint16_t i=0; i<path.size(); ++i) {
          Intersection intersection = path[i];
          if(intersection.GetId() == car->GetLastIntersection().GetId()) {
            if(i>=path.size()-1) {
              break;
            }
            Intersection next_intersection = path[i+1];
            bool reached_next = car->Drive(1,car->GetLastIntersection(),next_intersection);
            if (reached_next == true) {
              car->SetLastIntersection(next_intersection);
            }
            break;
          }
        }
        //car.UpdatePosition  
      }else{
        //car->GetPassenger().EnterBuilding("");
        tf.removeVehicle(car);
      }

    }

    if(time>=1439) {
      time = 0;
    } else {
      time++;
    }
    
  }
}






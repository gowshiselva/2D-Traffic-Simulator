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

  /* Main loop. */
  int time = 0; // The time in the city in minutes.
  std::cout << "running simulation with " << city.GetPassengers().size() << " passengers" << std::endl;
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




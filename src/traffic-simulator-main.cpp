#include <iostream>
#include <string> 
//#include "map.h"
#include "map.h"

#include "json2city.hpp"

using namespace std;
 int main(int argc, char *argv[])
{
  /* Map tf; // tf: traffic simulator
  tf.run();
    std::cout<<"I am traffic simulator" << std::endl;
    return 0; */

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

  /* Main loop. */
  int time = 0; // The time in the city in minutes.

  while(true) {

    for(auto passenger: city.GetPassengers()) {
      int leave_home_time = passenger.GetLeaveHomeTime();
      int leave_work_time = passenger.GetLeaveWorkTime();
      if(time == leave_home_time) {
        if(passenger.GetPosition() == "home") {
          passenger.LeaveBuilding("home");
          /* ENTER CAR */
          /* CAR.set_destination(passenger.GetWorkplace()) */ 
        } else {
          ;
        }
      } else if(time == leave_work_time) {
        if(passenger.GetPosition() == "workplace") {
          passenger.LeaveBuilding("workplace");
          /* ENTER CAR */
          /* CAR.set_destination(passenger.GetHome()) */ 
        } else {
          ;
        }
      }
    }

    /* CAR LOOP HERE (pseudo):
    for car in city.GetCars {
      position = car.GetPosition(); 
      destination = car.GetDestination(); 
      
      if destination != null {
        // TO BE DONE: AN ALGORITHM WHICH WILL CALCULATE HOW TO GET FROM ONE POINT TO ANOTHER USING ROADS
        car.UpdatePosition  
      }

      if position == destination {
        car.destination = null;
        car.passenger.LeaveCar;
        car.passenger.EnterBuilding;
      }

    }
    */

    if(time>=1439) {
      time = 0;
    } else {
      time++;
    }
    
  }

}

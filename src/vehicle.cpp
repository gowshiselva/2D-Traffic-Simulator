#include "vehicle.h"
#include <queue>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Building.hpp"
#include "Intersection.hpp"
#include "Road.hpp"
#include "Passenger.hpp"

Vehicle::Vehicle(coordinates coords, Passenger& passenger):
    RectangleShape(sf::Vector2f(5, 5)), coordinates_(coords), passenger_(passenger)
    {
        this->setFillColor(sf::Color(50, 50, 250));
        this->setPosition(coords.x, (coords.y));
    }

coordinates Vehicle::GetCoordinates() const {
    return coordinates_;
}

void Vehicle::SetCoordinates(coordinates coords) {
    coordinates_.x = coords.x;
    coordinates_.y = coords.y;
    this->setPosition(coords.x, (coords.y));
}

bool Vehicle::destinationReached()
{
  return destReached;
}

void Vehicle::SetDestination(Building dest){
  this->destination_ = dest;
}

Building Vehicle::GetDestination(){
  return this->destination_;
}

Passenger Vehicle::GetPassenger(){
  return this->passenger_;
}

std::vector<Intersection> Vehicle::GetPath() {
  return this->path_; 
}

void Vehicle::SetPath(std::vector<Intersection> path) {
  this->path_ = path;
}

void Vehicle::SetLastIntersection(Intersection intersection) {
  this->last_intersection_ = intersection;
}

Intersection Vehicle::GetLastIntersection() {
  return this->last_intersection_;
}

bool Vehicle::GetDrivingFromBuilding() {
  return this->driving_from_building_;
}


void Vehicle::SetDrivingFromBuilding(bool b) {
  this->driving_from_building_ = b;
}

void Vehicle::SetStart(Building start) {
  this->start_ = start;
}

Building Vehicle::GetStart() {
  return this->start_;
}

bool Vehicle::Drive(int speed, Intersection start, Intersection end) {
  bool reached_end = false;
  coordinates current_coords = this->GetCoordinates();
  if(start.GetCoordinates().x == end.GetCoordinates().x) {
    if(start.GetCoordinates().y > end.GetCoordinates().y) {
      // Drive north.
      current_coords.y -= speed;
      if(current_coords.y <= end.GetCoordinates().y) {
        current_coords.y = end.GetCoordinates().y;
        reached_end = true;
      }
      this->SetCoordinates(current_coords);
    } else {
      // Drive south.
      current_coords.y += speed;
      if(current_coords.y >= end.GetCoordinates().y) {
        current_coords.y = end.GetCoordinates().y;
        reached_end = true;
      }
      this->SetCoordinates(current_coords);
    }
  } else {
    if(start.GetCoordinates().x > end.GetCoordinates().x) {
      // Drive west.
      current_coords.x -= speed;
      if(current_coords.x <= end.GetCoordinates().x) {
        current_coords.x = end.GetCoordinates().x;
        reached_end = true;
      }
      this->SetCoordinates(current_coords);
    } else {
      // Drive east.
      current_coords.x += speed;
      if(current_coords.x >= end.GetCoordinates().x) {
        current_coords.x = end.GetCoordinates().x;
        reached_end = true;
      }
      this->SetCoordinates(current_coords);
    }
  }
  return reached_end;
}

void Vehicle::DriveToBuilding(int speed, Intersection start, Building end) {
  coordinates current_coords = this->GetCoordinates();
  if(start.GetCoordinates().x == end.GetCoordinates().x) {
    if(start.GetCoordinates().y > end.GetCoordinates().y) {
      // Drive north.
      current_coords.y -= speed;
      if(current_coords.y <= end.GetCoordinates().y) {
        current_coords.y = end.GetCoordinates().y;
      }
      this->SetCoordinates(current_coords);
    } else {
      // Drive south.
      current_coords.y += speed;
      if(current_coords.y >= end.GetCoordinates().y) {
        current_coords.y = end.GetCoordinates().y;
      }
      this->SetCoordinates(current_coords);
    }
  } else {
    if(start.GetCoordinates().x > end.GetCoordinates().x) {
      // Drive west.
      current_coords.x -= speed;
      if(current_coords.x <= end.GetCoordinates().x) {
        current_coords.x = end.GetCoordinates().x;
      }
      this->SetCoordinates(current_coords);
    } else {
      // Drive east.
      current_coords.x += speed;
      if(current_coords.x >= end.GetCoordinates().x) {
        current_coords.x = end.GetCoordinates().x;
      }
      this->SetCoordinates(current_coords);
    }
  }
}

void Vehicle::DriveFromBuilding(int speed, Building start, Intersection end) {
  coordinates current_coords = this->GetCoordinates();
  if(start.GetCoordinates().x == end.GetCoordinates().x) {
    if(start.GetCoordinates().y > end.GetCoordinates().y) {
      // Drive north.
      current_coords.y -= speed;
      if(current_coords.y <= end.GetCoordinates().y) {
        current_coords.y = end.GetCoordinates().y;
        this->SetDrivingFromBuilding(false);
      }
      this->SetCoordinates(current_coords);
    } else {
      // Drive south.
      current_coords.y += speed;
      if(current_coords.y >= end.GetCoordinates().y) {
        current_coords.y = end.GetCoordinates().y;
        this->SetDrivingFromBuilding(false);
      }
      this->SetCoordinates(current_coords);
    }
  } else {
    if(start.GetCoordinates().x > end.GetCoordinates().x) {
      // Drive west.
      current_coords.x -= speed;
      if(current_coords.x <= end.GetCoordinates().x) {
        current_coords.x = end.GetCoordinates().x;
        this->SetDrivingFromBuilding(false);
      }
      this->SetCoordinates(current_coords);
    } else {
      // Drive east.
      current_coords.x += speed;
      if(current_coords.x >= end.GetCoordinates().x) {
        current_coords.x = end.GetCoordinates().x;
        this->SetDrivingFromBuilding(false);
      }
      this->SetCoordinates(current_coords);
    }
  }
}

std::vector<Intersection> Vehicle::CalculatePath(Building start, Building end, std::vector<std::shared_ptr<Intersection>> intersections, std::vector<SideRoad> side_roads, std::vector<MainRoad> main_roads) {
  Intersection start_intersection;
  Intersection end_intersection;

  if(start.GetId() == end.GetId()) {
    std::cout << "Same id" << std::endl;
  }
  
  // First replace start and end buildings with their neighbor intersections.
  for (auto intersection: intersections) {
    if (intersection->GetId() == start.GetNeighborIntersection(side_roads).GetId()) {
      start_intersection= *intersection;
    }
    if (intersection->GetId() == end.GetNeighborIntersection(side_roads).GetId()) {
      end_intersection = *intersection;
    }
  }

  this->SetStart(start);
  this->SetLastIntersection(start_intersection);
  this->SetDrivingFromBuilding(true);

  // BFS with intersections as nodes.
  std::queue<std::vector<Intersection>> queue;
  std::vector<Intersection> visited; 
  bool visited_bool = false;
  std::vector<Intersection> path;
  std::vector<Intersection> new_path;
  Intersection last_node;

  path.push_back(start_intersection);
  queue.push(path);

  while (!queue.empty()) {
    path = queue.front();
    queue.pop();
    last_node = path.back();
    visited.push_back(last_node);
    
    // Check if found end.
    std::cout<< last_node.GetId() << std::endl;
    std::cout<< end_intersection.GetId() << std::endl;
    if (last_node.GetId() == end_intersection.GetId()) {
      return path;
    }

    // If not add neighbors to path and continue.
    for (auto neighbor: last_node.GetNeighbors(main_roads)) {

      for (auto intersection: visited) {
        if (neighbor.GetId() == intersection.GetId()) {
          visited_bool = true;
          break;
        }
      }
      
      if (visited_bool == false) {
        new_path = path;
        new_path.push_back(neighbor);
        queue.push(new_path);
      }
      visited_bool = false;
    }

    

  }
  std::cout << "NO PATH FOUND" << std::endl;
  // If no path found return empty vector.
  std::vector<Intersection> empty;
  return empty;
}
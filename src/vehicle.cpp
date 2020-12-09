#include "vehicle.h"
#include <queue>
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

std::vector<Intersection> Vehicle::GetPath(Building start, Building end, std::vector<Intersection> intersections, std::vector<SideRoad> side_roads, std::vector<MainRoad> main_roads) {
  Intersection start_intersection;
  Intersection end_intersection;
  
  // First replace start and end buildings with their neighbor intersections.
  for (auto intersection: intersections) {
    if (intersection.GetId() == start.GetNeighborIntersection(side_roads).GetId()) {
      start_intersection= intersection;
    } else if (intersection.GetId() == end.GetNeighborIntersection(side_roads).GetId()) {
      end_intersection = intersection;
    }
  }

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
    
    // Check if found end.
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
    }

    visited_bool = false;

  }

  // If no path found return empty vector.
  std::vector<Intersection> empty;
  return empty;
}
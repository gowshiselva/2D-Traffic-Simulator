#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <random>
#include <iomanip>
#include <math.h>

#include "input2json.hpp"

#include "json.hpp"
using json = nlohmann::json;

#include "coordinates.h"
#include "timeschedule.h"
#include "City.hpp"

City json2city(bool user_input, std::string json_user_input) {

    std::ifstream json_file;
    if(user_input) {
        json_file.open(json_user_input, std::ifstream::in);
        if (json_file.rdstate() & (json_file.failbit | json_file.badbit)) {
            std::cerr << "User inputted JSON file opening failed." << std::endl;
        }
    } else {
        input2json();
        json_file.open("input.json", std::ifstream::in);
        if (json_file.rdstate() & (json_file.failbit | json_file.badbit)) {
            std::cerr << "Generated JSON file opening failed." << std::endl;
        }
    }
    json json_input = json::parse(json_file);
    
    std::vector<std::shared_ptr<Building>> buildings;
    std::vector<std::shared_ptr<Intersection>> intersections;
    std::vector<Passenger> passengers;
    std::vector<MainRoad> main_roads;
    std::vector<SideRoad> side_roads;

    for(auto building: json_input["buildings"]) {
        coordinates coords;
        coords.x = building["coordinates"]["x"];
        coords.y = building["coordinates"]["y"];
        std::shared_ptr<Building> b = std::make_shared<Building>(building["id"], coords, 0, building["people_capacity"], 0, building["car_capacity"], building["type"]);
        buildings.push_back(b);
    }

    for(auto intersection: json_input["intersections"]) {
        coordinates coords;
        coords.x = intersection["coordinates"]["x"];
        coords.y = intersection["coordinates"]["y"];

        std::shared_ptr<Intersection> i = std::make_shared<Intersection>(intersection["id"], coords);
        intersections.push_back(i);
    }

    for(auto passenger: json_input["passengers"]) {
        std::shared_ptr<Building> home;
        std::shared_ptr<Building> workplace;
        std::shared_ptr<Building> shop;
        timeschedule schedule;

        for(auto building: buildings) {
            if(building->GetId() == passenger["home"]) {
                home = building;
                building->IncrementPeopleAmount();
            }
            if(building->GetId() == passenger["work"]) {
                workplace = building;
            }
            if(building->GetId() == passenger["shop"]) {
                shop = building;
            }
        }

        schedule.leave_home = passenger["timeschedule"]["leave_home"];
        schedule.leave_work = passenger["timeschedule"]["leave_work"];

        Passenger p(home, workplace, shop, "home", schedule);
        passengers.push_back(p);
    }

    for(auto main_road: json_input["main_roads"]) {
        std::shared_ptr<Intersection> start;
        std::shared_ptr<Intersection> end;
        for(auto intersection: intersections) {
            if(intersection->GetId() == main_road["start"]) {
                start = intersection;
            }
            if(intersection->GetId() == main_road["end"]) {
                end = intersection;
            }
        }
        MainRoad r(start, end, main_road["id"]);
        main_roads.push_back(r);
    }

    for(auto side_road: json_input["side_roads"]) {
        std::shared_ptr<Intersection> start;
        std::shared_ptr<Building> end;

        for(auto intersection: intersections) {
            if(intersection->GetId() == side_road["start"]) {
                start = intersection;
            }
        }

        for(auto building: buildings) {
            if(building->GetId() == side_road["end"]) {
                end = building;
            }
        }

        SideRoad r(start, end);
        side_roads.push_back(r);
    }

    City city(buildings,intersections,passengers,main_roads,side_roads);
    return city;
}
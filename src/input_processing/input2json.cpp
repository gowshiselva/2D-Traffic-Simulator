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

#include "input_processing/nlohmann/json.hpp"
using json = nlohmann::json;

#include "amounts.h"
#include "classes/coordinates.h"

#define RESIDENTIAL_PROB 60
#define INDUSTRIAL_PROB 20
#define COMMERCIAL_PROB 20

int GenerateLeaveHome() {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{480,60};
    return(std::round(d(gen)));
}

int GenerateLeaveWork() {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{960,60};
    return(std::round(d(gen)));
}

float RandomNumberGenerator() {
    //std::srand(std::time(nullptr));  // set seed for rand function
    float rand_num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // random number between 0 and 1
    std::cerr<<rand_num<<std::endl;
    return rand_num;
}

int ChooseRandom(std::vector<int> buildings) {
    int rand = static_cast<int>(std::floor(RandomNumberGenerator()*buildings.size()));
    if(rand>=buildings.size()) {
        rand = static_cast<int>(buildings.size()-1);
    }
    return buildings[rand];
}

int CalculateCitySize(int density,int buildings_amount) {
    /* City is always square shaped, here we calculate the size of the side of the square. */
    float city_size = sqrt(buildings_amount);
    city_size = city_size*(150-density);
    return(static_cast<int>(city_size));
}

std::string GenerateBuildingType(int building_number) {
    if(building_number == 0) {
        return "residential";
    } else if(building_number == 1) {
        return "commercial";
    } else if(building_number == 2) {
        return "industrial";
    }
    float rand = 100*RandomNumberGenerator();
    if(rand<RESIDENTIAL_PROB) {
        return "residential";
    } else if(rand<(RESIDENTIAL_PROB+COMMERCIAL_PROB)) {
        return "commercial";
    } else {
        return "industrial";
    }
}

coordinates GenerateBuildingCoordinates(int city_size, int buildings_amount, int building_number) {
    int rows = static_cast<int>(std::round(sqrt(buildings_amount)));
    int cols = static_cast<int>(std::ceil(buildings_amount/rows));
    int row = static_cast<int>(std::floor(building_number/rows));
    int col = static_cast<int>(building_number%cols);
    int x_rand = static_cast<int>(std::floor(city_size/cols*RandomNumberGenerator()));
    int y_rand = static_cast<int>(std::floor(city_size/rows*RandomNumberGenerator()));
    int x_lower = static_cast<int>(std::floor(city_size/cols*col));
    int y_lower = static_cast<int>(std::floor(city_size/rows*row));
    coordinates coords;
    coords.x = x_rand+x_lower;
    coords.y = y_rand+y_lower;
    return coords;
}

int main(void) {
    /* First read lines from input file to a vector of pairs. */
    std::ifstream input_file_stream;
    input_file_stream.open("input_file.txt", std::ios::in);
    std::vector<std::pair<std::string, int>> lines;
    std::string line;
    std::string line_str;
    int line_int;

    /* if (!input_file_stream) {
        std::cerr << "Unable to open file input_file.txt";
        exit(1);   
    } */

    while (std::getline(input_file_stream,line))
    {
        line_str = line.substr(0, line.find(" "));
        line_int = std::stoi(line.substr(line.find(" ")));
        std::pair<std::string, int> line_pair = std::make_pair(line_str, line_int);
        if(line_str.size() > 0) {
            lines.push_back(line_pair);
        }
    }
    input_file_stream.close();

    /* Load from pairs to struct. */
    amounts amounts_struct = amounts_default;
    
    std::string object;
    int amount;
    for(auto i:lines) {
        object = i.first;
        amount = i.second;
        
        if(object=="Density" || object=="density") {
            amounts_struct.density = amount;
        } else if(object=="Buildings" || object=="buildings") {
            if(amount<3) {
                amount = 3;     // Can't have less than 3 buildings.
            }
            amounts_struct.buildings = amount;
        } else if(object=="Passengers" || object=="passengers") {
            amounts_struct.passengers = amount;
        }
    }

    /* Calculate city size. */
    int city_size = CalculateCitySize(amounts_struct.density, amounts_struct.buildings);

    /* Create JSON here. */
    json output;
    json building;
    coordinates coords;
    std::vector<int> residential_buildings;
    std::vector<int> commercial_buildings;
    std::vector<int> industrial_buildings;
    for(int i=0; i<amounts_struct.buildings; i++) {
        building["id"] = i;
        coords = GenerateBuildingCoordinates(city_size, amounts_struct.buildings, i);
        building["coordinates"]["x"] = coords.x;
        building["coordinates"]["y"] = coords.y;
        std::string building_type = GenerateBuildingType(i);
        building["type"] = building_type;

        if(building_type == "residential") {
            residential_buildings.push_back(i);
        } else if(building_type == "commercial") {
            commercial_buildings.push_back(i);
        } else {
            industrial_buildings.push_back(i);
        }

        building["people_capacity"] = 1000; //provisional
        output["buildings"].push_back(building);
    }

    json passenger;
    for(int i=0; i<amounts_struct.passengers; i++) {
        passenger["id"] = i;
        passenger["home"] = ChooseRandom(residential_buildings);
        passenger["work"] = ChooseRandom(industrial_buildings);
        passenger["shop"] = ChooseRandom(commercial_buildings);
        passenger["timeschedule"]["leave_home"] = GenerateLeaveHome();
        passenger["timeschedule"]["leave_work"] = GenerateLeaveWork();
        output["passengers"].push_back(passenger);
    }

    std::ofstream o("test.json");
    o << std::setw(4) << output << std::endl;
    o.close();
}
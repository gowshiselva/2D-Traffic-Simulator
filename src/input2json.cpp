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

#include "json.hpp"
using json = nlohmann::json;

#include "amounts.h"
#include "coordinates.h"

#include "input2json.hpp"

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
    return rand_num;
}

int GetRoadStatus(int x, int y, std::string direction, int map_size, int step_size) { // 0...free, 1...occupied, 2...not available
    if (direction == "n") {
        if (y - step_size < 0) {
            return 2;
        }
    } else if (direction == "e") {
        if (x + step_size >= map_size) {
            return 2;
        }
    } else if (direction == "s") {
        if (y + step_size >= map_size) {
            return 2;
        }
    } else {
        if (x - step_size < 0) {
            return 2;
        }
    }
    return 0;
}

int StepX(std::string direction, int x, int step_size) {
    if(direction == "e") {
        return(x+step_size);
    } else if(direction == "w") {
        return(x-step_size);
    } else {
        return(x);
    }
}

int StepY(std::string direction, int y, int step_size) {
    if(direction == "n") {
        return(y-step_size);
    } else if(direction == "s") {
        return(y+step_size);
    } else {
        return(y);
    }
}

std::string ChooseDirection(json intersection) {
    std::vector<std::string> directions;
        if(intersection["road_directions"]["n"] == 0) {
            directions.push_back("n");
        }
        if(intersection["road_directions"]["e"] == 0) {
            directions.push_back("e");
        }
        if(intersection["road_directions"]["s"] == 0) {
            directions.push_back("s");
        }
        if(intersection["road_directions"]["w"] == 0) {
            directions.push_back("w");
        }

    int i = static_cast<int>(std::floor(RandomNumberGenerator()*directions.size()));
    std::string direction = directions[i];
    return direction;
}

int ChooseRandom(std::vector<int> buildings) {
    int rand = static_cast<int>(std::floor(RandomNumberGenerator()*buildings.size()));
    if(rand>=static_cast<int>(buildings.size())) {
        rand = static_cast<int>(buildings.size()-1);
    }
    return buildings[rand];
}

int ChooseRandomIndexFromJsonArray(json json_array) {
    int rand = static_cast<int>(std::floor(RandomNumberGenerator()*json_array.size()));
    if(rand>=static_cast<int>(json_array.size())) {
        rand = static_cast<int>(json_array.size()-1);
    }
    return rand;
}

int ChooseRandomNonfullIntersection(json intersections) {
    bool found = false;
    while(!found) {
        int i = ChooseRandomIndexFromJsonArray(intersections);
        if (intersections[i]["road_directions"]["n"] == 0 ||
        intersections[i]["road_directions"]["e"] == 0 ||
        intersections[i]["road_directions"]["s"] == 0 ||
        intersections[i]["road_directions"]["w"] == 0) {
            return i;
        }
    }
    return -1;
}

int CalculateMapSize(int density,int city_size) {
    /* City is always square shaped, here we calculate the size of the side of the square. */
    int map_size = 10+city_size;
    map_size = static_cast<int>(std::round(map_size*(60-density/2)));
    return(map_size);
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

std::string ReverseDirection(std::string direction) {
    if (direction == "n") {
        return "s";
    } else if (direction == "s") {
        return "n";
    } else if (direction == "e") {
        return "w";
    } else {
        return "e";
    }
}

/* coordinates GenerateBuildingCoordinates(int city_size, int buildings_amount, int building_number) {
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
} */
coordinates GenerateBuildingCoordinates(int x, int y, std::string direction, int step_size) {
    coordinates coords;
    if (direction == "n") {
        coords.x = x;
        coords.y = y-step_size;
    } else if (direction == "e") {
        coords.x = x+step_size;
        coords.y = y;
    } else if (direction == "s") {
        coords.x = x;
        coords.y = y+step_size;
    } else {
        coords.x = x-step_size;
        coords.y = y;
    }
    return coords;
}

json GenerateSkeleton(int city_size, int map_size) {
    int intersections_amount = city_size;
    int step_size = map_size/intersections_amount;
    json intersection;
    json intersections;
    json base_road;
    json base_roads;

    // First create one intersection in the middle of the grid.
    intersection["id"] = 0;
    intersection["coordinates"]["x"] = static_cast<int>(std::floor(map_size/2));
    intersection["coordinates"]["y"] = static_cast<int>(std::floor(map_size/2));
    intersection["road_directions"]["n"] = 0;
    intersection["road_directions"]["e"] = 0;
    intersection["road_directions"]["s"] = 0;
    intersection["road_directions"]["w"] = 0;
    intersections.push_back(intersection);

    while (static_cast<int>(static_cast<int>(intersections.size())) < intersections_amount) {
        int existing_intersection_index = ChooseRandomNonfullIntersection(intersections);
        try {
            if (existing_intersection_index < 0) {
                throw (existing_intersection_index);
            }
        }
        catch (int index) {
            std::cout << "No empty existing intersection found, that is an error.\n" << std::endl;
        } 
        json& existing_intersection = intersections[existing_intersection_index];

        std::string direction = ChooseDirection(existing_intersection);
        existing_intersection["road_directions"][direction] = 1;
        base_road["id"] = base_roads.size();
        base_road["start_x"] = existing_intersection["coordinates"]["x"];
        base_road["start_y"] = existing_intersection["coordinates"]["y"];
        base_road["start"] = existing_intersection["id"];

        int new_x = StepX(direction, existing_intersection["coordinates"]["x"], step_size);
        int new_y = StepY(direction, existing_intersection["coordinates"]["y"], step_size);
        bool occupied = false;
        int i = 0;
        for (auto it = intersections.begin(); it != intersections.end(); ++it, ++i) {
            auto & intersect = *it;

            if(intersect["coordinates"]["x"] == new_x && intersect["coordinates"]["y"] == new_y) {
                occupied = true;
                base_road["end_x"] = intersect["coordinates"]["x"];
                base_road["end_y"] = intersect["coordinates"]["y"];
                base_road["end"] = intersect["id"];
                std::string reverse_direction = ReverseDirection(direction);
                intersections[i]["road_directions"][reverse_direction] = 1;
                break;
            }
        }
        /* for(auto intersect: intersections) {
            if(intersect["coordinates"]["x"] == new_x && intersect["coordinates"]["y"] == new_y) {
                occupied = true;
                base_road["end_x"] = intersect["coordinates"]["x"];
                base_road["end_y"] = intersect["coordinates"]["y"];
                base_road["end"] = intersect["id"];
                
                break;
            }
        } */

        if(!occupied) {
            intersection["id"] = intersections.size();
            intersection["coordinates"]["x"] = new_x;
            intersection["coordinates"]["y"] = new_y;
            intersection["road_directions"]["n"] = GetRoadStatus(new_x, new_y, "n", map_size, step_size);
            intersection["road_directions"]["e"] = GetRoadStatus(new_x, new_y, "e", map_size, step_size);
            intersection["road_directions"]["s"] = GetRoadStatus(new_x, new_y, "s", map_size, step_size);
            intersection["road_directions"]["w"] = GetRoadStatus(new_x, new_y, "w", map_size, step_size);
            // Correct the opposite of the direction used to create this intersection to status 1
            if (direction == "n") {
                intersection["road_directions"]["s"] = 1;
            } else if (direction == "e") {
                intersection["road_directions"]["w"] = 1;
            } else if (direction == "s") {
                intersection["road_directions"]["n"] = 1;
            } else {
                intersection["road_directions"]["e"] = 1;
            }
            intersections.push_back(intersection);
            base_road["end_x"] = intersection["coordinates"]["x"];
            base_road["end_y"] = intersection["coordinates"]["y"];
            base_road["end"] = intersection["id"];
        }
        base_roads.push_back(base_road);
    }

    // Put an intersection halfway through every road.
    json roads;
    json road1;
    json road2;
    int smaller_step_size = static_cast<int>(std::round(step_size/3));
    for(auto base_road: base_roads) {
        int x = static_cast<int>(std::floor((static_cast<int>(base_road["start_x"]) + static_cast<int>(base_road["end_x"]))/2));
        int y = static_cast<int>(std::floor((static_cast<int>(base_road["start_y"]) + static_cast<int>(base_road["end_y"]))/2));
        intersection["id"] = intersections.size();
        intersection["coordinates"]["x"] = x;
        intersection["coordinates"]["y"] = y;

        if(base_road["start_x"] == base_road["end_x"]) {
            intersection["road_directions"]["n"] = 1;
            intersection["road_directions"]["e"] = GetRoadStatus(x, y, "e", map_size, smaller_step_size);
            intersection["road_directions"]["s"] = 1;
            intersection["road_directions"]["w"] = GetRoadStatus(x, y, "w", map_size, smaller_step_size);
        } else {
            intersection["road_directions"]["n"] = GetRoadStatus(x, y, "n", map_size, smaller_step_size);
            intersection["road_directions"]["e"] = 1;
            intersection["road_directions"]["s"] = GetRoadStatus(x, y, "s", map_size, smaller_step_size);
            intersection["road_directions"]["w"] = 1;
        }
        intersections.push_back(intersection);
        road1["id"] = static_cast<int>(base_road["id"])*2;
        road2["id"] = static_cast<int>(base_road["id"])*2+1;
        road1["start"] = base_road["start"];
        road1["end"] = intersection["id"];
        road2["start"] = intersection["id"];
        road2["end"] = base_road["end"];
        road1["start_type"] = "intersection";
        road1["end_type"] = "intersection";
        road2["start_type"] = "intersection";
        road2["end_type"] = "intersection";
        roads.push_back(road1);
        roads.push_back(road2);
    }

    json output;
    output["main_roads"] = roads;
    output["intersections"] = intersections;
    output["step_size"] = step_size;
    output["smaller_step_size"] = smaller_step_size;
    return output;
}

void input2json(void) {
    std::srand(std::time(nullptr));  // set seed for rand function
    
    /* First read lines from input file to a vector of pairs. */
    std::ifstream input_file_stream;
    input_file_stream.open("../traffic-sim-2020-1/src/input_file.txt", std::ios::in);
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
            if(amount <= 0) {
                amount = 1; 
            } else if(amount > 100) {
                amount = 100;
            }
            amounts_struct.density = amount;
        } else if(object=="Size" || object=="size") {
            if(amount <= 0) {
                amount = 1; 
            } else if(amount > 100) {
                amount = 100;
            }
            amounts_struct.city_size = amount;
        } else if(object=="Passengers" || object=="passengers") {
            if(amount <= 0) {
                amount = 1; 
            } else if(amount > 10000) {
                amount = 10000;
            }
            amounts_struct.passengers = amount;
        }
    }

    /* Calculate city size. */
    int map_size = CalculateMapSize(amounts_struct.density, amounts_struct.city_size);

    /* Create JSON here. */
    json output = GenerateSkeleton(amounts_struct.city_size, map_size);
    json building;
    json road;
    coordinates coords;
    std::vector<int> residential_buildings;
    std::vector<int> commercial_buildings;
    std::vector<int> industrial_buildings;
    int building_id = output["intersections"].size(); // Start counting where we ended... (a helpful trick)
    int road_id = output["roads"].size();
    for(auto intersection: output["intersections"]) {
        for(std::string direction: {"n","e","s","w"}) {
            if(intersection["road_directions"][direction] == 0) {
                building["id"] = building_id;
                building_id++;
                coords = GenerateBuildingCoordinates(intersection["coordinates"]["x"], intersection["coordinates"]["y"], direction, output["smaller_step_size"]);
                building["coordinates"]["x"] = coords.x;
                building["coordinates"]["y"] = coords.y;
                std::string building_type = GenerateBuildingType(building["id"]);
                building["type"] = building_type;

                if(building_type == "residential") {
                    residential_buildings.push_back(building["id"]);
                } else if(building_type == "commercial") {
                    commercial_buildings.push_back(building["id"]);
                } else {
                    industrial_buildings.push_back(building["id"]);
                }

                building["people_capacity"] = 1000; // Provisional...
                building["car_capacity"] = 1000; // Provisional...
                output["buildings"].push_back(building);

                // Create road connecting the building with the intersection.
                road["id"] = road_id;
                road["start"] = intersection["id"];
                road["end"] = building["id"];
                road["start_type"] = "intersection";
                road["end_type"] = "building";
                road_id++;
                output["side_roads"].push_back(road);
            }
        }
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

    std::ofstream o("input.json");
    o << std::setw(4) << output << std::endl;
    o.close();
}
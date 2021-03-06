#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <map>
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
    float rand_num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // random number between 0 and 1
    return rand_num;
}

/*Used in generating the roads&intersections skeleton. Step size is the distance between intersections.*/
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

/*Used in generating the roads&intersections skeleton.*/
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

/*Full intersection is an intersection with four roads - one in each direction.*/
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

/*Either returns coresponding string to a number, or generates type randomly. Just a helper function.*/
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

/*Used in generating the roads&intersections skeleton. Helper function.*/
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

/*Used to get the city size to make the displayed window dynamic size.*/
std::map<std::string,int> FindCoordsRange(json buildings, json intersections) {
    int max_x = 0, max_y = 0, min_x = 99999, min_y = 99999;

    for(auto b:buildings) {
        if (b["coordinates"]["x"] > max_x) {
            max_x = b["coordinates"]["x"];
        } else if (b["coordinates"]["x"] < min_x) {
            min_x = b["coordinates"]["x"];
        }

        if (b["coordinates"]["y"] > max_y) {
            max_y = b["coordinates"]["y"];
        } else if (b["coordinates"]["y"] < min_y) {
            min_y = b["coordinates"]["y"];
        }
    }

    for(auto inters:intersections) {
        if (inters["coordinates"]["x"] > max_x) {
            max_x = inters["coordinates"]["x"];
        } else if (inters["coordinates"]["x"] < min_x) {
            min_x = inters["coordinates"]["x"];
        }

        if (inters["coordinates"]["y"] > max_y) {
            max_y = inters["coordinates"]["y"];
        } else if (inters["coordinates"]["y"] < min_y) {
            min_y = inters["coordinates"]["y"];
        }
    }

    std::map<std::string,int> coordinates_ranges;
    coordinates_ranges.insert(std::make_pair("max_x",max_x));
    coordinates_ranges.insert(std::make_pair("min_x",min_x));
    coordinates_ranges.insert(std::make_pair("max_y",max_y));
    coordinates_ranges.insert(std::make_pair("min_y",min_y));
    return(coordinates_ranges);
}

/*Used in generating the roads&intersections skeleton. Helper function*/
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

/*This is the important part.*/
/*Here we generate a skeleton comprising of intersections and roads.*/
/*I won't go into detail - it's a trade secret.*/
json GenerateSkeleton(int city_size) {
    int intersections_amount = static_cast<int>(std::ceil(city_size/2))+2;
    int step_size = static_cast<int>(std::floor(30+2000/(10+intersections_amount)));
    json intersection;
    json intersections;
    json base_road;
    json base_roads;

    /*Create base intersection.*/
    intersection["id"] = 0;
    intersection["coordinates"]["x"] = intersections_amount*step_size;
    intersection["coordinates"]["y"] = intersections_amount*step_size;
    intersection["road_directions"]["n"] = 0;
    intersection["road_directions"]["e"] = 0;
    intersection["road_directions"]["s"] = 0;
    intersection["road_directions"]["w"] = 0;
    intersections.push_back(intersection);

    /*Generate given amount of intersections.*/
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

        /*Generate and keep track of connections between the intersections.*/
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

        if(!occupied) {
            intersection["id"] = intersections.size();
            intersection["coordinates"]["x"] = new_x;
            intersection["coordinates"]["y"] = new_y;
            intersection["road_directions"]["n"] = 0;
            intersection["road_directions"]["e"] = 0;
            intersection["road_directions"]["s"] = 0;
            intersection["road_directions"]["w"] = 0;
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
            intersection["road_directions"]["e"] = 0;
            intersection["road_directions"]["s"] = 1;
            intersection["road_directions"]["w"] = 0;
        } else {
            intersection["road_directions"]["n"] = 0;
            intersection["road_directions"]["e"] = 1;
            intersection["road_directions"]["s"] = 0;
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

/*This is the function used outside of this file. It calls the generate skeleton stuff and then
uses the skeleton to generate buildings. It also handles passengers. The output is a json file.*/
void input2json(void) {
    std::srand(std::time(nullptr));  // set seed for rand function
    
    /* First read lines from input file to a vector of pairs. */
    std::ifstream input_file_stream;
    input_file_stream.open("../src/input_file.txt", std::ios::in);
    if(!input_file_stream)
    {
        std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
        std::cout << "Error: Input file not found. Please create an input_file.txt file in the src folder." << std::endl;
        std::cout << "Default input will be used." << std::endl;
        std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    } 
    std::vector<std::pair<std::string, int>> lines;
    std::string line;
    std::string line_str;
    int line_int;

    while (std::getline(input_file_stream,line))
    {
        if(!line.empty()) {
            try {
                line_str = line.substr(0, line.find(" "));
                line_int = std::stoi(line.substr(line.find(" ")));
            } catch (const std::out_of_range& e) {
                std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
                std::cout << "Error: " << "Some part of input file has incorrect format." << std::endl;
                std::cout << "Only part of input or default input will be used." << std::endl;
                std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
                break;
            }
            std::pair<std::string, int> line_pair = std::make_pair(line_str, line_int);
            if(line_str.size() > 0) {
                lines.push_back(line_pair);
            }
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
        
        if(object=="Size" || object=="size") {
            if(amount <= 0) {
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Warning: " << "City size is too small, has been set to 1." << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                amount = 1; 
            } else if(amount > 100) {
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Warning: " << "Size of the city exceeded the limit (100) and has been set to 100." << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                amount = 100;
            }
            amounts_struct.city_size = amount;
        } else if(object=="Passengers" || object=="passengers") {
            if(amount <= 0) {
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Warning: " << "Not enough passengers, number of passengers has been set to 1." << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                amount = 1; 
            } else if(amount > 1000) {
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Warning: " << "Number of passengers exceeded the limit (1000) and has been set to 1000." << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                amount = 1000;
            }
            amounts_struct.passengers = amount;
        }
    }

    /* Create JSON here. */
    json output = GenerateSkeleton(amounts_struct.city_size);
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

                building["people_capacity"] = 1000; // Provisional - we decided not to use capacities in the end.
                building["car_capacity"] = 1000; // Provisional - we decided not to use capacities in the end.
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

    // Move the whole city to the 0,0 corner.
    std::map<std::string,int> coordinates_ranges = FindCoordsRange(output["buildings"], output["intersections"]);

    for (uint_fast16_t i=0; i < output["buildings"].size(); i++) {
        output["buildings"][i]["coordinates"]["x"] = static_cast<int>(output["buildings"][i]["coordinates"]["x"]) - coordinates_ranges["min_x"]+20;
        output["buildings"][i]["coordinates"]["y"] = static_cast<int>(output["buildings"][i]["coordinates"]["y"]) - coordinates_ranges["min_y"]+20;
    }

    for (uint_fast16_t i=0; i < output["intersections"].size(); i++) {
        output["intersections"][i]["coordinates"]["x"] = static_cast<int>(output["intersections"][i]["coordinates"]["x"]) - coordinates_ranges["min_x"] +20;
        output["intersections"][i]["coordinates"]["y"] = static_cast<int>(output["intersections"][i]["coordinates"]["y"]) - coordinates_ranges["min_y"] +20;
    }

    output["city_size"]["coordinates"]["x"] = coordinates_ranges["max_x"]-coordinates_ranges["min_x"]+40;
    output["city_size"]["coordinates"]["y"] = coordinates_ranges["max_y"]-coordinates_ranges["min_y"]+40;

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
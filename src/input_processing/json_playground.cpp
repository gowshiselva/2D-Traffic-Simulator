#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <iomanip>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int mainiiiii(void) {
    json j;
    j["hello"] = "world";
    j["pi"] = 3.141;
    j["happy"] = true;
    std::ofstream o("test.json");
    o << std::setw(4) << j << std::endl;
}
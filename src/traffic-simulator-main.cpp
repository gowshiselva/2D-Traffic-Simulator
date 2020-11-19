#include <iostream>
#include "car.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
 int main() {
    std::cout << " I am traffic simulator" << std::endl;
    plt::plot({1,3,2,4});
    plt::show();
    return 0;
}


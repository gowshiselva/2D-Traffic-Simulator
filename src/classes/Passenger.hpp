#pragma once
#include "timeschedule.h"
#include "Building.hpp"

#include <memory>

class Passenger {
    public:
        Passenger(Building home, Building workplace, timeschedule schedule); // also car
        
        Building GetHome() const;
        Building GetWorkplace() const;
        int GetLeaveHomeTime() const;
        int GetLeaveWorkTime() const;

    private:
        std::shared_ptr<Building> home_;
        std::shared_ptr<Building> workplace_;
        timeschedule timeschedule_;
};
#pragma once
#include "timeschedule.h"
#include "Building.hpp"

#include <memory>

class Passenger {
    public:
        Passenger(Building home, Building workplace, CommercialBuilding shop, timeschedule schedule); // also car
        
        ResidentialBuilding GetHome() const;
        Building GetWorkplace() const;
        CommercialBuilding GetShop() const;
        int GetLeaveHomeTime() const;
        int GetLeaveWorkTime() const;

    private:
        std::shared_ptr<ResidentialBuilding> home_;
        std::shared_ptr<Building> workplace_;          // Can this be just Building?
        std::shared_ptr<CommercialBuilding> shop_;
        
        timeschedule timeschedule_;
        std::string current_position;
};
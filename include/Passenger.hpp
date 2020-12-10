#pragma once
#include "timeschedule.h"
#include "Building.hpp"

#include <memory>

class Passenger {
    public:
        Passenger(int id, std::shared_ptr<Building> home, std::shared_ptr<Building> workplace, std::shared_ptr<Building> shop, std::string position, timeschedule schedule); // also car
        
        Building GetHome() const;
        Building GetWorkplace() const;
        Building GetShop() const;
        std::string GetPosition() const;
        void SetPosition(std::string position);
        bool EnterBuilding(std::string building_name);
        bool LeaveBuilding(std::string building_name);
        /*GetCar*/
        int GetLeaveHomeTime() const;
        int GetLeaveWorkTime() const;
        int GetId() const;

    private:
        int id_;
        std::shared_ptr<Building> home_;
        std::shared_ptr<Building> workplace_;          
        std::shared_ptr<Building> shop_;
        std::string position_;
        /*car_*/
        
        timeschedule timeschedule_;
        std::string current_position;
};
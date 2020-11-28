#include "Passenger.hpp"

Passenger::Passenger(/*car,*/ std::shared_ptr<Building> home, std::shared_ptr<Building> workplace, std::shared_ptr<Building> shop, std::string position, timeschedule schedule)
    : /*car_(car),*/
    home_(home),
    workplace_(workplace),
    shop_(shop),
    position_(position),
    timeschedule_(schedule) {}

/*GetCar*/
        
Building Passenger::GetHome() const {
    return *home_;
}

Building Passenger::GetWorkplace() const {
    return *workplace_;
}

Building Passenger::GetShop() const {
    return *shop_;
}

std::string Passenger::GetPosition() const {
    return position_;
}

void Passenger::SetPosition(std::string position) {
    position_ = position;   //"home","workplace","car"
}

bool Passenger::EnterBuilding(std::string building_name) {
    Building building;

    if(building_name == "home") {
        building = GetHome();
    } else if(building_name == "workplace") {
        building = GetWorkplace();
    } else {
        return false;
    }

    if (building.GetPeopleAmount() < building.GetPeopleCapacity()) {    // Can fit into building.
        building.IncrementPeopleAmount();
        SetPosition(building_name);
        return true;
    } else {    // Building is full.
        return false;
    }
}

bool Passenger::LeaveBuilding(std::string building_name) {
    Building building;

    if(building_name == "home") {
        building = GetHome();
    } else if(building_name == "workplace") {
        building = GetWorkplace();
    } else {
        return false;
    }

    building.DecrementPeopleAmount();   // Leave building.
    SetPosition("car");     // Enter car.
    return true;
}

int Passenger::GetLeaveHomeTime() const {
    return timeschedule_.leave_home;
}

int Passenger::GetLeaveWorkTime() const {
    return timeschedule_.leave_work;
}
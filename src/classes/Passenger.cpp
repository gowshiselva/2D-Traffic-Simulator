#include "Passenger.hpp"

Passenger::Passenger(Building home, Building workplace, CommercialBuilding shop, timeschedule schedule)
    : home_(std::make_shared<ResidentialBuilding>(home)),
    workplace_(std::make_shared<Building>(workplace)),
    shop_(std::make_shared<CommercialBuilding>(shop)),
    timeschedule_(schedule) {}
        
ResidentialBuilding Passenger::GetHome() const {
    return *home_;
}

Building Passenger::GetWorkplace() const {
    return *workplace_;
}

CommercialBuilding Passenger::GetShop() const {
    return *shop_;
}

int Passenger::GetLeaveHomeTime() const {
    return timeschedule_.leave_home;
}

int Passenger::GetLeaveWorkTime() const {
    return timeschedule_.leave_work;
}
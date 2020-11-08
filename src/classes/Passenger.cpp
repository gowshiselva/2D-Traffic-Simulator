#include "Passenger.hpp"

Passenger::Passenger(Building home, Building workplace, timeschedule schedule)
    : home_(std::make_shared<Building>(home)), workplace_(std::make_shared<Building>(workplace)), timeschedule_(schedule) {}
        
Building Passenger::GetHome() const {
    return *home_;
}

Building Passenger::GetWorkplace() const {
    return *workplace_;
}

int Passenger::GetLeaveHomeTime() const {
    return timeschedule_.leave_home;
}

int Passenger::GetLeaveWorkTime() const {
    return timeschedule_.leave_work;
}
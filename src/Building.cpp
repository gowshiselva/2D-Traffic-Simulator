#include "Building.hpp"

Building::Building(int id, coordinates coords, int people_amount, int people_capacity, int car_amount, int car_capacity, std::string type)
    : id_(id), coordinates_(coords), people_amount_(people_amount), people_capacity_(people_capacity), car_amount_(car_amount), car_capacity_(car_capacity), type_(type) {}

int Building::GetId() const {
    return id_;
}

coordinates Building::GetCoordinates() const {
    return coordinates_;
}

void Building::IncrementPeopleAmount() {
    people_amount_+=1;
}

void Building::DecrementPeopleAmount() {
    people_amount_-=1;
}

int Building::GetPeopleCapacity() const {
    return people_capacity_;
}

int Building::GetPeopleAmount() const {
    return people_amount_;
}

void Building::IncrementCarAmount() {
    car_amount_+=1;
}

void Building::DecrementCarAmount() {
    car_amount_-=1;
}

int Building::GetCarCapacity() const {
    return car_capacity_;
}

int Building::GetCarAmount() const {
    return car_amount_;
}

std::string Building::GetType() const {
    return type_;
}
/*-----------------------------------------------------------------------*/
/*---------------------------DERIVED CLASSES-----------------------------*/
/*-----------------------------------------------------------------------*/

/* ResidentialBuilding::ResidentialBuilding(coordinates coords, int people_capacity, int car_capacity)
    : Building(coords, people_capacity, car_capacity) {}

CommercialBuilding::CommercialBuilding(coordinates coords, int people_capacity, int car_capacity)
    : Building(coords, people_capacity, car_capacity) {}
    
IndustrialBuilding::IndustrialBuilding(coordinates coords, int people_capacity, int car_capacity)
    : Building(coords, people_capacity, car_capacity) {} */
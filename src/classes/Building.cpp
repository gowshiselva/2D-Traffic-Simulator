#include "Building.hpp"

Building::Building(coordinates coords, int people_capacity, int car_capacity)
    : coordinates_(coords), people_capacity_(people_capacity), car_capacity_(car_capacity) {}

coordinates Building::GetCoordinates() const {
    return coordinates_;
}

int Building::GetPeopleCapacity() const {
    return people_capacity_;
}

int Building::GetCarCapacity() const {
    return car_capacity_;
}
/*-----------------------------------------------------------------------*/
/*---------------------------DERIVED CLASSES-----------------------------*/
/*-----------------------------------------------------------------------*/

ResidentialBuilding::ResidentialBuilding(coordinates coords, int people_capacity, int car_capacity)
    : Building(coords, people_capacity, car_capacity) {}

CommercialBuilding::CommercialBuilding(coordinates coords, int people_capacity, int car_capacity)
    : Building(coords, people_capacity, car_capacity) {}
    
IndustrialBuilding::IndustrialBuilding(coordinates coords, int people_capacity, int car_capacity)
    : Building(coords, people_capacity, car_capacity) {}
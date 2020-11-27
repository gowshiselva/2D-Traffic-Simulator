#pragma once
#include "coordinates.h"

class Building {
    public:
        Building(coordinates coords, int people_capacity, int car_capacity);
        
        coordinates GetCoordinates() const;
        int GetPeopleCapacity() const;
        int GetCarCapacity() const;
        bool EnterBuilding();

    private:
        coordinates coordinates_;
        int people_capacity_;
        int car_capacity_;
};

class ResidentialBuilding: public Building {
    public:
        ResidentialBuilding(coordinates coords, int people_capacity, int car_capacity);
};

class CommercialBuilding: public Building {
    public:
        CommercialBuilding(coordinates coords, int people_capacity, int car_capacity);
};

class IndustrialBuilding: public Building {
    public:
        IndustrialBuilding(coordinates coords, int people_capacity, int car_capacity);
};
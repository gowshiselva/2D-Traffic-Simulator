#pragma once
#include <string>
#include <vector>
#include "coordinates.h"

class Intersection;
class SideRoad;

class Building {
    public:
        Building(int id, coordinates coords, int people_amount, int people_capacity, int car_amount, int car_capacity, std::string type);
        Building() {}
        int GetId() const;
        coordinates GetCoordinates() const;
        void IncrementPeopleAmount();
        void DecrementPeopleAmount();
        int GetPeopleCapacity() const;
        int GetPeopleAmount() const;
        void IncrementCarAmount();
        void DecrementCarAmount();
        int GetCarCapacity() const;
        int GetCarAmount() const;
        std::string GetType() const;
        bool EnterBuilding();
        Intersection GetNeighborIntersection(std::vector<SideRoad> side_roads) const;

    private:
        int id_;
        coordinates coordinates_;
        int people_amount_;
        int people_capacity_;
        int car_amount_;
        int car_capacity_;
        std::string type_;
};

/* class ResidentialBuilding: public Building {
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
}; */
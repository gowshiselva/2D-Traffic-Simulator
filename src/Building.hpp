struct coordinates {
    int x;
    int y;
};

class Building {
    public:
        Building(coordinates coords, int people_capacity, int car_capacity);

        coordinates GetCoordinates() const;

        int GetPeopleCapacity() const;

        int GetCarCapacity() const;

    private:
        coordinates coordinates_;
        int people_capacity_;
        int car_capacity_;
};
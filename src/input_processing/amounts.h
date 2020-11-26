#ifndef AMOUNTS_H
#define AMOUNTS_H

#define DEFAULT_DENSITY 50
#define DEFAULT_CITY_SIZE 50
#define DEFAULT_PASSENGERS_AMOUNT 100

struct amounts_s 
{
    int density;
    int city_size;
    int passengers;
} amounts_default = {DEFAULT_DENSITY, DEFAULT_CITY_SIZE, DEFAULT_PASSENGERS_AMOUNT};

typedef struct amounts_s amounts;
// initialise like: amounts mInstance = amounts_default;
#endif

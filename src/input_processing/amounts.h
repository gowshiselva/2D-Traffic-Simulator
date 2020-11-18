#ifndef AMOUNTS_H
#define AMOUNTS_H

#define DEFAULT_DENSITY 50
#define DEFAULT_BUILDINGS_AMOUNT 10
#define DEFAULT_PASSENGERS_AMOUNT 100

struct amounts_s 
{
    int density;
    int buildings;
    int passengers;
} amounts_default = {DEFAULT_DENSITY, DEFAULT_BUILDINGS_AMOUNT, DEFAULT_PASSENGERS_AMOUNT};

typedef struct amounts_s amounts;
// initialise like: amounts mInstance = amounts_default;
#endif

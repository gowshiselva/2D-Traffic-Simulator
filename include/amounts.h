#ifndef AMOUNTS_H
#define AMOUNTS_H

#define DEFAULT_CITY_SIZE 15
#define DEFAULT_PASSENGERS_AMOUNT 100

struct amounts_s 
{
    int city_size;
    int passengers;
} amounts_default = {DEFAULT_CITY_SIZE, DEFAULT_PASSENGERS_AMOUNT};

typedef struct amounts_s amounts;
// initialise like: amounts mInstance = amounts_default;
#endif

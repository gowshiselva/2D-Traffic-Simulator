/* #include "Road.hpp"
#include <cmath>

template<typename T1, typename T2>
T1& Road<T1,T2>::GetStart() const{
    return start_;
}

template<typename T1, typename T2>
T2& Road<T1,T2>::GetEnd() const{
    return end_;
}

template<typename T1, typename T2>
double Road<T1,T2>::CalculateLength() {
    coordinates start_coords = GetStart().GetCoordinates();
    coordinates end_coords = GetEnd().GetCoordinates();
    return sqrt(pow(end_coords.x-start_coords.x,2)+pow(end_coords.y-start_coords.y,2));
} */
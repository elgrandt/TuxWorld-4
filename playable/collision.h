#ifndef collision_H_
#define collision_H_

#include "elements/element.h"
#include "stage.h"

#include <vector>
using namespace std;

namespace coll{
    extern const char up    ;
    extern const char down  ;
    extern const char left  ;
    extern const char right ;
    extern const char nocoll;
};
struct collision{
    double percentaje;
    double distance;
    char side;
    collision(double side,double distance);
};

typedef vector <collision> collist;

collist collide(Element* from,Element* bywhat);
collist get_max_collide(Element* from,Element* bywhat);

#endif

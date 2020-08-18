#ifndef WEAPON_H
#define WEAPON_H

#include "element.h"

class weapon : public Element{
    public:
        void update();
        virtual void weapon_update();
};

#endif // WEAPON_H

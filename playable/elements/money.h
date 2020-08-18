#ifndef MONEY_H_
#define MONEY_H_

#include "lincludes/mSDL.h"
#include "lincludes/mSDL.h"

#include "element.h"

class Money : public Element{
    private:
        double value;
        int sy;
        bool st;
        double original_y;
    public:
        Money(double value,double x,double y);
        void update();
        double get_value();
};

#endif //MONEY_H_

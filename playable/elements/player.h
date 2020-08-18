#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "element.h"
#include "weapon.h"

using namespace std;

#define QUIET 0
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_UP 3
#define MOVE_DOWN 4

class Handler;

class player : public Element{
    private:
        int speed;

        bool going_up;
        bool going_down;
        bool going_left;
        bool going_right;
        char loops;

        void get_collision();
        bool act_coll[4];
        bool obtained;

        int timeout;
        int money;
        int life ;
        vector <weapon*> weapons;
        Handler* controller;
    public:
        player();
        virtual ~player();
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void update();
        void reset_going();
        void set_controller(Handler* controller);
        void lose_life();

};

#endif // PLAYER_H

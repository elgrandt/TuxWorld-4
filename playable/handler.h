#ifndef HANDLER_H_
#define HANDLER_H_

#include <string>
#include "lincludes/mSDL.h"
#include "elements/player.h"

using namespace std;

class Handler{
    private:
        player *central;
        bool go_up;
        bool go_down;
        bool go_left;
        bool go_right;
        string name;
        int energy;
        int lives;
        long double money;
        GLuint surface_name;
        GLuint surface_money;
        GLuint surface_lives;
    public:
        Handler();
        void set_player(player* play);
        void keydown(int key_pressed);
        void keyup(int key_up);
        void take_action();
        void set_name(string name);

        void loss_energy(int amount);
        void add_live();
        void kill_live();
        void give_money(double amount);
        void take_money(int amount);
        void update_money_surface();
        void update_lives_surface();
        GLuint get_surface_name();
        GLuint get_surface_money();
        int get_energy();
        player* get_central();

};

#endif // HANDLER_H_

#ifndef ENEMY_H
#define ENEMY_H

#include "element.h"
#include "playable/collision.h"

class enemy : public Element{
    private:
        double speed;
        double angle;
        bool destroy;
    public:
        enemy(double x,double y);
        void update();
        void check_collision();
        void handle_collision(collision c,epointer e);
        virtual void enemy_update()=0;
        virtual void enemy_collision(collision c,epointer e)=0;
        void set_angle(double angle);
        double get_angle();
        virtual void destroy_sequence();
        void destroyme();
};

class classic_enemy : public enemy{
    private:
        int timer;
        int imager;
    public:
        classic_enemy(double x,double y);
        void enemy_update();
        void enemy_collision (collision c, epointer e);
        void destroy_sequence();
};

class sequencial_enemy : public enemy{
    private:
        vector <pair <int,int> > go_list;
        int iamnow;
    public:
        sequencial_enemy(double x,double y, vector < pair<int,int> > areas );
        void enemy_update ();
        void enemy_collision (collision c,epointer e);
        void destroy_sequence ();
};

#endif // ENEMY_H

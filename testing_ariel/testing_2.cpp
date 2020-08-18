#include "testing_2.h"
#include "lincludes/mSDL.h"

#include "OGL/OGL.h"
#include "testing/testing.h"
#include "playable/stage.h"
#include "playable/elements/player.h"
#include "playable/elements/wall.h"
#include "playable/elements/enemy.h"
#include "playable/elements/background.h"
#include "playable/elements/money.h"
#include "playable/elements/tecnowall.h"
#include "playable/elements/check_point.h"
#include <cstdio>
#include <iostream>
using namespace std;

int test_2(){

    start_testing ("Testing 2");

    graphic_stage stage;

    Handler move_player_1 = Handler();
    stage.add_player ( 400 , 400 , &move_player_1);
    stage.set_focus_player (0);

    /*Tecnowall* tecno = new Tecnowall();
    int R = tecno->add_first_wall (10,1,HORIZONTAL,0,0);
    R = tecno->add_wall (1,10,IZQUIERDA,0,R);
    R = tecno->add_wall (10,1,DERECHA,10,R);
    R = tecno->add_wall (1,10,DERECHA,10,R);

    stage.add_element (tecno);
*/
    check_point* cp = new check_point();
    cp->set_x(200);
    cp->set_y(500);

    stage.add_element (cp);

    wall *wall_1 = classic_wall_horizontal(10*20,1);
    stage.add_element (wall_1);

    wall *wall_2 = classic_wall_vertical(1,10);
    wall_2->set_position (wall_1->get_w (),0);
    stage.add_element (wall_2);

    wall* wall_3 = classic_wall_vertical (1,10);
    stage.add_element (wall_3);

    wall* wall_4 = classic_wall_horizontal(10*20,1);
    wall_4->set_position (0,wall_3->get_h());
    stage.add_element (wall_4);

    vector <double> values;
    values.push_back (0.5);
    values.push_back (0.6);
    values.push_back (0.5);
    values.push_back (.2);
    values.push_back (.03);
    values.push_back (.02);
    values.push_back (.07);
    values.push_back (.01);
    values.push_back (.03);
    values.push_back (.07);
    values.push_back (.04);
    values.push_back (1000.03);

    for (int x = 0;x < values.size ();x++){
        Money* moneda = new Money(values[x],400+x*50,400+x*10);
        stage.add_element (moneda);
    }

    background* b1 = get_classic_background (50*20,50,1000*20,1000,0,0);

    stage.add_element (b1);

    /*for (int v = 0;v < 50;v++){
        classic_enemy* enemy1 = new classic_enemy(50+rand()%500,50+rand()%500);
        stage.add_element (enemy1);
    }*/
    bool continuar = true;
    while (continuar){
        while (SDL_PollEvent(&events)){
            switch (events.type){
                case SDL_QUIT:
                    continuar = false;
                break;
                case SDL_KEYDOWN:
                    move_player_1.keydown (events.key.keysym.sym);
                    if (events.key.keysym.sym == SDLK_z){
                        stage.sum_zoom (0.1);
                    }
                    if (events.key.keysym.sym == SDLK_x){
                        stage.sum_zoom (-0.1);
                    }
                break;
                case SDL_KEYUP:
                    move_player_1.keyup (events.key.keysym.sym);
                break;

            }
        }
        stage.update ();
        stage.draw ();
        refresh_screen ();
    }
    return 0;
}

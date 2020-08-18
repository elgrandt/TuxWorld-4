#include "title.h"

Title::Title(){
    enabled = false;
    tux.image = images::tux_cargando[0].img;
    tux.w = images::tux_cargando[0].w;
    tux.h = images::tux_cargando[0].h;
    tux.x = -tux.w;
    tux.y = OGL::screen->h/2-tux.h/2;
    moving_tux = 0;
    moving_enemies = false;
}

void Title::enable(Authors* autores){
    enabled = true;
    authors = autores;
    int act_y = authors->globaly;
    SDL_Surface* Test1 = TTF_RenderText_Blended(fonts::presentacion,"a",OGL::c(0,0,0));
    SDL_Surface* Test2 = TTF_RenderText_Blended(fonts::presentacion,"b",OGL::c(0,0,0));
    SDL_Surface* Test3 = TTF_RenderText_Blended(fonts::presentacion,"ab",OGL::c(0,0,0));
    double espacio_separacion = Test3->w-(Test1->w+Test2->w);
    SDL_FreeSurface(Test1);
    SDL_FreeSurface(Test2);
    SDL_FreeSurface(Test3);
    Text letter_act;
    authors->color_first = OGL::c(255, 0, 0);
    for (int x = authors->texts.size()-1; x >= 0; x--) {
        double x_act = 0;
        for (int y = 0; y < authors->texts[x].text_string.length(); y++) {
            letter_act = Text();
            letter_act.text_string = authors->texts[x].text_string[y];
            letter_act.surface_first = TTF_RenderText_Blended(fonts::presentacion, letter_act.text_string.c_str(), authors->color_first);
            letter_act.surface = TTF_RenderText_Blended(fonts::presentacion, letter_act.text_string.c_str(), authors->color_second);
            letter_act.w = letter_act.surface->w;
            letter_act.h = letter_act.surface->h;
            letter_act.text = OGL::generate_texture(letter_act.surface);
            letter_act.text_first = OGL::generate_texture(letter_act.surface_first);
            letter_act.x = OGL::screen->w/2-authors->texts[x].w/2+x_act;
            letter_act.y = act_y;
            letter_act.from_line = x;
            letters.push_back(letter_act);
            x_act += letter_act.w+espacio_separacion;
        }
        act_y += letter_act.h+3;
    }
    int X = (-1)*images::enemies::classical[0].w;
    int Y = 50;
    for (int n = 0; n < 300; n++){
        int selected = rand()%2;
        TuxCartel actual;
        actual.x = X;
        actual.y = Y;
        if (selected == 0){
            actual.w = images::enemies::classical[0].w;
            actual.h = images::enemies::classical[0].h;
            actual.image = images::enemies::classical[0].img;
        }else{
            actual.w = images::enemies::classical[0].w;
            actual.h = images::enemies::classical[0].h;
            actual.image = images::enemies::windows.img;
        }
        Y += actual.h;
        actual.angle = rand()%140+20;
        if (Y >= OGL::screen->h-50){
            Y = 50; X -= actual.w;
        }
        actual.cruzo = false;
        enemies.push_back(actual);
    }
    Y = OGL::screen->h/2-images::enemies::enorme.h/2;
    X -= images::enemies::enorme.w;
    for (int x = 0; x < 3; x++){
        TuxCartel actual;
        actual.x = X;
        actual.y = Y;
        actual.w = images::enemies::enorme.w;
        actual.h = images::enemies::enorme.h;
        actual.image = images::enemies::enorme.img;
        actual.angle = 90;
        X -= actual.w+rand()%200;
        enemies.push_back(actual);
    }
}

bool Title::is_enabled(){
    return enabled;
}

void Title::update(){
    if (enabled) {
        if (moving_tux == 0) {
            tux.x += 6;
            tux.image = images::tux_cargando[loops/10 % images::tux_cargando.size()].img;
            if (tux.x == OGL::screen->w/2-380/2) {
                moving_tux = 1;
                loops = 0;
            }
        }else{
            tux.image = images::final_tux_cargando[moving_tux-1].img;
            if (loops == 100){
                moving_tux++;
                if (moving_tux == 3){
                    moving_tux = 0;
                    moving_enemies = true;
                }
                loops = 0;
            }
            tux.y = OGL::screen->h/2-tux.h/2;
            tux.x = OGL::screen->w/2-380/2;
        }
        OGL::blit_texture(tux.image, tux.x, tux.y, tux.w, tux.h);
        for (int x = 0; x < 14; x++) {
            for (int y = 0; y < letters.size(); y++) {
                GLuint to_blit;
                if (x == 13) {
                    to_blit = letters[y].text_first;
                }else{
                    to_blit = letters[y].text;
                }
                OGL::blit_texture(to_blit,letters[y].x,letters[y].y+x,letters[y].w,letters[y].h);
            }
        }
        for (int x = 0; x < letters.size(); x++) {
            if (!letters[x].moving_out){
                if (tux.x + tux.w > letters[x].x) {
                    letters[x].moving_out = true;
                    if (letters[x].from_line < authors->texts.size()/2) {
                        letters[x].angle = rand()%180+270;
                        if (letters[x].angle > 360) {
                            letters[x].angle -= 360;
                        }
                    }else{
                        letters[x].angle = rand()%180+90;
                    }
                }
            }else{
                letters[x].x += sin(letters[x].angle*PI/180)*15;
                letters[x].y += cos(letters[x].angle*PI/180)*15;
            }
        }
        if (moving_enemies){
            vector<int> del;
            for (int x = 0; x < enemies.size(); x++){
                int speed = 8;
                if (enemies[x].w == images::enemies::enorme.w && enemies[x].x + enemies[x].w> 0){
                    speed = 5;
                }
                enemies[x].x += sin(enemies[x].angle*PI/180)*speed;
                enemies[x].y += cos(enemies[x].angle*PI/180)*speed;
                if (enemies[x].y < -enemies[x].h || enemies[x].y > OGL::screen->h+enemies[x].h){
                    enemies[x].angle = 180-enemies[x].angle;
                }
                OGL::blit_texture(enemies[x].image,enemies[x].x,enemies[x].y,enemies[x].w, enemies[x].h);
                if (!(enemies[x].x > -enemies[x].w && enemies[x].x < OGL::screen->w+enemies[x].w && enemies[x].y > -enemies[x].h && enemies[x].y < OGL::screen->h+enemies[x].h)){
                    if (enemies[x].cruzo){
                        del.push_back(x);
                    }
                }else{
                    enemies[x].cruzo = true;
                }
            }
            while (del.size() > 0){
                enemies.erase(enemies.begin()+del[del.size()-1]);
                del.pop_back();
            }
            if (enemies.size() == 0){
                enabled = false;
            }
        }
        loops++;
    }
}

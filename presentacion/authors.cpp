#include "authors.h"

Authors::Authors(){
    angle = 0;
    speed = 2;
    finished = false;
    color_first = OGL::c(0,0,255);
    color_second = OGL::c(0,0,0);
    loops = 0;
}

void Authors::set_text(vector<string> text){
    TTF_Font* font = fonts::presentacion;
    int bigger_w = 0;
    for (int x = 0; x < text.size(); x++) {
        Text act;
        SDL_Surface* surf = TTF_RenderText_Blended(font, text[x].c_str(), color_second);
        act.text = OGL::generate_texture(surf);
        SDL_Surface* surf2 = TTF_RenderText_Blended(font, text[x].c_str(), color_first);
        act.text_first = OGL::generate_texture(surf2);
        act.w = surf->w;
        act.h = surf->h;
        act.surface = surf;
        act.surface_first = surf2;
        act.text_string = text[x];
        if (act.w > bigger_w) { bigger_w = act.w; }
        texts.push_back(act);
    }
    int GlobalW = bigger_w;
    int GlobalH = ((int)text.size()*(texts[0].h+3)-3);
    int GlobalX = OGL::screen->w/2-GlobalW/2;
    int GlobalY = OGL::screen->h/2-GlobalH/2;
    int GlobalY2 = GlobalY;
    globalx = GlobalX;
    globaly = GlobalY2;
    SDL_Surface* final_surface_first = OGL::create_void_surface(GlobalW, GlobalH);
    SDL_Surface* final_surface = OGL::create_void_surface(GlobalW, GlobalH);
    for (int x = 0; x < texts.size(); x++) {
        texts[x].x = GlobalX+(bigger_w/2-texts[x].w/2);
        texts[x].y = GlobalY;
        OGL::blit_surface_inside_another(texts[x].surface, final_surface, texts[x].x-GlobalX, texts[x].y-GlobalY2);
        OGL::blit_surface_inside_another(texts[x].surface_first, final_surface_first, texts[x].x-GlobalX, texts[x].y-GlobalY2);
        GlobalY += texts[0].h+3;
    }
    final_text.img = OGL::generate_texture(final_surface);
    final_text_first.img = OGL::generate_texture(final_surface_first);
    final_text.surface = final_surface;
    final_text_first.surface = final_surface_first;
    final_text.w = 0; final_text.h = 0;
    final_text_first.w = 0; final_text_first.h = 0;
}

void Authors::update(){
    if (angle < 360) {
        angle += 2;
        final_text.w += 1.2*speed;
        final_text.h += .3*speed;
        final_text_first.w = final_text.w;
        final_text_first.h = final_text.h;
        SDL_Surface* rotated_surface = OGL::rotate_surface(final_text.surface, (double)angle);
        SDL_Surface* rotated_surface_first = OGL::rotate_surface(final_text_first.surface, (double)angle);
        glDeleteTextures(1,(GLuint*)(&final_text.img));
        glDeleteTextures(1,(GLuint*)(&final_text_first.img));
        final_text.img = OGL::generate_texture(rotated_surface);
        SDL_FreeSurface(rotated_surface);
        final_text_first.img = OGL::generate_texture(rotated_surface_first);
        SDL_FreeSurface(rotated_surface_first);
    }
    if (angle >= 360){
        angle = 360;
        if (loops == 100){
            finished = true;
        }
        loops++;
    }
    globalx = OGL::screen->w/2-final_text.w/2;
    globaly = OGL::screen->h/2-final_text.h/2;
    for (int q = 0; q < 14; q++){
        if (q == 13) {
            OGL::blit_texture(final_text_first.img, globalx, globaly+q, final_text_first.w, final_text_first.h);
        }else{
            OGL::blit_texture(final_text.img, globalx, globaly+q, final_text.w, final_text.h);
        }
    }
}

bool Authors::get_finished(){
    return finished;
}

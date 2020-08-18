#ifndef TESTING_H
#define TESTING_H

#include <string>

using namespace std;

extern SDL_Window* window;
extern SDL_GLContext* context;
extern SDL_Surface* screen;
extern string testing_name;
extern int width  ;
extern int height ;
extern SDL_Event events;
void update_fps();
void start_testing(string tn);
void load_basic();
void refresh_screen();

#endif // TESTING_H

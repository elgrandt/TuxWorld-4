//
//  title.h
//  TW32
//
//  Created by Dylan Tasat on 14/09/14.
//  Copyright (c) 2014 GranDT&Newtonis. All rights reserved.
//

#ifndef TITLE_H_
#define TITLE_H_
#include "authors.h"

struct TuxCartel{
    GLint image;
    int w, h;
    int x, y;
    int angle;
    bool cruzo;
};

class Title{
    private:
        Authors* authors;
        bool enabled;
        vector<Text> letters;
        vector<TuxCartel> enemies;
        TuxCartel tux;
        int loops;
        int moving_tux;
        bool moving_enemies;
    public:
        Title();
        void enable(Authors* autores);
        void update();
        bool is_enabled();
};

#endif

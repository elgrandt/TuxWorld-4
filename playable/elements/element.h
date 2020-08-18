#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <vector>
#include "lincludes/mSDL.h"
#include "els.h"
#include "lincludes/mOPENGL.h"
#include "images.h"

/*** Para evitar errores ***/
class Stage;

class heyfriends{
    public:
        int j;
};

class Element{
    private:
        double x;
        double y;
        int W;
        int H;
        GLuint image;
        bool on;
        int rx;
        int ry;
        bool draw_enable;
    public:
        Stage* outside;
        //Stage *outside;
        /*** VARIABLES ***/
        int tags[4];
        int type;

        /*** FUNCTIONS ***/
        Element();

        /*** TYPES AND TAG ***/
        void add_tag(int tag);
        void set_type(int type);
        int get_type();

        /*** initialize ***/
        void initializate(Stage* my_stage);

        /*** position and dimension ***/
        double get_x();
        double get_y();
        void set_x(double x);
        void set_y(double y);
        void set_position (double x, double y);
        void sum_x(double sx);
        void sum_y(double sy);
        int get_w();
        int get_h();
        void set_w(int w);
        void set_h(int h);

        /*** texture ***/
        GLuint get_image();
        void set_image(GLuint image);

        bool is_on();
        bool is_tag(int tag);

        /*** REPETITIONS ***/
        int get_rx();
        int get_ry();
        void set_rx(int rx);
        void set_ry(int ry);

        /*** LOGIC UPDATE ***/
        virtual void update() = 0;

        /*** managment ***/
        void kill();
        void enabledraw();
        void disabledraw();
        bool checkdraw();
};

class Root : public Element{
    public:
        Root();
        ~Root();
        void update();
};
struct image_position_dimension{
    GLuint image;
    double x;
    double y;
    int w;
    int h;
    image_position_dimension(GLuint Dimage, double Dx,double Dy,int Dw, int Dh);
};

class ElementWIMG : public Element{
    protected:
        vector <image_position_dimension> myimages;
    public:
        vector <image_position_dimension> get_images();
};

#endif

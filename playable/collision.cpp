#include "collision.h"
#include "elements/element.h"

namespace coll{
    const char up     = 0;
    const char down   = 1;
    const char left   = 2;
    const char right  = 3;
    const char nocoll = 4;
}

collision::collision(double side,double distance){
    this->side = side;
    this->distance = distance;
}

collist collide(Element* from,Element* bywhat){

    /********** Cargamos la informacion **********/
    double MY_X = from->get_x(); double MY_Y = from->get_y();
    double MY_W = from->get_w(); double MY_H = from->get_h();
    double MYX2 = MY_X + MY_W  ; double MYY2 = MY_Y + MY_H  ;

    double E2_X = bywhat->get_x(); double E2_Y = bywhat->get_y();
    double E2_W = bywhat->get_w(); double E2_H = bywhat->get_h();
    double E2X2 = E2_X + E2_W    ; double E2Y2 = E2_Y + E2_H    ;


    collist colisiones; /** vector de almacenamiento de colisiones encontradas **/

    if (MY_Y >= E2_Y and MY_Y <= E2Y2){
	
        bool A = (MY_X <= E2_X and MYX2 >= E2X2);
        bool B = (MY_X >= E2_X and MYX2 <= E2X2);
        bool C = (MY_X > E2_X  and MY_X < E2X2);
        bool D = (MYX2 > E2_X  and MYX2 < E2X2);

        if(A){
            colisiones.push_back(collision(coll::up,E2_W));
        }else if(B){
            colisiones.push_back(collision(coll::up,MY_W));
        }else if(C){
            double dis = E2X2 - MY_X;
            colisiones.push_back(collision(coll::up,dis));
        }else if(D){
            double dis = MYX2 - E2_X;
            colisiones.push_back(collision(coll::up,dis));
        }
    }
    if (MYY2 >= E2_Y and MYY2 <= E2Y2){
        bool A = (MY_X <= E2_X and MYX2 >= E2X2);
        bool B = (MY_X >= E2_X and MYX2 <= E2X2);
        bool C = (MY_X > E2_X and MY_X < E2X2);
        bool D = (MYX2 > E2_X and MYX2 < E2X2);
        if(A){
            colisiones.push_back(collision(coll::down,E2_W));
        }else if(B){
            colisiones.push_back(collision(coll::down,MY_W));
        }else if(C){
            double dis = E2X2 - MY_X;
            colisiones.push_back(collision(coll::down,dis));
        }else if(D){
            double dis = MYX2 - E2_X;
            colisiones.push_back(collision(coll::down,dis));
        }
    }
    if (MY_X >= E2_X and MY_X <= E2X2){
        bool A = (MY_Y <= E2_Y and MYY2 >= E2Y2);
        bool B = (MY_Y >= E2_Y and MYY2 <= E2Y2);
        bool C = (MY_Y > E2_Y and MY_Y < E2Y2);
        bool D = (MYY2 > E2_Y and MYY2 < E2Y2);
        if (A){
            colisiones.push_back(collision(coll::left,E2_H));
        }else if(B){
            colisiones.push_back(collision(coll::left,MY_H));
        }else if(C){
            double dis = E2Y2 - MY_Y;
            colisiones.push_back(collision(coll::left,dis));
        }else if(D){
            double dis = MYY2 - E2_Y;
            colisiones.push_back(collision(coll::left,dis));
        }
    }
    if (MYX2 >= E2_X and MYX2 <= E2X2){
        bool A = (MY_Y <= E2_Y and MYY2 >= E2Y2);
        bool B = (MY_Y >= E2_Y and MYY2 <= E2Y2);
        bool C = (MY_Y > E2_Y and MY_Y < E2Y2);
        bool D = (MYY2 > E2_Y and MYY2 < E2Y2);
        if (A){
            colisiones.push_back(collision(coll::right,E2_H));
        }else if(B){
            colisiones.push_back(collision(coll::right,MY_H));
        }else if(C){
            double dis = E2Y2 - MY_Y;
            colisiones.push_back(collision(coll::right,dis));
        }else if(D){
            double dis = MYY2 - E2_Y;
            colisiones.push_back(collision(coll::right,dis));
        }
    }
    double total = 0;
    for (int x = 0;x < (signed)colisiones.size();x++){
        collision *actual = &colisiones[x];
        total += actual->distance;
    }

    for (int x = 0;x < (signed)colisiones.size();x++){
        collision *actual = &colisiones[x];
        int per = actual->distance / total * 100.0;
        actual->percentaje = per;
    }
    return colisiones;
}

collist get_max_collide(Element* from,Element* bywhat){
    collist data = collide(from,bywhat);
    collist final;
    for (int d = 0;d < data.size ();d++){
        if (final.size () == 0){
            final.push_back (data[d]);
        }else if(final[0].distance == data[d].distance){
            final.push_back (data[d]);
        }else if(final[0].distance < data[d].distance){
            final.clear ();
            final.push_back (data[d]);
        }
    }
    return final;
}


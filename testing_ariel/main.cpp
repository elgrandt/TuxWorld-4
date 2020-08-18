#include <iostream>
#include <vector>
#include <cstdio>

#include "lincludes/mSDL.h"
#include "graphical.h"
#include "manager.h"
#include "testing/testing.h"
#include "OGL/OGL.h"
#include "testing_2.h"
#include "testing_3.h"
#include <iostream>
#include <stdio.h>
using namespace std;

using namespace std;

typedef vector < pair <int(*)(),string> > func_list;

func_list funciones;

void evaluar_funciones();
void add_test( int(*func)() , string name );

int main( int argc, char *argv[] ){
    freopen("output.txt","w",stdout);
    cout<<"HOL"<<endl;

    load_basic();

    //int (*point)();
    //point = test_2;

    //add_test ( test_2 ,"testeo 2");
    add_test ( test_3 ,"testeo 3");

    evaluar_funciones();
}
void add_test(int(*func)(), string name){
    pair <int(*)(),string> par;
    par.first = func;
    par.second = name;
    funciones.push_back (par);
}

void evaluar_funciones(){
    int total = funciones.size ();
    int correct = 0;

    for (int x = 0;x < funciones.size ();x++){

        cout<<"Corriendo "<<funciones[x].second<<endl;
        int (*point)() = funciones[x].first;
        int status = point();
        if (status == 0){
            cout<<"Se corrio de manera correcta "<<endl;
            correct++;
        }else{
            cout<<"Errores:"<<status<<endl;
        }
    }
    cout<<"Testeos ejecutados:"<<total<<endl;
    cout<<"Testeos sin errores: "<<correct<< "("<<double(correct) / double(total) * 100.0 <<" % )"<<endl;
}

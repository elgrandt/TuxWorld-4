#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <map>
using namespace std;


namespace interpreter{
    struct level_element{
        string name;
        vector <string> properties;
    };
    struct bucle : level_element{
        vector <level_element*> my_content;
    };

    struct level_content{
        vector <level_element*> data;
        void load_content( string filename , int fromline );
    };


    class loaded_level{
        private:
            string name;
            string description;
            string author;
            int difficultly;
            level_content content;
        public:
            string get_name       ();
            string get_description();
            string get_author     ();
            int    get_difficulty ();
            void   load_name   ( string filename );
            void   load_content( string filename );
    };
    class Reader{
        private:
            map          <string , int> levels;
            vector       <loaded_level> list_levels;
        public:
            Reader();
            void load_level_name   (string filename);
            void load_all_level    (string filename);
            void clear_all         ();
            void clear_level       ( string name );
    };
}
#endif // INTERPRETER_H

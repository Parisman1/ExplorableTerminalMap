#ifndef Object_h
#define Object_h

#include <string>

using namespace std;

class Object{

    private:
        string name;
        string description;
    public:

        Object();
        ~Object();

        string Get_name();
        void Set_name(string);

        string Get_desc();
        void Set_desc(string);

};

#endif
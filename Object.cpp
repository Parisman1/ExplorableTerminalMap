#include "Object.h"

    Object::Object(){
        name = "";
    }
    Object::~Object(){

    }
    string Object::Get_name(){
        return name;
    }
    void Object::Set_name(string n){
        name = n;
    }
    string Object::Get_desc(){
        return description;
    }
    void Object::Set_desc(string d){
        description = d;
    }
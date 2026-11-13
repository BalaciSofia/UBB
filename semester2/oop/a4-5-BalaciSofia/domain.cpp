#include "domain.h"


//constructor
Dog::Dog(std::string b, std::string n,int a,std::string p){
    this->photograph = p;
    this->name = n;
    this->age = a;
    this->breed=b;
}

//default constructor
Dog::Dog() {
    this->breed=" ";
    this->name=" ";
    this->age=0;
    this->photograph=" ";
}

//get-----------------------------------
std::string Dog::get_breed() {
    return this->breed;
}
std::string Dog::get_name() {
    return this->name;
}
int Dog::get_age() {
    return this->age;
}

std::string Dog::get_photograph() {
    return this->photograph;
}

//set------------------------------------
void Dog :: update_age(int a){
    this->age = a;
}

void Dog :: update_name(std::string n){
    this->name=n;
}

void Dog :: update_photograph(std::string p){
    this->photograph=p;
}

//operators----------------------------------
bool Dog::operator==(const Dog& other) const {
    /*
     *Equality operator for the Dog class.
     */
    return (this->age == other.age &&
            this->breed==other.breed &&
            this->name==other.name &&
            this->photograph==other.photograph);
}

Dog& Dog::operator=(const Dog& other) {
    /*
     *Assignment operator for the Dog class.
     */
    if (this == &other)
        return *this;
    this->breed = other.breed;
    this->name = other.name;
    this->age = other.age;
    this->photograph = other.photograph;
    return *this;
}




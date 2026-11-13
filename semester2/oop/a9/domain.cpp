#include "domain.h"
#include <iostream>
#include <sstream>

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

void Dog :: update_breed(std::string b) {
    this->breed = b;
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

//cin/cout-------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Dog& d) {
    os << d.name << '~' << d.breed << '~' << d.age << '~' << d.photograph << '~';
    return os;
}

std::istream& operator>>(std::istream& is, Dog& d) {
    if(is.peek() == '\n') is.ignore();
    std::string str;
    std::getline(is, str);
    if(str.empty()) return is;
    std::istringstream iss(str);
    std::string name, breed, age, link;
    std::getline(iss, name, '~');
    std::getline(iss, breed, '~');
    std::getline(iss, age, '~');
    std::getline(iss, link, '~');
    d.update_name(name);
    d.update_breed(breed);
    d.update_age(stoi(age));
    d.update_photograph(link);
    return is;
}
//validator---------------------------------------------------

void DogValidator::validate(Dog dog) const {
    if (dog.get_breed().empty())
        throw std::logic_error("breed cannot be empty");
    if (dog.get_name().empty())
        throw std::logic_error("name cannot be empty");
    if (dog.get_age() < 0)
        throw std::logic_error("age cannot be negative");
}

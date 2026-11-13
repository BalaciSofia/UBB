#pragma once
#include <string>

class Dog{
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;

public:
    std::string get_breed();
    std::string get_name();
    int get_age();
    std::string get_photograph();
    Dog();
    Dog(std::string breed, std::string name,int age,std::string photograph);
    void update_age( int age);
    void update_name( std::string name);
    void update_photograph(std::string photograph);
    bool operator==(const Dog& other) const;
    Dog& operator=(const Dog& other);
};
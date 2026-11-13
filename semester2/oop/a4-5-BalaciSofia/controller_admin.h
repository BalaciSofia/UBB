#pragma once
#include "repo.h"
class Controller_admin {
    private:
    Repository &repo;
    public:
    Controller_admin(Repository &repo);
    void Add_Dog(int age,std::string name,std::string breed,std::string photograph);
    void Remove_Dog(std::string name);
    void Update_name(std::string name,std::string new_name);
    void Update_age(std::string name,int age);
    void Update_photograph(std::string name,std::string new_photograph);
    void initial_data();
    int Search_name(std::string name);
    DynamicArray<Dog>& get_dogs_controller();
};
#pragma once
#include "repo.h"

class Controller_user {
private:
    Repository &repo;
    public:
    Controller_user(Repository &repo);
    Dog get_current_dog_controller(int i);
    DynamicArray<Dog>& get_adopted_dogs_controller();
    void add_dog_adoptedlist(Dog d);
    DynamicArray<Dog> filter_breed(DynamicArray<Dog> &r, std::string breed);
    DynamicArray<Dog> filter_age(DynamicArray<Dog> &r, int age);
};

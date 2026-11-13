#pragma once
#include "dynamicarray.h"
#include "domain.h"

class Repository {
    private:
    DynamicArray<Dog> dogs;
    DynamicArray<Dog> adopted_dogs;
    public:

    void add_dog(Dog dog);
    void remove_dog(Dog dog);

    void update_dog_name(Dog dog, std::string name);
    void update_dog_age(Dog dog, int age);
    void update_dog_photograph(Dog dog, std::string photograph);

    int search_dog_name(std::string name);
    DynamicArray<Dog> &get_dogs();

    Dog get_current_dog_repo(int i);
    void add_dog_adopted(Dog dog);
    DynamicArray<Dog> &get_adopted_dogs();
};
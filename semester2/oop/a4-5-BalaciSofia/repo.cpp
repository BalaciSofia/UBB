
#include "repo.h"
#include <iostream>


void Repository::add_dog(Dog dog) {
    /*
     *adds a dog to the repository
     *param:A dog object
     */
    if (search_dog_name(dog.get_name()) !=-1)
        throw std::logic_error("Dog already exists");
    this->dogs.append(dog);
}

void Repository:: remove_dog(Dog dog) {
    /*
     *removes a dog from the repository
     *param:A dog object
     */
    for (int i=0; i< this->dogs.getSize();i++) {
        if (this->dogs[i]==dog) {
            this->dogs.remove_index(i);
            return;
        }
    }
    throw std::logic_error("Dog not found");
}

void Repository::update_dog_name(Dog dog, std::string name) {
    /*
     *updates a dogs name
     *param dog:dog object
     *param name:the new name of the dog object
     */
    for (int i = 0; i < dogs.getSize(); i++) {
        if (dogs.operator[](i) == dog) {
            dogs.operator[](i).update_name(name);
            return;
        }
    }
}
void Repository::update_dog_age(Dog dog, int age) {
    /*
     *updates a dogs age
     *param dog:dog object
     *param name:the new age of the dog object
     */
    for (int i = 0; i < dogs.getSize(); i++) {
        if (dogs.operator[](i) == dog) {
            dogs[i].update_age(age);
            return;
        }
    }
}

void Repository::update_dog_photograph(Dog dog, std::string photograph) {
    /*
     *updates a dogs photograph
     *param dog:dog object
     *param photograph:the new photograph of the dog object
     */
    for (int i = 0; i < dogs.getSize(); i++) {
        if (this->dogs[i] == dog) {
            this->dogs[i].update_photograph(photograph);
            return;
        }
    }
}

int Repository::search_dog_name(std::string name) {
    /*
     *searches a dog in the repository by it s name
     */
    for (int i = 0; i < dogs.getSize(); i++) {
        if (this->dogs[i].get_name() == name)
            return i;
    }
    return -1;
}

DynamicArray<Dog>& Repository::get_dogs() {
    /*
     *returns the dynamic array of dogs
     */
    return this->dogs;
}

Dog Repository::get_current_dog_repo(int i) {
    return this->dogs[i];
}

void Repository::add_dog_adopted(Dog dog) {
    this->adopted_dogs.append(dog);
}
DynamicArray<Dog>& Repository::get_adopted_dogs() {
    return this->adopted_dogs;
}
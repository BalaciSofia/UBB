
#include "controller_user.h"

#include "controller_admin.h"

Controller_user::Controller_user(Repository &repo) : repo(repo) { }

Dog Controller_user::get_current_dog_controller(int i) {
    return this->repo.get_current_dog_repo(i);
}

DynamicArray<Dog>& Controller_user::get_adopted_dogs_controller() {
    return this->repo.get_adopted_dogs();
}

void Controller_user::add_dog_adoptedlist(Dog d) {
  this->repo.add_dog_adopted(d);
}

DynamicArray<Dog> Controller_user::filter_breed(DynamicArray<Dog> &r, std::string breed) {
    DynamicArray<Dog> dogs;
    for (int i = 0; i < r.getSize(); i++) {
        if (r[i].get_breed() == breed) {
            dogs.append(r[i]);
        }
    }
    return dogs;
}


DynamicArray<Dog> Controller_user::filter_age(DynamicArray<Dog> &r, int age) {
    DynamicArray<Dog> dogs;
    for (int i = 0; i < r.getSize(); i++) {
        if (r[i].get_age() <= age) {
            dogs.append(r[i]);
        }
    }
    return dogs;
}

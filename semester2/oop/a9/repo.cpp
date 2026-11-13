
#include "repo.h"
#include <iostream>
#include <fstream>

void Repository::load_dogs() {
    std::ifstream file(this->filename);
    if (!file.is_open()) return;
    Dog dog;
    while (file >> dog)
        this->dogs.push_back(dog);
    file.close();
}

void Repository::save_dogs() {
    std::ofstream file(this->filename);
    if (!file.is_open()) return;
    for (Dog& dog : this->dogs)
        file << dog << std::endl;
    file.close();
}

Repository :: Repository(std::string filename) : filename(filename) {
    this->load_dogs();
}

void Repository::add_dog(Dog dog) {
    /*
     *adds a dog to the repository
     *param:A dog object
     */
    DogValidator vlid;
    vlid.validate(dog);
    if (search_dog(dog) !=-1)
        throw RepositoryError("Dog already exists");
    this->dogs.push_back(dog);
    this->save_dogs();
}

void Repository:: remove_dog(Dog dog) {
    /*
     *removes a dog from the repository
     *param:A dog object
     */
    int index = 0;
    for(auto i : this->dogs) {
        if (i == dog) {
            this->dogs.erase(this->dogs.begin() + index);
            this->save_dogs();
            return;
        }
        index++;
    }
    throw RepositoryError("Dog not found");
}

void Repository::update_dog_name(Dog dog, std::string name) {
    /*
     *updates a dogs name
     *param dog:dog object
     *param name:the new name of the dog object
     */
    if(this->search_dog_name(name)!=-1)
        throw RepositoryError("This dog name already exists");
    for (auto &i : this->dogs) {
        if (i == dog) {
            i.update_name(name);
            this->save_dogs();
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
    for ( auto &i : this->dogs ) {
        if (i == dog) {
            i.update_age(age);
            this->save_dogs();
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
    for (auto &i : this->dogs) {
        if (i == dog) {
            i.update_photograph(photograph);
            this->save_dogs();
            return;
        }
    }
}

int Repository::search_dog(Dog dog) {
    /*
     *searches a dog in the repository
     */
    int p=0;
    for (auto i : this->dogs) {
        if (i == dog)
            return p;
        p++;
    }
    return -1;
}

int Repository::search_dog_name(std::string name) {
    int index = 0;
    for (auto i : this->dogs) {
        if (i.get_name() == name)
            return index;
        index++;
    }
    return -1;
}

std::vector<Dog>& Repository::get_dogs() {
    /*
     *returns the array of dogs
     */
    return this->dogs;
}

Dog Repository::get_current_dog_repo(int i) {
    /*
   *returns the dog on index i in the array
   */
    return this->dogs[i];
}

void Repository::add_dog_adopted(Dog dog) {
    /*
   *adds a dog to the adopted dogs array
   */
    this->adopted_dogs.push_back(dog);
}

std::vector<Dog>& Repository::get_adopted_dogs() {
    /*
   *returns the adopted dog array
   */
    return this->adopted_dogs;
}

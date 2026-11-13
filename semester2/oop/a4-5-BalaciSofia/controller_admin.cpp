
#include "controller_admin.h"
#include <iostream>
#include <utility>
#include "domain.h"

Controller_admin::Controller_admin(Repository &repo) : repo(repo) { }


void Controller_admin::Add_Dog(int age,std::string name,std::string breed,std::string photograph) {
    /*
     *adds a dog to the repo
     *param age:age of the dog
     *param name:name of the dog
     *param breed:breed of the dog
     *param photograph:photograph of yhe dog
     */
    Dog dog=Dog(breed,name,age,photograph);
    this->repo.add_dog(dog);
}

void  Controller_admin::Remove_Dog(std::string name) {
    /*
     *removes a dog from the repo
     *pram name: name of the dog to be removed
     */
    int index=this->repo.search_dog_name(name);
    if (index==-1)
        throw std::logic_error("Dog not found");
    this->repo.remove_dog(this->repo.get_dogs()[index]);
}
void Controller_admin:: Update_name(std::string name,std::string new_name) {
    /*
     *updates a dogs name
     */
    int index=this->repo.search_dog_name(name);
    if (index==-1)
        throw std::logic_error("Dog not found");
    this->repo.update_dog_name(this->repo.get_dogs().operator[](index),std::move(new_name));
}
void Controller_admin:: Update_age(std::string name,int age) {
    /*
     *updates a dogs age
     */
    int index=this->repo.search_dog_name(name);
    if (index==-1)
        throw std::logic_error("Dog not found");
    this->repo.update_dog_age(this->repo.get_dogs()[index],age);
}
void Controller_admin:: Update_photograph(std::string name,std::string new_photograph) {
    /*
     *updates a dogs photograph
     */
    int index=this->repo.search_dog_name(name);
    if (index==-1)
        throw std::logic_error("Dog not found");
    this->repo.update_dog_photograph(this->repo.get_dogs()[index],std::move(new_photograph));
}

DynamicArray<Dog>& Controller_admin::get_dogs_controller() {
    return this->repo.get_dogs();
}

int Controller_admin::Search_name(std::string name) {
    return this->repo.search_dog_name(name);
}

void Controller_admin::initial_data() {
    this->Add_Dog(1, "Tito", "Corgi", "https://www.zooplus.ro/ghid/caini/rase-de-caini/pembroke-welsh-corgi");
    this->Add_Dog(2, "Rex", "Husky", "https://www.akc.org/dog-breeds/siberian-husky/");
    this->Add_Dog(3, "Ina", "Bichon Frise", "https://www.akc.org/dog-breeds/bichon-frise/");
    this->Add_Dog(4, "Marco", "Beagle", "https://www.akc.org/dog-breeds/beagle/");
    this->Add_Dog(5, "Sasha", "Poodle", "https://www.akc.org/dog-breeds/poodle/");
    this->Add_Dog(6, "Rocco", "Golden Retriever", "https://www.akc.org/dog-breeds/golden-retriever/");
    this->Add_Dog(7, "Bella", "Labrador", "https://www.akc.org/dog-breeds/labrador-retriever/");
    this->Add_Dog(8, "Charlie", "Dachshund", "https://www.akc.org/dog-breeds/dachshund/");
    this->Add_Dog(9, "Milo", "Shiba Inu", "https://www.akc.org/dog-breeds/shiba-inu/");
    this->Add_Dog(10, "Luna", "Border Collie", "https://www.akc.org/dog-breeds/border-collie/");
    this->Add_Dog(11, "Finn", "Corgi", "https://www.akc.org/dog-breeds/pembroke-welsh-corgi/");
    this->Add_Dog(12, "Ghost", "Shiba Inu", "https://www.akc.org/dog-breeds/shiba-inu/");
    this->Add_Dog(13, "Bailey", "Golden Retriever", "https://www.akc.org/dog-breeds/golden-retriever/");
    this->Add_Dog(14, "Zoey", "Beagle", "https://www.akc.org/dog-breeds/beagle/");
    this->Add_Dog(15, "Max", "Husky", "https://www.akc.org/dog-breeds/siberian-husky/");
    this->Add_Dog(16, "Oscar", "Poodle", "https://www.akc.org/dog-breeds/poodle/");
    this->Add_Dog(17, "Daisy", "Bichon Frise", "https://www.akc.org/dog-breeds/bichon-frise/");
    this->Add_Dog(18, "Cooper", "Labrador", "https://www.akc.org/dog-breeds/labrador-retriever/");
    this->Add_Dog(19, "Poppy", "Dachshund", "https://www.akc.org/dog-breeds/dachshund/");
    this->Add_Dog(20, "Nala", "Border Collie", "https://www.akc.org/dog-breeds/border-collie/");
}



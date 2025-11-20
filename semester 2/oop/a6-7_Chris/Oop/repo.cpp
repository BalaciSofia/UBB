#include "repo.h"
#include <fstream>
#include <iostream>

Repository::Repository(const std::string& filename_) : filename{filename_} {
    /*
     * Constructor for the repository
     * @param filename_ - the name of the file to load the dogs from
     */
    this->load_from_file();
}

void Repository::load_from_file() {
    /*
     * Loads the dogs from the file
     */
    std::ifstream file(this->filename);
    if (!file.is_open()) return;
    Dog dog;
    while (file >> dog)
        this->dogs.push_back(dog);
    file.close();
}

void Repository::save_to_file() {
    /*
     * Saves the dogs to the file
     */
    std::ofstream file(this->filename);
    if (!file.is_open()) return;
    for (auto i : this->dogs)
        file << i << "\n";
    file.close();
}

void Repository::add_dog(const Dog& dog) {
    /*
     * Adds a dog to the repository
     * @param dog - the dog to add
     * @return 1 if the dog was added, 0 if the dog already exists
     */
    for (auto i : dogs)
        if (dog == i)
            throw RepositoryError("Dog already exists");
    this->dogs.push_back(dog);
    this->save_to_file();
}

void Repository::remove_dog_by_index(const int& index) {
    /*
     * Removes a dog from the repository at a given index
     * @param index - the index of the dog to remove
     */
    this->dogs.erase(this->dogs.begin() + index);
    this->save_to_file();
}

void Repository::update_name(const int& index, const std::string& name) {
    /*
     * Updates the name of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param name - the new name of the dog
     */
    this->dogs[index].set_name(name);
    this->save_to_file();
}

void Repository::update_breed(const int& index, const std::string& breed) {
    /*
     * Updates the breed of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param breed - the new breed of the dog
     */
    this->dogs[index].set_breed(breed);
    this->save_to_file();
}

void Repository::update_age(int index, int age) {
    /*
     * Updates the age of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param age - the new age of the dog
     */
    this->dogs[index].set_age(age);
    this->save_to_file();
}

void Repository::update_photo_link(const int &index, const std::string &photo_link) {
    /*
     * Updates the photo link of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param photo_link - the new photo link of the dog
     */
    this->dogs[index].set_photo_link(photo_link);
    this->save_to_file();
}

std::vector<Dog> Repository::get_dogs() {
    /*
     * Gets the dogs from the repository
     * @return the dogs in the repository
     */
    return this->dogs;
}
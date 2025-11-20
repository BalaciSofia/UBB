#include "services.h"
#include "dog.h"
#include <algorithm>
#include <fstream>

AdminController::AdminController(Repository &repo) : repo{repo} {}

void AdminController::add_dog(const Dog &dog) const {
    /*
     * Adds a dog to the repository
     * @param dog - the dog to add
     */
    this->repo.add_dog(dog);
}

void AdminController::remove_dog(const int& index) const {
    /*
     * Removes a dog from the repository at a given index
     * @param index - the index of the dog to remove
     */
    this->repo.remove_dog_by_index(index);
}

void AdminController::update_breed(const int& index, const std::string& breed) const {
    /*
     * Updates the breed of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param breed - the new breed of the dog
     */
    this->repo.update_breed(index, breed);
}

void AdminController::update_name(const int& index, const std::string& name) const {
    /*
     * Updates the name of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param name - the new name of the dog
     */
    this->repo.update_name(index, name);
}

void AdminController::update_age(int index, int age) const {
    /*
     * Updates the age of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param age - the new age of the dog
     */
    this->repo.update_age(index, age);
}

void AdminController::update_photo_link(const int& index, const std::string& photo_link) const {
    /*
     * Updates the photo link of a dog in the repository at a given index
     * @param index - the index of the dog to update
     * @param photo_link - the new photo link of the dog
     */
    this->repo.update_photo_link(index, photo_link);
}

std::vector<Dog> AdminController::get_dogs() const {
    /*
     * Gets the dogs from the repository
     * @return the dogs from the repository
     */
    return this->repo.get_dogs();
}

// USER CONTROLLER CODE BELOW
// ===========================================================

UserController::UserController(Repository &repo, const std::string& filename_) : repo{repo}, filename{filename_} {
    std::ofstream temp(filename);
}

std::vector<std::pair<Dog, int>> UserController::get_dogs() const {
    /*
     * Gets the dogs from the repository
     *
     * @returns the dogs from the repository
     */
    std::vector<Dog> dogs = this->repo.get_dogs();
    std::vector<std::pair<Dog, int>> temp;
    int index = 0;
    for(auto i : dogs) {
        temp.emplace_back(i, index);
        index++;
    }
    return temp;
}

std::vector<std::pair<Dog, int>> UserController::get_filtered_dogs(const std::string& breed, const int max_age) const {
    /*
     * Gets the dogs from the repository that match the given breed and age
     *
     * @param breed - the breed of the dog
     * @param max_age - the maximum age of the dog
     * @return the dogs from the repository that match the given breed and age
     */
    std::vector<Dog> dogs = this->repo.get_dogs();
    std::vector<std::pair<Dog, int>> temp;
    int index = 0;
    for (auto i : dogs) {
        if ((i.get_breed() == breed || breed == "") && i.get_age() <= max_age)
            temp.emplace_back(i, index);
        index++;
    }
    return temp;
}

std::vector<std::pair<Dog, int>> UserController::get_adoption_list() const {
    /*
     * Gets the adoption list
     *
     * @return the adoption list
     */
    return this->adoption_list;
}

void UserController::add_dog_to_adoption_list(const std::pair<Dog, int>& dog) {
    /*
     * Adds a dog to the adoption list
     *
     * @param dog - the dog to add to the adoption list
     * @return true if the dog was added, false if the dog already exists in the adoption list
     */
    for (auto i : this->adoption_list)
        if (i.second == dog.second)
            throw ControllerError("dog already in adoption list");
    this->adoption_list.emplace_back(dog);
    this->write_to_file();
}

bool comp(std::pair<Dog, int> a, std::pair<Dog, int> b) {
    return a.second > b.second;
}

void UserController::adopt_dogs() {
    /*
     * Adopts the dogs in the adoption list
     */
    sort(adoption_list.begin(), adoption_list.end(), comp);
    while(!this->adoption_list.empty()) {
        this->repo.remove_dog_by_index(this->adoption_list[0].second);
        this->adoption_list.erase(this->adoption_list.begin());
    }
}

std::string UserController::get_file() {
    /*
     * Gets the file name
     *
     * @return the file name
     */
    return this->filename;
}

void CSVUserController::write_to_file() {
    /*
     * Writes the adoption list to a CSV file
     */
    std::ofstream file(this->get_file());
    for (auto i : this->adoption_list) {
        Dog d = i.first;
        file << d.get_breed() << "," << d.get_name() << "," << d.get_age() << "," << d.get_photo_link() << "\n";
    }
    file.close();
}

void HTMLUserController::write_to_file() {
    /*
     * Writes the adoption list to an HTML file
     */
    std::ofstream file(this->get_file());
    file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body>\n";
    file << "<table border=\"1\">\n";
    file << "<tr><th>Breed</th><th>Name</th><th>Age</th><th>Photo</th></tr>\n";

    for (const auto& i : this->adoption_list) {
        Dog d = i.first;
        file << "<tr>";
        file << "<td>" << d.get_breed() << "</td>";
        file << "<td>" << d.get_name() << "</td>";
        file << "<td>" << d.get_age() << "</td>";
        file << "<td><a href=\"" << d.get_photo_link() << "\">Link</a></td>";
        file << "</tr>\n";
    }

    file << "</table>\n</body>\n</html>";
    file.close();
}
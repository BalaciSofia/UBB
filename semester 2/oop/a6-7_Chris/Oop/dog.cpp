#include "dog.h"
#include <string>
#include <sstream>
#include <iostream>

Dog::Dog(const std::string &breed, const std::string &name, int age, const std::string &photo_link) {
    /*
     * Constructor for the Dog class
     * @param breed - breed of the dog
     * @param name - name of the dog
     * @param age - age of the dog
     * @param photo_link - photo link of the dog
     */
    this->breed = breed;
    this->name = name;
    this->age = age;
    this->photo_link = photo_link;
}

std::string Dog::get_breed() {
    /*
     * Getter for the breed of the dog
     */
    return this->breed;
}

std::string Dog::get_name() {
    /*
     * Getter for the name of the dog
     */
    return this->name;
}

int Dog::get_age() const {
    /*
     * Getter for the age of the dog
     */
    return this->age;
}

std::string Dog::get_photo_link() {
    /*
     * Getter for the photo link of the dog
     */
    return this->photo_link;
}

std::string Dog::to_string() const {
    /*
     * Converts the dog object to a string representation
     */
    return (this->breed + ";" + this->name + ";" + std::to_string(this->age) + ";" + this->photo_link + ";");
}

void Dog::set_breed(const std::string &breed) {
    /*
     * Setter for the breed of the dog
     * @param breed - breed of the dog
     */
    this->breed = breed;
}

void Dog::set_name(const std::string &name) {
    /*
     * Setter for the name of the dog
     * @param name - name of the dog
     */
    this->name = name;
}

void Dog::set_age(int age) {
    /*
     * Setter for the age of the dog
     * @param age - age of the dog
     */
    this->age = age;
}

void Dog::set_photo_link(const std::string &photo_link) {
    /*
     * Setter for the photo link of the dog
     * @param photo_link - photo link of the dog
     */
    this->photo_link = photo_link;
}

bool Dog::operator==(const Dog &other) const {
    /*
     * Overloading the == operator to compare two Dog objects
     * @param other - the other Dog object to compare with
     */
    return (this->name == other.name && this->breed == other.breed && this->age == other.age);
}

std::ostream &operator<<(std::ostream &os, const Dog &dog) {
    /*
     * Overloading the << operator to print a Dog object
     * @param os - the output stream
     * @param dog - the Dog object to print
     */
    os << dog.to_string();
    return os;
}

std::istream &operator>>(std::istream &is, Dog &dog) {
    /*
     * Overloading the >> operator to read a Dog object
     * @param is - the input stream
     * @param dog - the Dog object to read into
     */
    if (is.peek() == '\n') is.ignore();
    std::string dog_string;
    std::getline(is, dog_string);
    if (dog_string.empty())
        return is;
    std::stringstream ss {dog_string};
    std::string breed, name, age, photo_link;
    std::getline(ss, breed, ';');
    std::getline(ss, name, ';');
    std::getline(ss, age, ';');
    std::getline(ss, photo_link, ';');
    dog.set_breed(breed);
    dog.set_name(name);
    dog.set_age(std::stoi(age));
    dog.set_photo_link(photo_link);
    return is;
}

void Validator::validate(Dog dog) const {
    /*
     * Validates the dog object
     * @param dog - the dog object to validate
     */
    if (dog.get_breed().empty())
        throw ValidationError("breed cannot be empty");
    if (dog.get_name().empty())
        throw ValidationError("name cannot be empty");
    if (dog.get_age() < 0)
        throw ValidationError("age cannot be negative");
    if (dog.get_photo_link().empty())
        throw ValidationError("photo link cannot be empty");
}
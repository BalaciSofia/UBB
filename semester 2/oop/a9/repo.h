#pragma once
#include "domain.h"
#include <vector>

class RepositoryError : public std::exception {
private:
    std::string message;
public:
    explicit RepositoryError(const std::string& message_) : message{message_} {}
    const char* what() {
        return this->message.c_str();
    }
};

class Repository {
private:
    std::string filename;
    std::vector<Dog> dogs;
    std::vector<Dog> adopted_dogs;
    void load_dogs();
    void save_dogs();
public:
    Repository(std::string filename);

    void add_dog(Dog dog);
    void remove_dog(Dog dog);

    void update_dog_name(Dog dog, std::string name);
    void update_dog_age(Dog dog, int age);
    void update_dog_photograph(Dog dog, std::string photograph);

    int search_dog(Dog dog);
    int search_dog_name(std::string name);
    std::vector<Dog> &get_dogs();

    Dog get_current_dog_repo(int i);
    void add_dog_adopted(Dog dog);
    std::vector<Dog> &get_adopted_dogs();
};

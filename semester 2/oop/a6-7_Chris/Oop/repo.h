#pragma once
#include "dog.h"
#include <vector>
#include <exception>

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
    void load_from_file();
    void save_to_file();
public:
    explicit Repository(const std::string& filename_);
    void add_dog(const Dog& dog);
    void remove_dog_by_index(const int& index);
    void update_breed(const int& index, const std::string& breed);
    void update_name(const int& index, const std::string& name);
    void update_age(int index, int age);
    void update_photo_link(const int& index, const std::string& photo_link);
    std::vector<Dog> get_dogs();
};
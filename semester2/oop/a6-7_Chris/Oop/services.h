#pragma once
#include "repo.h"
#include "dog.h"
#include <vector>

class AdminController {
private:
    Repository &repo;
public:
    explicit AdminController(Repository &repo);
    void add_dog(const Dog& dog) const;
    void remove_dog(const int& index) const;
    void update_breed(const int& index, const std::string& breed) const;
    void update_name(const int& index, const std::string& name) const;
    void update_age(int index, int age) const;
    void update_photo_link(const int& index, const std::string& photo_link) const;
    std::vector<Dog> get_dogs() const;
};

class UserController {
protected:
    Repository &repo;
    std::string filename;
    std::vector<std::pair<Dog, int>> adoption_list;
public:
    UserController(Repository &repo, const std::string& filename_);
    std::vector<std::pair<Dog, int>> get_dogs() const;
    std::vector<std::pair<Dog, int>> get_filtered_dogs(const std::string& breed, int max_age) const;
    std::vector<std::pair<Dog,int>> get_adoption_list() const;
    void add_dog_to_adoption_list(const std::pair<Dog, int>& dog);
    void adopt_dogs();
    std::string get_file();
    virtual void write_to_file() = 0;
};

class ControllerError : public std::exception {
private:
    std::string message;
public:
    ControllerError(const std::string& message) : message{message} {}
    const char* what() {
        return message.c_str();
    }
};

class CSVUserController : public UserController {
public:
    CSVUserController(Repository &repo, const std::string &filename) : UserController(repo, filename) {}
    void write_to_file() override;
};

class HTMLUserController : public UserController {
public:
    HTMLUserController(Repository &repo, const std::string &filename) : UserController(repo, filename) {}
    void write_to_file() override;
};
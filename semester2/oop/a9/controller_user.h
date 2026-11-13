#pragma once
#include "repo.h"

class Controller_user {
protected:
    Repository &repo;
    std::string filename;
public:
    Controller_user(Repository &repo, std::string filename);
    std::string get_file();
    Dog get_current_dog_controller(int i);
    std::vector<Dog>& get_adopted_dogs_controller();
    void add_dog_adoptedlist(Dog d);
    std::vector<Dog> filter_breed(std::vector<Dog> &r, std::string breed);
    std::vector<Dog> filter_age(std::vector<Dog> &r, int age);
    virtual void write_to_file() = 0;
};

class Controller_CSV : public Controller_user {
public:
    Controller_CSV(Repository &repo, const std::string &filename);
    void write_to_file() override;
};

class Controller_HTML : public Controller_user {
public:
    Controller_HTML(Repository &repo, const std::string &filename);
    void write_to_file() override;
};

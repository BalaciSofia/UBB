//
// Created by balac on 5/31/2025.
//

#ifndef COMMAND_H
#define COMMAND_H
#include "repo.h"

class command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddCommand : public command {
    Repository& repo;
    Dog item;
public:
    AddCommand(Repository& r, const Dog& i);
    void execute() override ;
    void undo() override ;
};

class RemoveCommand : public command {
    Repository& repo;
    Dog item;
public:
    RemoveCommand(Repository& r, const Dog& i);
    void execute() override ;
    void undo() override ;
};


class UpdateNameCommand : public command {
    Repository& repo;
    Dog item;
    std::string new_name,old_name;
    public:
    UpdateNameCommand(Repository& r,Dog& i,std::string old_name,std::string new_name);
    void execute() override ;
    void undo() override ;
};

class UpdateAgeCommand : public command {
    Repository& repo;
    Dog item;
    int new_age,old_age;
    public:
    UpdateAgeCommand(Repository& r, Dog& i, int age);
    void execute() override ;
    void undo() override ;
};

class UpdatePhotographCommand : public command {
    Repository& repo;
    Dog item;
    std::string new_photograph,old_photograph;
    public:
    UpdatePhotographCommand(Repository& r, Dog& i, std::string photograph);
    void execute() override ;
    void undo() override ;
};
#endif //COMMAND_H

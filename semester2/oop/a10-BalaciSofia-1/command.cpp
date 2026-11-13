//
// Created by balac on 5/31/2025.
//

#include "command.h"
//
// Created by balac on 5/31/2025.
//


AddCommand::AddCommand(Repository& r, const Dog& i) : repo(r), item(i) {}

void AddCommand::execute() {
    this->repo.add_dog(item);
}
void AddCommand::undo(){
    this->repo.remove_dog(item);
}


RemoveCommand::RemoveCommand(Repository& r, const Dog& i) : repo(r), item(i) {}

void RemoveCommand::execute(){
    this->repo.remove_dog(item);
}
void RemoveCommand::undo(){
    this->repo.add_dog(item);
}

UpdateNameCommand::UpdateNameCommand(Repository &r,Dog &i,std::string old_name,std::string new_name) : repo(r), item(i),old_name(old_name), new_name(new_name){
}

void UpdateNameCommand::execute() {
    this->repo.update_dog_name(this->item, this->new_name);
}
void UpdateNameCommand::undo() {
    Dog dog = this->item;
    dog.update_name(this->new_name);
    this->repo.update_dog_name(dog, this->old_name);
}

UpdateAgeCommand::UpdateAgeCommand(Repository &r, Dog &i, int age): repo(r), item(i), new_age(age) {
    this->old_age = i.get_age();
}

void UpdateAgeCommand::execute() {
    this->repo.update_dog_age(this->item, this->new_age);
}

void UpdateAgeCommand::undo() {
    Dog dog = this->item;
    dog.update_age(this->new_age);
    this->repo.update_dog_age(dog, this->old_age);
}

UpdatePhotographCommand::UpdatePhotographCommand(Repository &r, Dog &i, std::string photograph): repo(r), item(i), new_photograph(photograph) {
    this->old_photograph = i.get_photograph();
}
void UpdatePhotographCommand::execute() {
    this->repo.update_dog_photograph(this->item, this->new_photograph);
}

void UpdatePhotographCommand::undo() {
    Dog dog = this->item;
    dog.update_photograph(this->new_photograph);
    this->repo.update_dog_photograph(dog, this->old_photograph);
}
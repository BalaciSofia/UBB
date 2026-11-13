//
// Created by balac on 6/17/2025.
//

#include "Service.h"

#include <algorithm>

std::vector<Researcher> Service::getResearchers_service() {
    return this->repo.getResearchers();
}

std::vector<Idea> Service::getIdeas_service() {
    return this->repo.getIdeas();
}

std::vector<Idea> Service::sortedIdeas() {
    std::vector<Idea> ideas = this->repo.getIdeas();
    std::sort(ideas.begin(), ideas.end(),[](Idea a, Idea b) {
        return a.getDuration() < b.getDuration();
    });
}

void Service::addIdea(std::string title,std::string description,std::string creator,std::string status,int duration) {
    Idea idea(title,description,creator,status,duration);
    this->repo.addIdea_repo(idea);
    this->notifyObservers();
}

void Service::UpdateStatus(Idea i,std::string status) {
    this->repo.UpdateStatus_repo(i,status);
    this->notifyObservers();
}

void Service::writetofile(std::string filename) {
    this->repo.save(filename);
}
bool Service::hasaccepted(Researcher r) {
    for (auto i:this->getIdeas_service()) {
        if (i.getCreator()==r.getName() && i.getStatus()=="accepted") {
            return true;
        }
    }
    return false;
}

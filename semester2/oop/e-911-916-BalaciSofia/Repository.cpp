//
// Created by balac on 6/17/2025.
//

#include "Repository.h"

#include <algorithm>
#include <fstream>
#include <string>

Repository::Repository(std::string filename1, std::string filename2):filename1(filename1),filename2(filename2){
    this->load();
}

void Repository::load() {
    std::ifstream file1(filename1);
    if (!file1.is_open()) {
        throw std::runtime_error("Could not open file: " + filename1);
    }
    Researcher researcher;
    while (file1 >> researcher) {
        researchers.push_back(researcher);
    }
    file1.close();

    std::ifstream file2(filename2);
    if (!file2.is_open()) {
        throw std::runtime_error("Could not open file: " + filename2);
    }
    Idea idea;
    while (file2 >>idea) {
        ideas.push_back(idea);
    }
    file2.close();
}

std::vector<Idea> Repository::acceptedIdeas() {
    std::vector<Idea> rez;
    for (auto i:this->ideas) {
        if (i.getStatus()=="accepted")
            rez.push_back(i);
    }
    return rez;
}

void Repository::save(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::vector<Idea> ideas = this->acceptedIdeas();
    std::sort(ideas.begin(), ideas.end(),[](Idea a,Idea b) {
        return a.getDuration() < b.getDuration();
    });
    for (auto& idea : ideas) {
        file << idea.getTitle()+"["+idea.getCreator()+"]"+std::to_string(idea.getDuration())+ ","+idea.getDescription()<<" \n";
    }
    file.close();
}

std::vector<Idea> Repository::getIdeas() {
    return ideas;
}

std::vector<Researcher> Repository::getResearchers() {
    return researchers;
}
void Repository::addIdea_repo(Idea idea) {
    this->ideas.push_back(idea);
}

void Repository::UpdateStatus_repo(Idea i, std::string status) {
    for (auto& idea : ideas) {
        if (idea.getTitle() == i.getTitle()) {
            idea.setStatus(status);
            break;
        }
    }
}
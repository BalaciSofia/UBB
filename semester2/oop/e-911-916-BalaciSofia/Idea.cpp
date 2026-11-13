//
// Created by balac on 6/17/2025.
//
#include <sstream>
#include "Idea.h"
Idea::Idea(std::string title, std::string description, std::string creator,std::string status, int duration):title(title),description(description),status(status),
creator(creator),duration(duration){

}

std::string Idea::getTitle() {
    return title;
}

std::string Idea::getDescription() {
    return description;
}

std::string Idea::getCreator() {
    return creator;
}
std::string Idea::getStatus() {
    return status;
}
int Idea::getDuration() {
    return duration;
}

void Idea::setTitle(std::string title) {
    this->title = title;
}

void Idea::setDescription(std::string description) {
    this->description = description;
}

void Idea::setCreator(std::string creator) {
    this->creator = creator;
}

void Idea::setDuration(int duration) {
    this->duration = duration;
}

void Idea::setStatus(std::string status) {
    this->status = status;
}

std::string Idea::toString() {
    return title + "," + description + "," +creator+"," +status +","+ std::to_string(duration);
}

std::istream &operator>>(std::istream &is, Idea &i) {
    std::string line;
    getline(is, line);
    if(line.empty()) return is;
    std::istringstream iss(line);

    getline(iss, i.title, ',');
    getline(iss, i.description, ',');
    getline(iss, i.status, ',');
    getline(iss, i.creator, ',');
    std::string dur;
    getline(iss, dur, ',');
    int duration = std::stoi(dur);
    i.setDuration(duration);
    return is;
}

std::ostream &operator<<(std::ostream &os, Idea &i) {
    os << i.toString()+',';
    return os;
}
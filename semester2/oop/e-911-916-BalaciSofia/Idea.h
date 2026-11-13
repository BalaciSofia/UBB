//
// Created by balac on 6/17/2025.
//

#ifndef IDEA_H
#define IDEA_H

#include <string>

class Idea {
private:
    std::string title;
    std::string description;
    std::string status;//proposed/accepted
    std::string creator;//researcher
    int duration;//1/2/3
public:
    Idea()=default;
    Idea(std::string title, std::string description, std::string creator,std::string status, int duration);

    //get
    std::string getTitle();
    std::string getDescription();
    std::string getStatus();
    std::string getCreator();
    int getDuration();

    //set
    void setTitle(std::string title);
    void setDescription(std::string description);
    void setStatus(std::string status);
    void setCreator(std::string creator);
    void setDuration(int duration);

    std::string toString();

    friend std::ostream &operator<<(std::ostream &os,Idea &r);
    friend std::istream &operator>>(std::istream &is,Idea &r);
};



#endif //IDEA_H

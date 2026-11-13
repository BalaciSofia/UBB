//
// Created by balac on 6/17/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "Researcher.h"
#include "Idea.h"


class Repository {
private:
    std::string filename1,filename2;
    std::vector<Idea> ideas;
    std::vector<Researcher> researchers;
public:
    Repository(std::string filename1, std::string filename2);
    void load();
    void save(std::string filename);
    std::vector<Idea> getIdeas();
    std::vector<Researcher> getResearchers();
    void addIdea_repo(Idea idea);

    std::vector<Idea> acceptedIdeas();

    void UpdateStatus_repo(Idea i,std::string status);
};



#endif //REPOSITORY_H

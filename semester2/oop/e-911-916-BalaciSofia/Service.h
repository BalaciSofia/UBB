//
// Created by balac on 6/17/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"
#include "Subject.h"


class Service:public Subject{
private:
    Repository &repo;
    public:
    Service(Repository &repo):repo(repo){}

    std::vector<Researcher> getResearchers_service();
    std::vector<Idea> getIdeas_service();

    std::vector<Idea> sortedIdeas();
    void addIdea(std::string title,std::string description,std::string creator,std::string status,int duration);

    void UpdateStatus(Idea i,std::string status);
    void writetofile(std::string filename);
    bool hasaccepted(Researcher r);

};



#endif //SERVICE_H

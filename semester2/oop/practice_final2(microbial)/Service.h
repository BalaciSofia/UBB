//
// Created by balac on 6/16/2025.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "Repository.h"
#include "Subject.h"

class Service: public Subject {
private:
    Repository &repo;
public:
    Service(Repository &repo);
    std::vector<Bacterium> get_bacteriums_service();
    std::vector<Biologist> get_biologists_service();
    std::vector<Bacterium> bacteria_for_biologist(Biologist biologist);
    void addBacterium(std::string name, std::string species,int size,std::vector<std::string> diseases);
};



#endif //SERVICE_H

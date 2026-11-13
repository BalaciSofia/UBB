//
// Created by balac on 6/15/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"
#include "Subject.h"


class Service :public Subject{
private:
    Repository repo;
public:

    Service(Repository repo) : repo(repo) {}
    std::vector<Department> get_departments_service();
    std::vector<Volunteer> get_volunteers_service();

    std::vector<Volunteer> volunteersForDepartment(Department department);
    std::vector<Volunteer> volunteersUnassigned();

    void addVolunteer(std::string name,std::string email, std::string interests);
    void assignVolunteer(Volunteer volunteer, Department dep);
    int numberofvolunteers(Department department);
};



#endif //SERVICE_H

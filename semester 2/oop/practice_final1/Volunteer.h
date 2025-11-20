//
// Created by balac on 6/15/2025.
//

#ifndef VOLUNTEER_H
#define VOLUNTEER_H
#include <string>
#include <vector>

#include "Department.h"


class Volunteer {
private:
    std::string name;
    std::string email;
    std::string interests;
    std::string department;
public:
    Volunteer()=default;
    Volunteer(std::string name, std::string email, std::string interests,std::string department);
    Volunteer(std::string name, std::string email, std::string interests);

    std::string getName();
    std::string getEmail();
    std::string getInterests();
    std::string getDepartment();

    void setName(std::string name);
    void setEmail(std::string email);
    void setInterests(std::string interests);
    void setDepartment(std::string department);

    std::string toString();

    friend std::ostream& operator<<(std::ostream& os, Volunteer& volunteer);
    friend std::istream& operator>>(std::istream& is, Volunteer& volunteer);
};



#endif //VOLUNTEER_H

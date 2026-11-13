//
// Created by balac on 6/15/2025.
//

#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>


class Department {
private:
    std::string name;
    std::string description;
public:
    Department()=default;
    Department(std::string name, std::string description);
    std::string getName();
    std::string getDescription();

    void setName(std::string name);
    void setDescription(std::string description);

    friend std::ostream& operator<<(std::ostream& os, Department& department);
    friend std::istream& operator>>(std::istream& is, Department& department);

    std::string toString();
};



#endif //DEPARTMENT_H

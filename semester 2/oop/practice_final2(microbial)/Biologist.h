//
// Created by balac on 6/15/2025.
//

#ifndef BIOLOGIST_H
#define BIOLOGIST_H

#include <string>
#include <vector>

class Biologist {
private:
    std::string name;
    std::vector<std::string> bacterialSpecies;
public:
    Biologist()=default;
    Biologist(std::string name, std::vector<std::string> bacterialSpecies);

    std::string getName();
    std::vector<std::string> getBacterialSpecies();

    void setName(std::string name);
    void setBacterialSpecies(std::vector<std::string> bacterialSpecies);

    bool operator==(Biologist &other);
    std::string toString();
    ~Biologist()=default;

    friend std::ostream &operator<<(std::ostream &os,Biologist &bio);
    friend std::istream &operator>>(std::istream &is,Biologist &bio);
};



#endif //BIOLOGIST_H

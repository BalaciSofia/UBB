//
// Created by balac on 6/17/2025.
//

#ifndef RESEARCHER_H
#define RESEARCHER_H
#include <string>


class Researcher {
  private:
    std::string name;
    std::string position;//phd student postdoc senior
public:
    Researcher()=default;
    Researcher(std::string name, std::string position);

    //get
    std::string getName();
    std::string getPosition();

    //set
    void setName(std::string name);
    void setPosition(std::string position);

    std::string toString();

    friend std::ostream &operator<<(std::ostream &os,Researcher &r);
    friend std::istream &operator>>(std::istream &is,Researcher &r);

    ~Researcher()=default;

};



#endif //RESEARCHER_H

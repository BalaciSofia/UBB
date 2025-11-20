//
// Created by balac on 6/17/2025.
//

#ifndef ASTRONOMER_H
#define ASTRONOMER_H
#include <string>


class Astronomer {
private:
    std::string name,constellation;
public:
    Astronomer()=default;
    Astronomer(std::string name, std::string constellation);
    std::string get_name();
    std::string get_constellation();

    void set_constellation(std::string constellation);
    void set_name(std::string name);

    std::string to_string();
    bool operator==(Astronomer &other);

    friend std::ostream& operator<<(std::ostream& os,Astronomer& a);
    friend std::istream& operator>>(std::istream& is, Astronomer& a);
};



#endif //ASTRONOMER_H

//
// Created by balac on 6/17/2025.
//

#ifndef STAR_H
#define STAR_H
#include <string>


class Star {
    private:
    std::string name,constellation;
    int ra,dec,diameter;
    public:
    Star()=default;
    Star(std::string name, std::string constellation, int ra, int dec, int diameter);
    std::string get_name();
    std::string get_constellation();
    int get_ra();
    int get_dec();
    int get_diameter();

    void set_name(std::string name);
    void set_constellation(std::string constellation);
    void set_ra(int ra);
    void set_dec(int dec);
    void set_diameter(int diameter);

    std::string to_string();

    friend std::ostream& operator<<(std::ostream& os, Star& star);
    friend std::istream& operator>>(std::istream& is, Star& star);

};



#endif //STAR_H

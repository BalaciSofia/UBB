//
// Created by balac on 6/15/2025.
//

#ifndef BACTERIUM_H
#define BACTERIUM_H

#include <string>
#include <vector>

class Bacterium {
private:
  std::string name;
  std::string species;
  int size;
  std::vector<std::string> diseases;
public:
  Bacterium()=default;
  Bacterium(std::string name, std::string species, int size, std::vector<std::string> diseases);

  std::string getName();
  std::string getSpecies();
  int getSize();
  std::vector<std::string> getDiseases();

  void setName(std::string name);
  void setSpecies(std::string species);
  void setSize(int size);
  void setDiseases(std::vector<std::string> diseases);

  std::string toString();
  bool operator==(Bacterium& other);

  friend std::ostream& operator<<(std::ostream& os, Bacterium& bacterium);
  friend std::istream& operator>>(std::istream& is, Bacterium& bacterium);
};



#endif //BACTERIUM_H

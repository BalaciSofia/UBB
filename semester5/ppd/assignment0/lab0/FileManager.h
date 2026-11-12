#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <vector>


class FileManager {
public:
    std::vector<double> readFile(std::string filename);
    void writeFile(std::string filename, std::vector<double> result);
};



#endif //FILEMANAGER_H

//
// Created by balac on 5/29/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>
#include "Document.h"


class repository {
private:
    std::vector<Document> documents;
    std::string filename;
public:
    repository(std::string filename);
    void load();
    std::vector<Document> get_documents_repo();
    void sortByName();
};



#endif //REPOSITORY_H

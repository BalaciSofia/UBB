//
// Created by balac on 5/29/2025.
//

#include "repository.h"

#include <algorithm>
#include <fstream>
#include <bits/ranges_algo.h>

repository::repository(std::string filename):filename(filename) {
    this->load();
    this->sortByName();
}

std::vector<Document> repository::get_documents_repo() {
    return documents;
}
void repository::load() {
    std::ifstream file(this->filename);
    if (!file.is_open()) return;
    Document doc;
    while (file>>doc) {
        this->documents.push_back(doc);
    }
    file.close();
}

void repository::sortByName() {
    sort(documents.begin(), documents.end(),[](Document &a, Document &b) {
             return a.getName() < b.getName();
         });
}
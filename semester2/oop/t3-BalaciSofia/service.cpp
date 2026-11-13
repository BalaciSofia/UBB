//
// Created by balac on 5/29/2025.
//

#include "service.h"
service::service(repository &repo): repo(repo) {

}

std::vector<Document> service::get_documents_service() {
    return this->repo.get_documents_repo();
}

Document service::best_match(std::string search) {
    double max_score = 0;
    Document best_doc;
    for (auto &doc : this->repo.get_documents_repo()) {
        std::string name = doc.getName();
        int pos = name.find(search);
        if (pos != std::string::npos) {
            double score = double(search.length()) / double(name.length());
            if (score > max_score) {
                max_score = score;
                best_doc = doc;
            }
        }
    }
    return best_doc;
}
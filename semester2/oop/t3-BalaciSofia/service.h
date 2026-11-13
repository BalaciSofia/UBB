//
// Created by balac on 5/29/2025.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"

class service {
private:
  repository &repo;
public:
  service(repository &repo);
  std::vector<Document> get_documents_service();
  Document best_match(std::string search);
};



#endif //SERVICE_H

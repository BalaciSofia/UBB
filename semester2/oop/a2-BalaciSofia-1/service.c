#include "service.h"

#include <stdlib.h>

#include "repo.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

Service createService(DynamicRepo *r) {
  /*
   *creates an instance of a service
   */
  Service service;
  service.repo = r;
  service.undocount = 0;
  service.redocount = 0;
  for (int i = 0; i < 50; i++) {
    service.undo_repo[i] = NULL;
    service.redo_repo[i] = NULL;
  }
  return service;
}

int validate_type(char *type) {
  /*
   *check if type is valid
   *param1:type to be checked
   */
  if (strcmp(type,"house")!=0 && strcmp(type,"apartment")!=0 && strcmp(type,"penthouse")!=0) {
    return 0;
  }
  return 1;
}

void add_estate_services(Service *s,char *type,char *address, int surface, int price) {
  /*
   *creates an estate object and adds it to the repository
   *param1:-
   *param2:type of estate
   *param3:address of estate
   *param4:surface of estate
   *param5:price of estate
   */
  Estate estate;
  strcpy(estate.address, address);
  strcpy(estate.type, type);
  estate.price = price;
  estate.surface = surface;
  append(s->repo,estate);
}

int find_estate(Service *s,char *address) {
  /*
   *checks if an estate exists in the repository
   *param1:-
   *param2:the unique address
   */
  for (int i=0;i<s->repo->length;i++) {
    if (strcmp(s->repo->estates[i]->address, address)==0) {
      return 1;
    }
  }
  return 0;
}

void delete_estate_service(Service *s,char *address) {
  /*
   *deletes an estate from the repository
   *param1:-
   *param2:the unique address it is identified by
   */
  for (int i=0;i<s->repo->length;i++) {
    if (strcmp(s->repo->estates[i]->address, address)==0) {
      remove_index(s->repo,i);
    }
  }
}

void update_type_services(Service *s,char *type,char *address) {
  /*
   *updates an estates type
   *param1:-
   *param2:the new type
   *param3:the unique address it is identified by
   */
  update_type_repo(s->repo,type,address);
}

void update_price_services(Service *s,int price,char *address) {
  /*
   *updates an estates price
   *param1:-
   *param2:the new price
   *param3:the unique address it is identified by
   */
  update_price_repo(s->repo,price,address);
}

void update_surface_services(Service *s,int surface,char *address) {
  /*
   *updates an estates surface
   *param1:-
   *param2:the new surface
   *param3:the unique address it is identified by
   */
  update_surface_repo(s->repo,surface,address);
}

DynamicRepo* copyDynamicRepo_service(Service *s) {
  /*
   *creates a copy of the repository
   */
  DynamicRepo *repo = copyDynamicRepo(s->repo);
  return repo;
}

DynamicRepo* sort_estates_price(DynamicRepo *repo) {
  /*
   *sorts the repository ascending by price
   */
  Estate *aux;
  for (int i=0;i<repo->length;i++) {
    for (int j=i+1;j<repo->length;j++) {
      if (repo->estates[i]->price > repo->estates[j]->price) {
        aux=repo->estates[i];
        repo->estates[i]=repo->estates[j];
        repo->estates[j]=aux;
      }
    }
  }
  return repo;
}

DynamicRepo* search_estates_wstring(DynamicRepo *repo,char *string,char sort) {
  /*
   *searches for the estates that contain the given string(string)
   *param1:the repo
   *param2:the string
   *param3:'a'to sort ascending by price,'d' to sort descending by price
   *returns the found estates sorted acordingly
   */
  DynamicRepo *(*ftpr)(DynamicRepo*);
  ftpr=&sortd_estates_price;
  DynamicRepo *aux = createDynamicRepo();
  for (int i=0;i<repo->length;i++) {
    if (strstr(repo->estates[i]->address,string)!=NULL) {
      append(aux,*(repo->estates[i]));
    }
  }
  if (sort=='a')return sort_estates_price(aux);
  else return ftpr(aux);
}

DynamicRepo* search_estates_wtype(DynamicRepo *repo,char *type,int surface) {
  /*
   *searches estates of a given type with s surface bigger than a give one
   *param1:the repo
   *param2:the type
   *param3:the surface
   *return the found estest sorted ascending by price
   */
  DynamicRepo *aux = createDynamicRepo();
  for (int i=0;i<repo->length;i++) {
    if (strcmp(repo->estates[i]->type,type)==0 && repo->estates[i]->surface >= surface) {
      append(aux,*(repo->estates[i]));
    }
  }
  return sort_estates_price(aux);
}

DynamicRepo* search_estates_wprice(DynamicRepo *repo,int price) {
  /*
   *searches estates that have a smaller price than a given one
   *param1:the repo
   *param2:the price
   *return the estates sorted descending by surface
   */
  DynamicRepo *aux = createDynamicRepo();
  for (int i=0;i<repo->length;i++) {
    if (repo->estates[i]->price <= price) {
      append(aux,*(repo->estates[i]));
    }
  }
  return sortd_estates_surface(aux);
}

DynamicRepo* sortd_estates_surface(DynamicRepo *repo) {
  /*
   *sorts the repository descending by surface
   */
  Estate *aux;
  for (int i=0;i<repo->length;i++) {
    for (int j=i+1;j<repo->length;j++) {
      if (repo->estates[i]->surface < repo->estates[j]->surface) {
        aux=repo->estates[i];
        repo->estates[i]=repo->estates[j];
        repo->estates[j]=aux;
      }
    }
  }
  return repo;
}

DynamicRepo* sortd_estates_price(DynamicRepo *repo) {
  /*
   *sorts the repository descending by price
   */
  Estate *aux;
  for (int i=0;i<repo->length;i++) {
    for (int j=i+1;j<repo->length;j++) {
      if (repo->estates[i]->price < repo->estates[j]->price) {
        aux=repo->estates[i];
        repo->estates[i]=repo->estates[j];
        repo->estates[j]=aux;
      }
    }
  }
  return repo;
}

void destroyService(Service *s) {
  /*
   *deallocates the services memory
   */
  for (int i=0;i<50;i++) {
    if (s->undo_repo[i]!=NULL) {
      destroyDynamicRepo(s->undo_repo[i]);
      s->undo_repo[i] = NULL;
    }
  }
  for (int i=0;i<50;i++) {
    if (s->redo_repo[i]!=NULL) {
      destroyDynamicRepo(s->redo_repo[i]);
      s->redo_repo[i] = NULL;
    }
  }
  destroyDynamicRepo(s->repo);
}

int undo(Service *s) {
  /*
   * Undoes last action
   *
   * returns 1 if undo was successful, 0 otherwise
   */
  if (s->undocount == 0)
    return 0;

  if (s->redocount >= 50) {
    destroyDynamicRepo(s->redo_repo[0]);
    for (int i = 1; i < s->redocount; i++) {
      s->redo_repo[i - 1] = s->redo_repo[i];
    }
    s->redocount--;
  }
  s->redo_repo[s->redocount++] = copyDynamicRepo(s->repo);

  s->undocount--;
  destroyDynamicRepo(s->repo);
  s->repo = copyDynamicRepo(s->undo_repo[s->undocount]);
  destroyDynamicRepo(s->undo_repo[s->undocount]);
  return 1;
}

int redo(Service *s) {
  /*
   *Redoes last action
   *
   *returns 1 if redo was successful, otherwise 0
   */
  if (s->redocount == 0)
    return 0;

  if (s->undocount >= 50) {
    destroyDynamicRepo(s->undo_repo[0]);//free the first element
    for (int i = 1; i < s->undocount; i++) {
      s->undo_repo[i - 1] = s->undo_repo[i];
    }
    s->undocount--;
  }
  s->undo_repo[s->undocount++] = copyDynamicRepo(s->repo);
  destroyDynamicRepo(s->repo);
  s->repo = copyDynamicRepo(s->redo_repo[--s->redocount]);
  return 1;
}

void savecurrent(Service *s) {
  /*
   *saves the current state of the repo
   */
  if (s->undocount >= 50) {
    destroyDynamicRepo(s->undo_repo[0]);
    for (int i = 1; i < s->undocount; i++) {
      s->undo_repo[i - 1] = s->undo_repo[i];
    }
    s->undocount--;
  }
  s->undo_repo[s->undocount] = copyDynamicRepo(s->repo);
  s->undocount++;

  for (int i = 0; i < 50; i++) {
    destroyDynamicRepo(s->redo_repo[i]);
    s->redo_repo[i] = NULL;
  }
  s->redocount = 0;
}

//test-----------------------------------------------------------------------------------------------------

void test_createService() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    assert(service.repo == repo);
    assert(service.undocount == 0);
    assert(service.redocount == 0);

    destroyDynamicRepo(repo);
}

void test_validate_type() {
    assert(validate_type("house") == 1);
    assert(validate_type("apartment") == 1);
    assert(validate_type("penthouse") == 1);
    assert(validate_type("villa") == 0);
}

void test_add_estate_services() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Str Soarelui", 100, 50000);
    assert(service.repo->length == 1);
    assert(strcmp(service.repo->estates[0]->address, "Str Soarelui") == 0);

    destroyDynamicRepo(repo);
}

void test_find_estate() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Str Soarelui", 100, 50000);
    assert(find_estate(&service, "Str Soarelui") == 1);
    assert(find_estate(&service, "Soarelui") == 0);

    destroyDynamicRepo(repo);
}

void test_delete_estate_service() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "apartment", "Str Soarelui", 80, 75000);
    assert(service.repo->length == 1);

    delete_estate_service(&service, "Str Soarelui");
    assert(service.repo->length == 0);

    destroyDynamicRepo(repo);
}

void test_update_services() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Str Soarelui", 120, 100000);

    update_type_services(&service, "penthouse", "Str Soarelui");
    assert(strcmp(service.repo->estates[0]->type, "penthouse") == 0);

    update_price_services(&service, 200000, "Str Soarelui");
    assert(service.repo->estates[0]->price == 200000);

    update_surface_services(&service, 150, "Str Soarelui");
    assert(service.repo->estates[0]->surface == 150);

    destroyDynamicRepo(repo);
}

void test_copyDynamicRepo_service() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "apartment", "Str Soarelui", 90, 85000);

    DynamicRepo *copy = copyDynamicRepo_service(&service);
    assert(copy != NULL);
    assert(copy->length == 1);
    assert(strcmp(copy->estates[0]->address, "Str Soarelui") == 0);

    destroyDynamicRepo(copy);
    destroyDynamicRepo(repo);
}

void test_sort_estates_price() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "A", 100, 300000);
    add_estate_services(&service, "apartment", "B", 100, 150000);
    add_estate_services(&service, "penthouse", "C", 100, 500000);

    DynamicRepo *sorted = sort_estates_price(service.repo);
    assert(sorted->estates[0]->price == 150000);
    assert(sorted->estates[1]->price == 300000);
    assert(sorted->estates[2]->price == 500000);

    destroyDynamicRepo(repo);
}

void test_search_estates_wstring() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Big House", 100, 250000);
    add_estate_services(&service, "apartment", "Small Apartment", 80, 120000);

    DynamicRepo *searchResult = search_estates_wstring(service.repo, "House", 'a');
    assert(searchResult->length == 1);
    assert(strcmp(searchResult->estates[0]->address, "Big House") == 0);

    destroyDynamicRepo(searchResult);
    destroyDynamicRepo(repo);
}

void test_search_estates_wtype() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Str Soarelui", 200, 300000);
    add_estate_services(&service, "apartment", "Str Lunii", 50, 100000);

    DynamicRepo *searchResult = search_estates_wtype(service.repo, "house", 100);
    assert(searchResult->length == 1);
    assert(strcmp(searchResult->estates[0]->type, "house") == 0);

    destroyDynamicRepo(searchResult);
    destroyDynamicRepo(repo);
}

void test_search_estates_wprice() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Cheap House", 150, 100000);
    add_estate_services(&service, "apartment", "Expensive Apartment", 120, 500000);

    DynamicRepo *searchResult = search_estates_wprice(service.repo, 200000);
    assert(searchResult->length == 1);
    assert(strcmp(searchResult->estates[0]->address, "Cheap House") == 0);

    destroyDynamicRepo(searchResult);
    destroyDynamicRepo(repo);
}

void test_undo_redo() {
  DynamicRepo *repo = createDynamicRepo();
  Service service = createService(repo);

  savecurrent(&service);
  add_estate_services(&service, "house", "Str Soarelui", 100, 50000);

  savecurrent(&service);
  add_estate_services(&service, "apartment", "Redo Apt", 80, 120000);

  assert(service.repo->length == 2);
  assert(undo(&service) == 1);
  assert(service.repo->length == 1);
  assert(redo(&service) == 1);
  assert(service.repo->length == 2);
  savecurrent(&service);
  add_estate_services(&service, "penthouse", "New Estate", 100, 300000);
  assert(service.redocount == 0);
  destroyService(&service);
}

void test_destroyService() {
    DynamicRepo *repo = createDynamicRepo();
    Service service = createService(repo);

    add_estate_services(&service, "house", "Destroy Test", 120, 200000);
    destroyService(&service);
}

void run_test_service() {
  test_createService();
  test_validate_type();
  test_add_estate_services();
  test_find_estate();
  test_delete_estate_service();
  test_update_services();
  test_copyDynamicRepo_service();
  test_sort_estates_price();
  test_search_estates_wstring();
  test_search_estates_wtype();
  test_search_estates_wprice();
  test_undo_redo();
  test_destroyService();
}

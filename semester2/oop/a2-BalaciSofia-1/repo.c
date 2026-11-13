#include "repo.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

DynamicRepo* createDynamicRepo(){
  /*
   *creates an instance of a Repository dealing with a dynamic array
   */
  DynamicRepo * repo=malloc(sizeof(DynamicRepo));
  repo->cap=1;
  repo->length=0;
  repo->estates = malloc(sizeof(Estate*));
  return repo;
  }

void double_size(DynamicRepo *repo) {
  /*
   *doubles the maximum size of the dynamic array(repo)
   *param:the repository
   */
  repo->cap *= 2;
  repo->estates=realloc(repo->estates,repo->cap*sizeof(Estate));
}

void shrink(DynamicRepo *repo) {
  /*
   *halves the maximum size of the dynamic array(repo)
   *param:the repository
   */
  repo->cap /= 2;
  repo->estates=realloc(repo->estates,repo->cap*sizeof(Estate*));
}

void append(DynamicRepo *repo, Estate e) {
  /*
   *adds an estate to the repository
   *param1:the repository
   *param2:the estate to be added
   */
  if (repo->length>=repo->cap) double_size(repo);
  Estate *estate_pointer=malloc(sizeof(Estate));
  strcpy(estate_pointer->address,e.address);
  strcpy(estate_pointer->type,e.type);
  estate_pointer->surface=e.surface;
  estate_pointer->price=e.price;
  repo->estates[repo->length]=estate_pointer;
  repo->length++;
}

void remove_index(DynamicRepo *repo, int index) {
  /*
   *removes the estate at the specified index
   *param1:the repository
   *param2:the index
   */
  free(repo->estates[index]);
  for (int i=index; i<repo->length-1; i++)
    repo->estates[i] = repo->estates[i+1];
  repo->length--;
  if (repo->length == repo->cap / 2 && repo->cap != 1) shrink(repo);
}

void destroyDynamicRepo(DynamicRepo *repo) {
  /*
   *deallocates the repository memory
   */
  if (repo == NULL) return;
  if (repo->estates != NULL)
    for (int i=0; i<repo->length; i++)
      if (repo->estates[i] != NULL)
        free(repo->estates[i]);
  if (repo->estates != NULL)
    free(repo->estates);
  free(repo);
}

void update_type_repo(DynamicRepo *repo,char *type,char *address) {
  /*
   *updates an estates type from the repository
   *param1:the repository
   *param2:new type
   *param3:the address of the estate to be updated
   */
  for(int i=0;i<repo->length;i++) {
    if (strcmp(repo->estates[i]->address,address)==0) {
      strcpy(repo->estates[i]->type,type);
    }
  }
}

void update_price_repo(DynamicRepo *repo,int price,char *address) {
  /*
   *updates an estates price from the repository
   *param1:the repository
   *param2:new price
   *param3:the address of the estate to be updated
   */
  for(int i=0;i<repo->length;i++) {
    if (strcmp(repo->estates[i]->address,address)==0) {
      repo->estates[i]->price=price;
    }
  }
}

void update_surface_repo(DynamicRepo *repo,int surface,char *address) {
  /*
   *updates an estates surface from the repository
   *param1:the repository
   *param2:new surface
   *param3:the address of the estate to be updated
   */
  for(int i=0;i<repo->length;i++) {
    if (strcmp(repo->estates[i]->address,address)==0) {
      repo->estates[i]->surface=surface;
    }
  }
}

DynamicRepo* copyDynamicRepo(DynamicRepo *repo) {
  /*
   * Creates a copy of the repository
   */
  DynamicRepo *new_repo = malloc(sizeof(DynamicRepo));
  new_repo->cap = repo->cap;
  new_repo->length = repo->length;
  new_repo->estates = malloc(new_repo->cap * sizeof(Estate*));

  for (int i = 0; i < repo->length; i++) {
    new_repo->estates[i] = copyEstate(repo->estates[i]);
  }
  return new_repo;
}


//tests--------------------------------------------------------------------------------------------------

void test_createDynamicRepo() {
  DynamicRepo *repo = createDynamicRepo();
  assert(repo != NULL);
  assert(repo->cap == 1);
  assert(repo->length == 0);
  assert(repo->estates != NULL);
  destroyDynamicRepo(repo);
}

void test_double_size() {
  DynamicRepo *repo = createDynamicRepo();
  repo->cap = 2;
  double_size(repo);
  assert(repo->cap == 4);
  destroyDynamicRepo(repo);
}

void test_shrink() {
  DynamicRepo *repo = createDynamicRepo();
  repo->cap = 8;
  shrink(repo);
  assert(repo->cap == 4);
  destroyDynamicRepo(repo);
}

void test_append() {
  DynamicRepo *repo = createDynamicRepo();
  Estate e = createEstate("house", "Str Soarelui", 100, 50000);
  append(repo, e);
  assert(repo->length == 1);
  assert(strcmp(repo->estates[0]->address, "Str Soarelui") == 0);
  destroyDynamicRepo(repo);
}

void test_remove_index() {
  DynamicRepo *repo = createDynamicRepo();
  Estate e = createEstate("apartment", "Str Soarelui", 80, 75000);
  append(repo, e);
  assert(repo->length == 1);
  remove_index(repo, 0);
  assert(repo->length == 0);
  destroyDynamicRepo(repo);
}

void test_update_functions() {
  DynamicRepo *repo = createDynamicRepo();
  Estate e = createEstate("house", "Str Soarelui", 120, 100000);
  append(repo, e);
  update_type_repo(repo, "penthouse", "Str Soarelui");
  assert(strcmp(repo->estates[0]->type, "penthouse") == 0);
  update_price_repo(repo, 200000, "Str Soarelui");
  assert(repo->estates[0]->price == 200000);
  update_surface_repo(repo, 150, "Str Soarelui");
  assert(repo->estates[0]->surface == 150);
  destroyDynamicRepo(repo);
}

void test_copyDynamicRepo() {
  DynamicRepo *repo = createDynamicRepo();
  Estate e = createEstate("apartment", "Str Soarelui", 90, 85000);
  append(repo, e);
  DynamicRepo *copy = copyDynamicRepo(repo);
  assert(copy != NULL);
  assert(copy->length == repo->length);
  assert(strcmp(copy->estates[0]->address, "Str Soarelui") == 0);
  destroyDynamicRepo(repo);
  destroyDynamicRepo(copy);
}
void run_test_repo() {
  test_createDynamicRepo();
  test_double_size();
  test_shrink();
  test_append();
  test_remove_index();
  test_update_functions();
  test_copyDynamicRepo();
}

#pragma once
#include "repo.h"

typedef struct{
  DynamicRepo *repo;
  DynamicRepo *undo_repo[50];
  DynamicRepo *redo_repo[50];
  int undocount;
  int redocount;
}Service;

Service createService(DynamicRepo *r);
int validate_type(char *type);
void add_estate_services(Service *s,char *type,char *address, int surface, int price);
int find_estate(Service *s,char *address);
void delete_estate_service(Service *s, char *address);
void update_type_services(Service *s,char *type,char *address);
void update_price_services(Service *s,int price,char *address);
void update_surface_services(Service *s,int surface,char *address);
DynamicRepo* copyDynamicRepo_service(Service *s);
DynamicRepo* search_estates_wstring(DynamicRepo *repo,char *string,char sort);
DynamicRepo* search_estates_wtype(DynamicRepo *repo,char *type,int surface);
DynamicRepo* search_estates_wprice(DynamicRepo *repo,int price);
DynamicRepo* sortd_estates_surface(DynamicRepo *repo);
DynamicRepo* sortd_estates_price(DynamicRepo *repo);
DynamicRepo* sort_estates_price(DynamicRepo *repo);
void destroyService(Service *s);
void savecurrent(Service *s);
int undo(Service *s);
int redo(Service *s);
void run_test_service();
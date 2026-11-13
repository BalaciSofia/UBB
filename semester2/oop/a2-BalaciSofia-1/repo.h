#pragma once
#include "domain.h"

typedef struct{
  int cap;
  int length;
  Estate  ** estates;
  }DynamicRepo;

DynamicRepo* createDynamicRepo();
void double_size(DynamicRepo *repo);
void shrink(DynamicRepo *repo);
void append(DynamicRepo *repo,Estate estate);
void remove_index(DynamicRepo *repo,int index);
void destroyDynamicRepo(DynamicRepo *repo);
void update_type_repo(DynamicRepo *repo,char *type,char *address);
void update_price_repo(DynamicRepo *repo,int price,char *address);
void update_surface_repo(DynamicRepo *repo,int surface,char *address);
DynamicRepo* copyDynamicRepo(DynamicRepo *repo);
void run_test_repo();


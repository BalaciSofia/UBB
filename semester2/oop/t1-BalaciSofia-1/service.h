#pragma once
#include "repo.h"

class Service {
private:
    Repository &repo;
    public:
    Service(Repository &repo) : repo(repo) {}

    void addSchool_serv(std::string name,std::string address,int day,int month,int year);
    bool searchSchool(School s);
    DynamicArray<School>& getSchools_serv();
    void initialize();
    DynamicArray<School> sort_by_name();

    void Test_addSchool_serv();
    //void test_sorting_by_name();
};

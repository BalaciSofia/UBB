#pragma once
#include "domain.h"
#include "dynamicarray.h"
class Repository {
private:
    DynamicArray<School> schools;
    public:
    Repository()=default;
    ~Repository()=default;

    void addSchool(School school);
    DynamicArray<School>& getSchools();
};
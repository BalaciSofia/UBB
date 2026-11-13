
#include "repo.h"

void Repository::addSchool(School school) {
    this->schools.append(school);
}

DynamicArray<School>& Repository:: getSchools() {
    return this->schools;
}

#include "service.h"
#include "domain.h"
#include <cassert>
void Service::addSchool_serv(std::string name,std::string address,int day,int month,int year) {
    /*
     *adds a school to the repository
     *param name: the name of the school
     *parm address: the address of the school
     *parm day month and year form the address when the school will be visited
     */
    School s=School(name,address,day,month,year);
    if ( searchSchool(s) )
        throw std::logic_error("School already exists");
    this->repo.addSchool(s);
}
bool Service::searchSchool(School s) {
    for (int i=0;i<this->repo.getSchools().getSize();i++) {
        if (this->repo.getSchools()[i].getName()==s.getName() &&  this->repo.getSchools()[i].getAddress()==s.getAddress()) {
            return true;
        }
    }
    return false;
}
DynamicArray<School>& Service:: getSchools_serv() {
    return this->repo.getSchools();
}

void Service:: initialize() {
    this->addSchool_serv("Avram_Iancu","46.77,23,60",15,04,2022);
    this->addSchool_serv("George_Cosbuc","46.77,23.58",18,4,2022);
    this->addSchool_serv("Alexandru_Vaida","46.77,23.63",23,4,2022);
    this->addSchool_serv("Romulus_Guga","46.53,24.57",4,5,2022);
    this->addSchool_serv("Colegiul_Transilvania","46.54,24.57",3,5,2022);
}

void Service::Test_addSchool_serv() {
    Repository repo;
    Service s(repo);
    s.addSchool_serv("name","address",1,2,3);
    assert(s.getSchools_serv().getSize()==1);
    assert(s.getSchools_serv()[0].getName()=="name");
    assert(s.getSchools_serv()[0].getAddress()=="address");
    assert(s.getSchools_serv()[0].getDay()==1);
    assert(s.getSchools_serv()[0].getMonth()==2);
    assert(s.getSchools_serv()[0].getYear()==3);
}

DynamicArray<School> Service::sort_by_name() {
    /*
     *sorts the schools in the repository by name
     *returns the new sorted array
     */
    School aux;
    DynamicArray<School> sorted_schools=this->repo.getSchools();
    for (int i=0;i<sorted_schools.getSize()-1;i++) {
        for (int j=i+1;j<sorted_schools.getSize();j++) {
            if (sorted_schools[j].getName()<sorted_schools[i].getName()) {
                aux=sorted_schools[i];
                sorted_schools[i]=sorted_schools[j];
                sorted_schools[j]=aux;
            }
        }
    }
    return sorted_schools;
}

// void Service::test_sorting_by_name() {
//     Repository repo;
//     Service s(repo);
//     s.addSchool_serv("name","address",1,2,3);
//     s.addSchool_serv("naame","address",1,2,3);
//     DynamicArray<School> s=this->sort_by_name();
// }
#include<iostream>
#include "BMI.h"
#include "BP.h"
#include "MedicalAnalysis.h"
#include <string>
#include<fstream>

#include "Person.h"
#include "Service.h"
#include "UI.h"
using namespace std;
int main() {
    Person person("David");
    Service service(person);
    UI ui(service);
    ui.run();
}
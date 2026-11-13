//
// Created by balac on 5/8/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <vector>

#include "Car.h"


class Service {
private:
    std::vector<Car> cars;
    public:
    Service()=default;
    double addCar(std::string bodyStyle,std::string engineType,int autonomy);
    std::vector<Car> getCarsWithMaxPrice(double maxprice);
    std::vector<Car> getCars();
    void writeToFile(std::string filename);
};



#endif //SERVICE_H

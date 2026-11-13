//
// Created by balac on 5/8/2025.
//

#include "Service.h"

#include "ElectricEngine.h"
#include "TurboEngine.h"

double Service::addCar(std::string bodyStyle,std::string engineType,int autonomy) {
    if(autonomy==-1) {
        //turbo
        TurboEngine * engine=new TurboEngine();
        Car car(bodyStyle,engine);
        double price=car.computePrice();
        this->cars.push_back(car);
        return price;
    }
    else {
        //electric
        ElectricEngine *engine=new ElectricEngine(autonomy);
        Car car(bodyStyle,engine);
        double price=car.computePrice();
        this->cars.push_back(car);
        return price;
    }
}

std::vector<Car> Service::getCars() {
    return this->cars;
}

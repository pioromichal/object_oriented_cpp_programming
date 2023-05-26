#include "../include/pharmacy.h"
Pharmacy::Pharmacy(int nCounters, int nOpenedCounters): counters(nCounters,nOpenedCounters) {

}

void Pharmacy::addRandomMedicine(std::string name) {
    //TODO randomNumber generate, from 1 to 6
    int randomNumber = 1;
    switch (randomNumber) {
        case 1:
            //Capsules
            break;
        case 2:
            //Drops
            break;
        case 3:
            //Ointment
            break;
        case 4:
            //Powders
            break;
        case 5:
            //Syrup
            break;
        case 6:
            //Tablets
            break;
        //TODO throw some fance exception
//        default:
//            throw
    }



}

void Pharmacy::pushNewClient(std::string firstName, std::string lastName) {

}

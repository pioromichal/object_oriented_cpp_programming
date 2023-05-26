#include <random>
#include <chrono>
#include <memory>
#include <stdexcept>
#include "../include/pharmacy.h"
Pharmacy::Pharmacy(int nCounters, int nOpenedCounters): counters(nCounters,nOpenedCounters) {

}

void Pharmacy::addRandomMedicine(std::string& name) {
    //TODO randomNumber generate, from 1 to 6
    std::default_random_engine generator (std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1,6);
    int randomMedicine = distribution(generator);
    std::shared_ptr<Medicine> drug;
    switch (randomMedicine) {
        case 1:
            //Capsules
            drug = std::make_shared<Capsules>(name,randomAffliction(),randomActiveSubstance(),randomMiligrams(),randomPrice(),randomAmount(),randomNumber());
            break;
        case 2:
            //Drops
            drug = std::make_shared<Drops>(name,randomAffliction(),randomActiveSubstance(),randomMiligrams(),randomPrice(),randomAmount(),randomVolume());
            break;
        case 3:
            //Ointment
            drug = std::make_shared<Ointment>(name,randomAffliction(),randomActiveSubstance(),randomMiligrams(),randomPrice(),randomAmount(),randomVolume());
            break;
        case 4:
            //Powders
            drug = std::make_shared<Powders>(name,randomAffliction(),randomActiveSubstance(),randomMiligrams(),randomPrice(),randomAmount(),randomSachets());
            break;
        case 5:
            //Syrup
            drug = std::make_shared<Syrup>(name,randomAffliction(),randomActiveSubstance(),randomMiligrams(),randomPrice(),randomAmount(),randomVolume());
            break;
        case 6:
            //Tablets
            drug = std::make_shared<Tablets>(name,randomAffliction(),randomActiveSubstance(),randomMiligrams(),randomPrice(),randomAmount(),randomNumber());
            break;
        //TODO throw some fancy exception
        default:
            drug = nullptr;
            throw std::invalid_argument("Something went wrong here");

    }
    inventory.addNewMedicine(drug);


}

void Pharmacy::pushNewClient(std::string& firstName, std::string& lastName) {
    std::default_random_engine generator (std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1,10);
    //TODO it is terribly implemented
    bool randomClient =  distribution(generator)>=4;
    if(randomClient){
        queue.pushIndividualClient(firstName,lastName, randomShoppingList(), randomArguability());
    }
    else{
        queue.pushBusinessClient(firstName, lastName, randomShoppingList(), randomArguability());
    }
}

Affliction Pharmacy::randomAffliction() {
    return Affliction::Hangover;
}

ActiveSubstance Pharmacy::randomActiveSubstance() {
    return ActiveSubstance::Atorvastatin;
}

unsigned Pharmacy::randomMiligrams() {
    return 0;
}

Price Pharmacy::randomPrice() {
    return Price();
}

unsigned Pharmacy::randomAmount() {
    return 0;
}

unsigned Pharmacy::randomNumber() {
    return 0;
}

unsigned Pharmacy::randomVolume() {
    return 0;
}

unsigned Pharmacy::randomSachets() {
    return 0;
}


float Pharmacy::randomArguability() {
    return 0;
}

ShoppingList Pharmacy::randomShoppingList() {
    return ShoppingList();
}

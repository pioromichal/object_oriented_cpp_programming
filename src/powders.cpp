#include "../include/powders.h"

#include <sstream>

Powders::Powders(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned numberOfSachets) :
	Medicine(name, afflication, activeSubstance, miligramsOfActiveSubstance, basePrice, amountInPharmacy), numberOfSachets(numberOfSachets) {
    checkIsOnPrescription();
}

void Powders::setNumberOfSachets(const unsigned newNumber) {
    numberOfSachets = newNumber;
}

unsigned Powders::getNumberOfSachets() const {
	return numberOfSachets;
}

const std::string Powders::representAsString() const {
    std::stringstream ss;
    ss << "Powders: " << name << " (" << id << ")" << std::endl;
    ss << "Prescription: ";
    if (prescription) ss << "yes" << std::endl;
    else ss << "no" << std::endl;
    ss << "Treated affliction: " << afflictionToString(affliction) << std::endl;
    ss << "Number of sachets: " << numberOfSachets << std::endl;
    ss << "One sachet contains " << miligramsOfActiveSubstance << " mg of " << activeSubstanceToString(activeSubstance) << std::endl;
    ss << "Prise: " << calculatePrice() << std::endl;
    return ss.str();
}

Price Powders::calculatePrice() const {
	return basePrice * (100 + provision) / 100;
}

bool Powders::checkIsOnPrescription() {
    switch (activeSubstance) {
    case ActiveSubstance::Paracetamol:
        return miligramsOfActiveSubstance > 1700;
        break;
    case ActiveSubstance::Ibuprofen:
        return miligramsOfActiveSubstance > 1500;
        break;
    case ActiveSubstance::Aspirin:
        return miligramsOfActiveSubstance > 900;
        break;
    case ActiveSubstance::Metamizole:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Amoxicillin:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Acenocoumarol:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Metformin:
        return miligramsOfActiveSubstance > 200;
        break;
    case ActiveSubstance::Atorvastatin:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Omeprazole:
        return miligramsOfActiveSubstance > 350;
        break;
    case ActiveSubstance::Sertraline:
        return miligramsOfActiveSubstance > 200;
        break;
    default:
        return false;
        break;
    }
}
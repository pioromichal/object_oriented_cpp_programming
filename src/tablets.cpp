#include "../include/tablets.h"

#include <sstream>

Tablets::Tablets(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned number) :
	Medicine(name, afflication, activeSubstance, miligramsOfActiveSubstance, basePrice, amountInPharmacy), number(number) {
    checkIsOnPrescription();
}

void Tablets::setNumber(const unsigned newNumber) {
	number = newNumber;
}

unsigned Tablets::getNumber() const {
	return number;
}

const std::string Tablets::representAsString() const {
    std::stringstream ss;
    ss << "Tablets: " << name << " (" << id << ")" << std::endl;
    ss << "Prescription: ";
    if (prescription) ss << "yes" << std::endl;
    else ss << "no" << std::endl;
    ss << "Treated affliction: " << afflictionToString(affliction) << std::endl;
    ss << "Number of tablets: " << number << std::endl;
    ss << "One tablet contains " << miligramsOfActiveSubstance << " mg of " << activeSubstanceToString(activeSubstance) << std::endl;
    ss << "Prise: " << calculatePrice() << std::endl;
    return ss.str();
}

Price Tablets::calculatePrice() const {
	return basePrice * (100 + provision)/100;
}

bool Tablets::checkIsOnPrescription() {
    switch (activeSubstance) {
    case ActiveSubstance::Paracetamol:
        return miligramsOfActiveSubstance > 1500;
        break;
    case ActiveSubstance::Ibuprofen:
        return miligramsOfActiveSubstance > 1200;
        break;
    case ActiveSubstance::Aspirin:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Metamizole:
        return miligramsOfActiveSubstance > 325;
        break;
    case ActiveSubstance::Amoxicillin:
        return miligramsOfActiveSubstance > 250;
        break;
    case ActiveSubstance::Acenocoumarol:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Metformin:
        return miligramsOfActiveSubstance > 700;
        break;
    case ActiveSubstance::Atorvastatin:
        return miligramsOfActiveSubstance > 560;
        break;
    case ActiveSubstance::Omeprazole:
        return miligramsOfActiveSubstance > 230;
        break;
    case ActiveSubstance::Sertraline:
        return miligramsOfActiveSubstance > 100;
        break;
    default:
        return false;
        break;
    }
}

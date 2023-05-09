#include "../include/capsules.h"

#include <sstream>

Capsules::Capsules(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned number) :
	Medicine(name, afflication, activeSubstance, miligramsOfActiveSubstance, basePrice, amountInPharmacy), number(number) {
    checkIsOnPrescription();
}

void Capsules::setNumber(const unsigned newNumber) {
	number = newNumber;
}

unsigned Capsules::getNumber() const {
	return number;
}

const std::string Capsules::representAsString() const {
    std::stringstream ss;
    ss << "Capsules: " << name << " (" << id << ")" << std::endl;
    ss << "Prescription: ";
    if (prescription) ss << "yes" << std::endl;
    else ss << "no" << std::endl;
    ss << "Treated affliction: " << afflictionToString(affliction) << std::endl;
    ss << "Number of capsules: " << number << std::endl;
    ss << "One capsule contains " << miligramsOfActiveSubstance << " mg of " << activeSubstanceToString(activeSubstance) << std::endl;
    ss << "Prise: " << calculatePrice() << std::endl;
    return ss.str();
}

Price Capsules::calculatePrice() const {
	return basePrice * (100 + provision) / 100;
}

bool Capsules::checkIsOnPrescription() {
    switch (activeSubstance) {
    case ActiveSubstance::Paracetamol:
        return miligramsOfActiveSubstance > 1500;
        break;
    case ActiveSubstance::Ibuprofen:
        return miligramsOfActiveSubstance > 1000;
        break;
    case ActiveSubstance::Aspirin:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Metamizole:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Amoxicillin:
        return miligramsOfActiveSubstance > 50;
        break;
    case ActiveSubstance::Acenocoumarol:
        return miligramsOfActiveSubstance > 300;
        break;
    case ActiveSubstance::Metformin:
        return miligramsOfActiveSubstance > 450;
        break;
    case ActiveSubstance::Atorvastatin:
        return miligramsOfActiveSubstance > 800;
        break;
    case ActiveSubstance::Omeprazole:
        return miligramsOfActiveSubstance > 20;
        break;
    case ActiveSubstance::Sertraline:
        return miligramsOfActiveSubstance > 540;
        break;
    default:
        return false;
        break;
    }
}
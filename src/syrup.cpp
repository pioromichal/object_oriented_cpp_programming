#include "../include/syrup.h"

#include <sstream>

Syrup::Syrup(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned volumeInMilliliters) :
	Medicine(name, afflication, activeSubstance, miligramsOfActiveSubstance, basePrice, amountInPharmacy), volumeInMilliliters(volumeInMilliliters) {
    checkIsOnPrescription();
}

void Syrup::setVolumeInMilliliters(const unsigned newVolume) {
	volumeInMilliliters = newVolume;
}

unsigned Syrup::getVolumeInMilliliters() const {
	return volumeInMilliliters;
}

const std::string Syrup::representAsString() const {
    std::stringstream ss;
    ss << "Syrup: " << name << " (" << id << ")" << std::endl;
    ss << "Prescription: ";
    if (prescription) ss << "yes" << std::endl;
    else ss << "no" << std::endl;
    ss << "Treated affliction: " << afflictionToString(affliction) << std::endl;
    ss << "Volume: " << volumeInMilliliters << " ml" << std::endl;
    ss << "One dose contains " << miligramsOfActiveSubstance << " mg of " << activeSubstanceToString(activeSubstance) << std::endl;
    ss << "Prise: " << calculatePrice() << std::endl;
    return ss.str();
}

Price Syrup::calculatePrice() const {
	return basePrice * (100 + provision) / 100;
}

bool Syrup::checkIsOnPrescription() {
    switch (activeSubstance) {
    case ActiveSubstance::Paracetamol:
        return miligramsOfActiveSubstance > 1000;
        break;
    case ActiveSubstance::Ibuprofen:
        return miligramsOfActiveSubstance > 1300;
        break;
    case ActiveSubstance::Aspirin:
        return miligramsOfActiveSubstance > 800;
        break;
    case ActiveSubstance::Metamizole:
        return miligramsOfActiveSubstance > 325;
        break;
    case ActiveSubstance::Amoxicillin:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Acenocoumarol:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Metformin:
        return miligramsOfActiveSubstance > 500;
        break;
    case ActiveSubstance::Atorvastatin:
        return miligramsOfActiveSubstance > 300;
        break;
    case ActiveSubstance::Omeprazole:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Sertraline:
        return miligramsOfActiveSubstance > 300;
        break;
    default:
        return false;
        break;
    }
}
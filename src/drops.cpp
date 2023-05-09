#include "../include/drops.h"

#include <sstream>

Drops::Drops(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned volumeInMilliliters) :
	Medicine(name, afflication, activeSubstance, miligramsOfActiveSubstance, basePrice, amountInPharmacy), volumeInMilliliters(volumeInMilliliters) {
    checkIsOnPrescription();
}

void Drops::setVolumeInMilliliters(const unsigned newVolume) {
	volumeInMilliliters = newVolume;
}

unsigned Drops::getVolumeInMilliliters() const {
	return volumeInMilliliters;
}

const std::string Drops::representAsString() const {
    std::stringstream ss;
    ss << "Drops: " << name << " (" << id << ")" << std::endl;
    ss << "Prescription: ";
    if (prescription) ss << "yes" << std::endl;
    else ss << "no" << std::endl;
    ss << "Treated affliction: " << afflictionToString(affliction) << std::endl;
    ss << "Volume: " << volumeInMilliliters << " ml" << std::endl;
    ss << "One dose contains " << miligramsOfActiveSubstance << " mg of " << activeSubstanceToString(activeSubstance) << std::endl;
    ss << "Prise: " << calculatePrice() << std::endl;
    return ss.str();
}

Price Drops::calculatePrice() const {
	return basePrice * (100 + provision) / 100;
}

bool Drops::checkIsOnPrescription() {
    switch (activeSubstance) {
    case ActiveSubstance::Paracetamol:
        return miligramsOfActiveSubstance > 300;
        break;
    case ActiveSubstance::Ibuprofen:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Aspirin:
        return miligramsOfActiveSubstance > 300;
        break;
    case ActiveSubstance::Metamizole:
        return miligramsOfActiveSubstance > 200;
        break;
    case ActiveSubstance::Amoxicillin:
        return miligramsOfActiveSubstance > 300;
        break;
    case ActiveSubstance::Acenocoumarol:
        return miligramsOfActiveSubstance > 250;
        break;
    case ActiveSubstance::Metformin:
        return miligramsOfActiveSubstance > 60;
        break;
    case ActiveSubstance::Atorvastatin:
        return miligramsOfActiveSubstance > 50;
        break;
    case ActiveSubstance::Omeprazole:
        return miligramsOfActiveSubstance > 80;
        break;
    case ActiveSubstance::Sertraline:
        return miligramsOfActiveSubstance > 100;
        break;
    default:
        return false;
        break;
    }
}
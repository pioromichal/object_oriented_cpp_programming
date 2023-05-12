#include "../include/ointment.h"

#include <sstream>

Ointment::Ointment(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned volumeInMilliliters) :
	Medicine(name, afflication, activeSubstance, miligramsOfActiveSubstance, basePrice, amountInPharmacy), volumeInMilliliters(volumeInMilliliters) {
    checkIsOnPrescription();
}

void Ointment::setVolumeInMilliliters(const unsigned newVolume) {
	volumeInMilliliters = newVolume;
}

unsigned Ointment::getVolumeInMilliliters() const {
	return volumeInMilliliters;
}

const std::string Ointment::representAsString() const {
    std::stringstream ss;
    ss << "Ointment: " << name << " (" << id << ")" << std::endl;
    ss << "Prescription: ";
    if (prescription) ss << "yes" << std::endl;
    else ss << "no" << std::endl;
    ss << "Treated affliction: " << afflictionToString(affliction) << std::endl;
    ss << "Volume: " << volumeInMilliliters << " ml" << std::endl;
    ss << "One dose contains " << miligramsOfActiveSubstance << " mg of " << activeSubstanceToString(activeSubstance) << std::endl;
    ss << "Prise: " << calculatePrice() << std::endl;
    return ss.str();
}

Price Ointment::calculatePrice() const {
	return basePrice * (100 + provision) / 100;
}

bool Ointment::checkIsOnPrescription() {
    switch (activeSubstance) {
    case ActiveSubstance::Paracetamol:
        return miligramsOfActiveSubstance > 1800;
        break;
    case ActiveSubstance::Ibuprofen:
        return miligramsOfActiveSubstance > 1600;
        break;
    case ActiveSubstance::Aspirin:
        return miligramsOfActiveSubstance > 1000;
        break;
    case ActiveSubstance::Metamizole:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Amoxicillin:
        return miligramsOfActiveSubstance > 750;
        break;
    case ActiveSubstance::Acenocoumarol:
        return miligramsOfActiveSubstance > 800;
        break;
    case ActiveSubstance::Metformin:
        return miligramsOfActiveSubstance > 400;
        break;
    case ActiveSubstance::Atorvastatin:
        return miligramsOfActiveSubstance > 700;
        break;
    case ActiveSubstance::Omeprazole:
        return miligramsOfActiveSubstance > 600;
        break;
    case ActiveSubstance::Sertraline:
        return miligramsOfActiveSubstance > 20;
        break;
    default:
        return false;
        break;
    }
}
#include "../include/medicine.h"

#include <sstream>

Medicine::Medicine(const std::string& name, Affliction affliction, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy) :
	name(name), id(medId++), affliction(affliction), activeSubstance(activeSubstance), miligramsOfActiveSubstance(miligramsOfActiveSubstance), basePrice(basePrice), amountInPharmacy(amountInPharmacy), prescription(false) {
}

void Medicine::setName(const std::string newName) {
	name = newName;
}

void Medicine::setAfflication(const Affliction newAffliction) {
	affliction = newAffliction;
}

void Medicine::setActiveSubstance(const ActiveSubstance newActiveSubstance) {
	activeSubstance = newActiveSubstance;
}

void Medicine::setMiligramsOfActiveSubstance(const unsigned newAmountOfSubstance) {
	miligramsOfActiveSubstance = newAmountOfSubstance;
}

void Medicine::setBasePrice(const Price& newBasePrice) {
	basePrice = newBasePrice;
}

void Medicine::setAmountInPharmacy(const unsigned newAmountInPharmacy) {
	amountInPharmacy = newAmountInPharmacy;
}

const std::string Medicine::getName() const {
	return name;
}

int Medicine::getId() const {
	return id;
}

Affliction Medicine::getAfflication() const {
	return affliction;
}

ActiveSubstance Medicine::getActiveSubstance() const {
	return activeSubstance;
}

unsigned Medicine::getMiligramsOfActiveSubstance() const {
	return miligramsOfActiveSubstance;
}

const Price& Medicine::getBasePrice() const {
	return basePrice;
}

unsigned Medicine::getAmountInPharmacy() const {
	return amountInPharmacy;
}

Medicine& Medicine::operator--() {
	amountInPharmacy--;
	return *this;
}

Medicine::~Medicine() {}

std::ostream& operator<<(std::ostream& os, const Medicine& medicine) {
	os << medicine.representAsString();
	return os;
}

void Medicine::resetMedId() {
    medId = 1;
}

std::string Medicine::activeSubstanceToString(ActiveSubstance substance) const {
    switch (substance) {
    case ActiveSubstance::Paracetamol:
        return "Paracetamol";
    case ActiveSubstance::Ibuprofen:
        return "Ibuprofen";
    case ActiveSubstance::Aspirin:
        return "Aspirin";
    case ActiveSubstance::Metamizole:
        return "Metamizole";
    case ActiveSubstance::Amoxicillin:
        return "Amoxicillin";
    case ActiveSubstance::Acenocoumarol:
        return "Acenocoumarol";
    case ActiveSubstance::Metformin:
        return "Metformin";
    case ActiveSubstance::Atorvastatin:
        return "Atorvastatin";
    case ActiveSubstance::Omeprazole:
        return "Omeprazole";
    case ActiveSubstance::Sertraline:
        return "Sertraline";
    default:
        return "";
    }
}

std::string Medicine::afflictionToString(Affliction affliction) const {
    switch (affliction) {
    case Affliction::Ache: return "Ache";
    case Affliction::Allergy: return "Allergy";
    case Affliction::Attack: return "Attack";
    case Affliction::Backache: return "Backache";
    case Affliction::Bellyache: return "Bellyache";
    case Affliction::Bite: return "Bite";
    case Affliction::Bleeding: return "Bleeding";
    case Affliction::Bruise: return "Bruise";
    case Affliction::Bump: return "Bump";
    case Affliction::Burn: return "Burn";
    case Affliction::Chills: return "Chills";
    case Affliction::Cold: return "Cold";
    case Affliction::Concussion: return "Concussion";
    case Affliction::Cough: return "Cough";
    case Affliction::Cut: return "Cut";
    case Affliction::Diarrhoea: return "Diarrhoea";
    case Affliction::Dislocation: return "Dislocation";
    case Affliction::Fatigue: return "Fatigue";
    case Affliction::Food: return "Food Poisoning";
    case Affliction::Poisoning: return "Poisoning";
    case Affliction::Fracture: return "Fracture";
    case Affliction::Hangover: return "Hangover";
    case Affliction::Headache: return "Headache";
    case Affliction::Indigestion: return "Indigestion";
    case Affliction::Infection: return "Infection";
    case Affliction::Nausea: return "Nausea";
    case Affliction::Pain: return "Pain";
    case Affliction::Rash: return "Rash";
    case Affliction::RunnyNose: return "Runny Nose";
    case Affliction::SoreThroat: return "Sore Throat";
    case Affliction::Toothache: return "Toothache";
    case Affliction::Wound: return "Wound";
    default: return "";
    }
}

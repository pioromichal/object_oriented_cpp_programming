#ifndef POWDERS_H
#define POWDERS_H

#include "medicine.h"

class Powders : public Medicine
{
private:
	static const unsigned provision = 14;
	unsigned numberOfSachets;
public:
	Powders(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned numberOfSachets);
	void setNumberOfSachets(const unsigned newNumber);
	unsigned getNumberOfSachets() const;
	const std::string representAsString() const override;
	Price calculatePrice() const override;
	bool checkIsOnPrescription() override;
};
#endif
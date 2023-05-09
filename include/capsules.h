#ifndef CAPSULES_H
#define CAPSULES_H

#include "medicine.h"

class Capsules : public Medicine
{
private:
	static const unsigned provision = 5;
	unsigned number;
public:
	Capsules(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned number);
	void setNumber(const unsigned newNumber);
	unsigned getNumber() const;
	const std::string representAsString() const override;
	Price calculatePrice() const override;
	bool checkIsOnPrescription() override;
};
#endif
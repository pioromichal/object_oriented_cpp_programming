#ifndef TABLETS_H
#define TABLETS_H

#include "medicine.h"

class Tablets : public Medicine {
private:
	static const unsigned provision = 3;
	unsigned number;
public:
	Tablets(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned number);
	void setNumber(const unsigned newNumber);
	unsigned getNumber() const;
	const std::string representAsString() const override;
	Price calculatePrice() const override;
	bool checkIsOnPrescription() override;
};
#endif
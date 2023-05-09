#ifndef SYRUP_H
#define SYRUP_H

#include "medicine.h"

class Syrup : public Medicine
{
private:
	static const unsigned provision = 7;
	unsigned volumeInMilliliters;
public:
	Syrup(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned volumeInMilliliters);
	void setVolumeInMilliliters(const unsigned newVolume);
	unsigned getVolumeInMilliliters() const;
	const std::string representAsString() const override;
	Price calculatePrice() const override;
	bool checkIsOnPrescription() override;
};
#endif
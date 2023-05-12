#ifndef DROPS_H
#define DROPS_H

#include "medicine.h"

class Drops : public Medicine
{
private:
	static const unsigned provision = 10;
	unsigned volumeInMilliliters;
public:
	Drops(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned volumeInMilliliters);
	void setVolumeInMilliliters(const unsigned newVolume);
	unsigned getVolumeInMilliliters() const;
	const std::string representAsString() const override;
	Price calculatePrice() const override;
	bool checkIsOnPrescription() override;
};
#endif
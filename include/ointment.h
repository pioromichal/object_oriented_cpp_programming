#ifndef OINTMENT_H
#define OINTMENT_H

#include "medicine.h"

class Ointment : public Medicine
{
private:
	static const unsigned provision = 8;
	unsigned volumeInMilliliters;
public:
	Ointment(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy, unsigned volumeInMilliliters);
	void setVolumeInMilliliters(const unsigned newVolume);
	unsigned getVolumeInMilliliters() const;
	const std::string representAsString() const override;
	Price calculatePrice() const override;
	bool checkIsOnPrescription() override;
};
#endif
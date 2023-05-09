#ifndef PROI_23L_101_APTEKA_MEDICINE_H
#define PROI_23L_101_APTEKA_MEDICINE_H

#include <string>

#include "price.h"

enum class Affliction {
    Ache,
    Allergy,
    Attack,
    Backache,
    Bellyache,
    Bite,
    Bleeding,
    Bruise,
    Bump,
    Burn,
    Chills,
    Cold,
    Concussion,
    Cough,
    Cut,
    Diarrhoea,
    Dislocation,
    Fatigue,
    Food,
    Poisoning,
    Fracture,
    Hangover,
    Headache,
    Indigestion,
    Infection,
    Nausea,
    Pain,
    Rash,
    RunnyNose,
    SoreThroat,
    Toothache,
    Wound,
	Count
};

enum class ActiveSubstance {
    Paracetamol,
    Ibuprofen,
    Aspirin,
    Metamizole,
    Amoxicillin,
    Acenocoumarol,
    Metformin,
    Atorvastatin,
    Omeprazole,
    Sertraline,
    Count
};

class Medicine {
private:
    inline static unsigned medId=1;
protected:
    std::string name;
    unsigned id;
    Affliction affliction;
    ActiveSubstance activeSubstance;
    unsigned miligramsOfActiveSubstance;
    Price basePrice;
    unsigned amountInPharmacy;
    bool prescription;
    std::string activeSubstanceToString(ActiveSubstance substance) const;
    std::string afflictionToString(Affliction affliction) const;
public:
    Medicine(const std::string& name, Affliction afflication, ActiveSubstance activeSubstance, unsigned miligramsOfActiveSubstance, Price basePrice, unsigned amountInPharmacy);

    void setName(const std::string newName);
    void setAfflication(const Affliction newAffliction);
    void setActiveSubstance(const ActiveSubstance newActiveSubstance);
    void setMiligramsOfActiveSubstance(const unsigned newAmountOfSubstance);
    void setBasePrice(const Price& newBasePrice);
    void setAmountInPharmacy(const unsigned newAmountInPharmacy);

    const std::string getName() const;
    int getId() const;
    Affliction getAfflication() const;
    ActiveSubstance getActiveSubstance() const;
    unsigned getMiligramsOfActiveSubstance() const;
    const Price& getBasePrice() const;
    unsigned getAmountInPharmacy() const;

    Medicine& operator--();

    virtual ~Medicine();

    virtual const std::string representAsString() const = 0;
    virtual Price calculatePrice() const = 0;
    virtual bool checkIsOnPrescription() = 0;

    static void resetMedId();

    friend std::ostream& operator<<(std::ostream& os, const Medicine& medicine);
};

std::ostream& operator<<(std::ostream& os, const Medicine& medicine);

#endif //PROI_23L_101_APTEKA_MEDICINE_H

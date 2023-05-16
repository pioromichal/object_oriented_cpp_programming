#ifndef PROI_23L_101_APTEKA_INVENTORY_H
#define PROI_23L_101_APTEKA_INVENTORY_H
#include <map>
#include <set>
#include <memory>
#include "medicine.h"

class Inventory {
private:
    std::map<Affliction,std::unique_ptr<std::set<std::shared_ptr<Medicine>> >> inventory;
    void addMedicine(std::unique_ptr<Medicine>);
public:
    Inventory();

    std::shared_ptr<Medicine> findSubstitute(const std::shared_ptr<Medicine>& medicine);

    void pickMedicine(const std::shared_ptr<Medicine>& medicine);
    void pickMedicine(const std::shared_ptr<Medicine>& medicine,int number);
    bool isMedicineInMagazine(const std::shared_ptr<Medicine>& medicine, int number) const;
    bool isMedicineInMagazine(const std::shared_ptr<Medicine> &medicine) const;
    unsigned howManyInMagazine(const std::shared_ptr<Medicine>& medicine) const;
    std::shared_ptr<Medicine> findRandomMedicine();

    std::shared_ptr<Medicine> findRandomMedicine(Affliction affliction);

    int numberOfMedicines();

    int numberOfMedicines(Affliction affliction);

#ifdef TESTING_ENV
    void addNewMedicine(std::shared_ptr<Medicine> medicine);
#endif

};



#endif //PROI_23L_101_APTEKA_INVENTORY_H

#ifndef PROI_23L_101_APTEKA_INVENTORY_H
#define PROI_23L_101_APTEKA_INVENTORY_H
#include <map>
#include <set>
#include <memory>
#include "medicine.h"

class Inventory {
private:
    std::map<Affliction,std::unique_ptr<std::set<std::shared_ptr<Medicine>> >> inventory;
    //Jeśli lek byłby tworzony przy pomocy pliku i fileManagera
    void addMedicine(std::unique_ptr<Medicine>);
public:
    Inventory();
    std::shared_ptr<Medicine> findSubstitute(const std::shared_ptr<Medicine>& medicine);
    void pickMedicine(const std::shared_ptr<Medicine>& medicine);
    bool isMedicineInMagazine(const std::shared_ptr<Medicine>& medicine) const;
    std::shared_ptr<Medicine> findRandomMedicine();
    std::shared_ptr<Medicine> findRandomMedicine(Affliction affliction);
};



#endif //PROI_23L_101_APTEKA_INVENTORY_H

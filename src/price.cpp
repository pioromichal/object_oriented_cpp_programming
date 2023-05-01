#include <iostream>
#include "../include/price.h"


Price::Price(unsigned zlotys, unsigned grosze) {
    setZlotys(zlotys);
    setGorsze(grosze);
}

void Price::setZlotys(const unsigned newZlotys) {
    zlotys = newZlotys;
}
void Price::setGorsze(const unsigned newGrosze) {
    zlotys += newGrosze / 100;
    grosze = newGrosze % 100;
}
unsigned Price::getZlotys() const {
    return zlotys;
}
unsigned Price::getGrosze() const {
    return grosze;
}

Price& Price::operator+=(const Price& secondPrice) {
    setZlotys(zlotys + secondPrice.zlotys);
    setGorsze(grosze + secondPrice.grosze);
    return *this;
}
Price Price::operator+(const Price& secondPrice) const {
    Price newPrice = *this;
    newPrice += secondPrice;
    return newPrice;
}
Price Price::operator*(const unsigned& multiplier) const {
    return Price(zlotys * multiplier, grosze * multiplier);
}
Price Price::operator/(const unsigned& divider) const {

    return Price(0, (zlotys * 100 + grosze) / divider);
}


bool Price::operator==(const Price& otherPrice) const {
    return (zlotys == otherPrice.zlotys) && (grosze == otherPrice.grosze);
}
bool Price::operator!=(const Price& otherPrice) const {
    return !(*this == otherPrice);
}
bool Price::operator<(const Price& otherPrice) const {
    return (zlotys <= otherPrice.zlotys) && (grosze < otherPrice.grosze);
}
bool Price::operator>(const Price& otherPrice) const {
    return otherPrice < *this;
}
bool Price::operator<=(const Price& otherPrice) const {
    return !(*this > otherPrice);
}
bool Price::operator>=(const Price& otherPrice) const {
    return !(*this < otherPrice);
}

std::ostream& operator<<(std::ostream& os, const Price& Price) {
    os << Price.zlotys << ",";
    if (Price.grosze < 10)
        os << 0;
    os << Price.grosze << " PLN";
    return os;
}
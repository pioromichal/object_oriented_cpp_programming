#ifndef PRICEH
#define PRICEH

#include <string>

class Price {
private:
    unsigned zlotys;
    unsigned grosze;
public:
    Price(unsigned zlotys, unsigned grosze);
    void setZlotys(const unsigned newZlotys);
    void setGrosze(const unsigned newGrosze);
    unsigned getZlotys() const;
    unsigned getGrosze() const;

    Price& operator+=(const Price& secondPrice);
    Price operator+(const Price& secondPrice) const;
    Price operator*(const unsigned& multiplier) const;
    Price operator/(const unsigned& divider) const;

    bool operator==(const Price& otherPrice) const;
    bool operator!=(const Price& otherPrice) const;
    bool operator<(const Price& otherPrice) const;
    bool operator>(const Price& otherPrice) const;
    bool operator<=(const Price& otherPrice) const;
    bool operator>=(const Price& otherPrice) const;
    friend std::ostream& operator<<(std::ostream& os, const Price& Price);
};

std::ostream& operator<<(std::ostream& os, const Price& Price);

#endif
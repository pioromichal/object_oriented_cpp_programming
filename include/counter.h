#ifndef PROI_23L_101_APTEKA_COUNTER_H
#define PROI_23L_101_APTEKA_COUNTER_H
#include <memory>

class Counter {
private:
    inline static unsigned idNumbering = 1;
    unsigned timeOpened;
    unsigned id;
    bool opened;
    bool occupied;
public:
    Counter(bool isOpened);

    bool isOccupied() const;

    void setIsOccupied(bool isOccupied);

    unsigned int getTimeOpened() const;

    unsigned int getId() const;

    bool isOpened() const;

    void closeCounter();

    void openCounter();

    static bool compareTimeWorking(const std::unique_ptr<Counter>& left, const std::unique_ptr<Counter>& right);

    bool operator<(const Counter &rhs) const;

    Counter& operator++();

    Counter operator++(int);

#ifdef TESTING_ENV
    static void resetIdNumbering();
#endif
};


#endif //PROI_23L_101_APTEKA_COUNTER_H

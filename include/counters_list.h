#ifndef PROI_23L_101_APTEKA_COUNTERS_LIST_H
#define PROI_23L_101_APTEKA_COUNTERS_LIST_H
#include <set>
#include <memory>
#include "counter.h"
class CountersList {
private:
    std::set<std::unique_ptr<Counter>> setCounters;

    unsigned char nOpenedCounters;
    unsigned int nAllCounters;
    void addCounter(bool openCounter);
public:
    CountersList(unsigned numberOfCounters, unsigned char openedCounters);

    std::unique_ptr<Counter>& findLongestWorking();

    void openCounter(unsigned id);

    void closeCounter(unsigned id);

    unsigned char getOpenedCounters() const;

    unsigned int getAllCounters() const;

    std::unique_ptr<Counter>& getOpenCounter();

    std::unique_ptr<Counter>& getCounter(unsigned id);

    void nextTurn();

#ifdef TESTING_ENV
    const std::set<std::unique_ptr<Counter>>& getSet() const;
#endif
 };


#endif //PROI_23L_101_APTEKA_COUNTERS_LIST_H

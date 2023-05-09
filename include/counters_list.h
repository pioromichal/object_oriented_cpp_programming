 //
// Created by damia on 06.04.2023.
//

#ifndef PROI_23L_101_APTEKA_COUNTERS_LIST_H
#define PROI_23L_101_APTEKA_COUNTERS_LIST_H
#include <set>
#include <memory>
#include "counter.h"
class CountersList {
private:
    std::set<std::unique_ptr<Counter>> setCounters;

    unsigned char openedCounters;

    void addCounter(bool openCounter);
public:
    CountersList(unsigned numberOfCounters, unsigned char openedCounters);

    std::unique_ptr<Counter>& findLongestWorking();

    void openCounter(unsigned id);

    void closeCounter(unsigned id);

    unsigned char getOpenedCounters() const;

    std::unique_ptr<Counter>& getCounter(unsigned id);

    void nextTurn();

#ifdef TESTING_ENV
    const std::set<std::unique_ptr<Counter>>& getSet() const;
#endif
 };


#endif //PROI_23L_101_APTEKA_COUNTERS_LIST_H

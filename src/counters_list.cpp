#include "../include/counters_list.h"
#include "../include/counter.h"
#include <algorithm>
#include <stdexcept>

CountersList::CountersList(unsigned int numberOfCounters, unsigned char openedCounters): nOpenedCounters(openedCounters),nAllCounters(numberOfCounters) {
    if(numberOfCounters<openedCounters){
        throw std::invalid_argument("You cannot open more counters than there is in the pharmacy");
    }
    for(int i=0;i<numberOfCounters;i++){
        if(i<openedCounters){
            addCounter(true);
        }
        else{
            addCounter(false);
        }
    }
}

std::unique_ptr<Counter>& CountersList::findLongestWorking() {
    auto it = std::max_element(setCounters.begin(),setCounters.end(),&Counter::compareTimeWorking);
    return const_cast<std::unique_ptr<Counter> &>(*it);
}

unsigned char CountersList::getOpenedCounters() const {
    return nOpenedCounters;
}

void CountersList::addCounter(bool openCounter) {
    std::unique_ptr<Counter> ptr = std::make_unique<Counter>(openCounter);
    setCounters.insert(std::move(ptr));
}

void CountersList::nextTurn() {
    for(auto &counter:setCounters){
        if(counter->isOpened()){
            (*counter)++;
        }
    }
}
#ifdef TESTING_ENV
const std::set<std::unique_ptr<Counter>> &CountersList::getSet() const {
    return setCounters;
}
#endif

void CountersList::openCounter(unsigned int id) {
    if(id>setCounters.size()){
        throw std::invalid_argument("There is no counter of such id");
    }
    for(auto &counter:setCounters){
        if(counter->getId()==id){
            counter->openCounter();
            nOpenedCounters++;
            return;
        }
    }
}

void CountersList::closeCounter(unsigned int id) {
    if(id>setCounters.size()){
        throw std::invalid_argument("There is no counter of such id");
    }
    for(auto &counter:setCounters){
        if(counter->getId()==id){
            counter->closeCounter();
            nOpenedCounters--;
            return;
        }
    }
}

std::unique_ptr<Counter> &CountersList::getCounter(unsigned int id) {
    if(id>setCounters.size()){
        throw std::invalid_argument("There is no counter of such id");
    }
    for(auto &counter:setCounters){
        if(counter->getId()==id){
            return const_cast<std::unique_ptr<Counter> &>(counter);
        }
    }
}

unsigned int CountersList::getAllCounters() const {
    return nAllCounters;
}

std::unique_ptr<Counter> &CountersList::getOpenCounter() {
    for (auto &counter: setCounters) {
        if (counter->isOpened() && !counter->isOccupied()) {
            return const_cast<std::unique_ptr<Counter> &>(counter);
        }
    }
    throw std::invalid_argument("No opened counters");
}
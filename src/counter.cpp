//
// Created by damia on 06.04.2023.
//

#include "../include/counter.h"

Counter::Counter(bool isOpened) : timeOpened(0), id(idNumbering++), opened(isOpened), occupied(false) {
}

bool Counter::compareTimeWorking(const std::unique_ptr<Counter> &left, const std::unique_ptr<Counter> &right) {
    return left->getTimeOpened() < right->getTimeOpened();
}


void Counter::closeCounter() {
    opened = false;
    timeOpened = 0;
}

void Counter::openCounter() {
    opened = true;
}

bool Counter::operator<(const Counter &rhs) const {
    return this->id<rhs.id;
}

Counter &Counter::operator++() {
    timeOpened+=1;
    return *this;
}

Counter Counter::operator++(int) {
   Counter old = *this;
   ++(*this);
    return old;
}

unsigned int Counter::getTimeOpened() const {
    return timeOpened;
}

unsigned int Counter::getId() const {
    return id;
}

bool Counter::isOpened() const {
    return opened;
}
#ifdef TESTING_ENV
void Counter::resetIdNumbering() {
    idNumbering = 1;
}
#endif
bool Counter::isOccupied() const {
    return occupied;
}

void Counter::setIsOccupied(bool isOccupied) {
    Counter::occupied = isOccupied;
}

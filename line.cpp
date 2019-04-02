//
//  line.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 4/2/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "line.hpp"

line::line() {
    totalLineTime = 0;
}

void line::addCustomer(long newCustomer) {
    customersInLine.push(newCustomer);
    totalLineTime += newCustomer;
}

void line::removeCustomer() {
    long leavingCustomer = customersInLine.front();
    customersInLine.pop();
    totalLineTime -= leavingCustomer;
}

void line::updateTime(long timePassed) {
    totalLineTime -= timePassed;
}

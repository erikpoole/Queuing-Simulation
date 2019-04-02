//
//  line.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 4/2/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "line.hpp"

line::line(int numRegisters) {
    totalLineTime = 0;
    registers = numRegisters;
}

void line::addCustomer(long newCustomer) {
    totalLineTime += newCustomer;
}

void line::syncLine(long timePassed) {
    totalLineTime -= timePassed;
    if (totalLineTime < 0) {
        totalLineTime = 0;
    }
}

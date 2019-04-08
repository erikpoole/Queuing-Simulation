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

void line::addCustomer(customer newCustomer) {
    totalLineTime += newCustomer.getTimeNeeded();
    customers.push(newCustomer);
}

customer line::removeCustomer(){
    if(customers.size() == 0) return {-1,-1};
    customer currentCustomer = customers.front();
    customers.pop();
    return currentCustomer;
};

int line::getTotalLineTime(){
    return totalLineTime;
}

int line::getRegister(){
    return registers;
}

int line::getCustomerQueueSize(){
    return customers.size();
}

void line::setRegister(int i){
    registers += i;
}

void line::syncLine(long timePassed) {
    if (customers.size() != 0) {
        totalLineTime -= timePassed;
        if (totalLineTime < 0) {
            totalLineTime = 0;
        }
    }
}

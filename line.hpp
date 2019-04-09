//
//  line.hpp
//  queuingSimulation
//
//  Created by Erik Poole on 4/2/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#ifndef line_hpp
#define line_hpp

#include <stdio.h>
#include <queue>
#include "customer.hpp"

#endif /* line_hpp */


class line {
private:
    long totalLineTime;
    int registers;
    std::queue<customer> customers;
public:
    line(int numRegisters);
    int getTotalLineTime();
    int getRegister();
    void setRegister(int i);
    int getCustomerQueueSize();
    void addCustomer(customer newCustomer);
    customer removeCustomer();
    void syncLine(long timePassed);
};

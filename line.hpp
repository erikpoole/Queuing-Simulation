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

#endif /* line_hpp */


class line {
public:
    std::queue<long> customersInLine;
    long totalLineTime;
    
    line();
    void addCustomer(long newCustomer);
    void removeCustomer();
    void updateTime(long timePassed);
};

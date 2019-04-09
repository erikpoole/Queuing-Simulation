//
//  customer.hpp
//  queuingSimulation
//
//  Created by Erik Poole on 4/2/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#ifndef customer_hpp
#define customer_hpp

#include <stdio.h>

#endif /* customer_hpp */

class customer{
private:
    long arrivalTime;
    long timeNeeded;
public:
    long getArrivalTime();
    long getTimeNeeded();
    customer(long inputArrivalTime, long inputTimeNeeded);
};

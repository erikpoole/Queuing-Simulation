//
//  customer.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 4/2/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "customer.hpp"

customer::customer(long inputArrivalTime, long inputTimeNeeded) {
    arrivalTime = inputArrivalTime;
    timeNeeded = inputTimeNeeded;
}

//
//  event.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include "event.hpp"

event::event(long inputTime) {
    startTime = inputTime;
}

bool compareEvents::operator()(event rhs, event lhs) {
    return rhs.startTime > lhs.startTime;
}


//
//  event.hpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include <stdio.h>

#endif /* event_hpp */

class event {
public:
    long startTime;
    
    event(long inputTime);
};

class newPersonEvent : public event {
    using event::event;
};

class tellerFreedEvent : public event {
    using event::event;
};

class compareEvents {
public:
    bool operator()(event rhs, event lhs);
};




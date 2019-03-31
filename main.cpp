//
//  main.cpp
//  queuingSimulation
//
//  Created by Erik Poole on 3/31/19.
//  Copyright © 2019 ErikPoole. All rights reserved.
//

#include <iostream>
#include <queue>
#include "event.hpp"

int main(int argc, const char * argv[]) {
    
    std::priority_queue<event, std::vector<event>, compareEvents> eventQueue;
    
    for (int i = 0; i < 100; i += 10) {
        eventQueue.push(newPersonEvent(i));
    }
    
    for (int i = 0; i < 10; i++) {
        std::cout << eventQueue.size() << "\n";
        std::cout << eventQueue.top().startTime << "\n";
        eventQueue.pop();
    }
}

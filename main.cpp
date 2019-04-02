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
    
    double customersPerSecond = std::stod(argv[1]) / 60;
    double maximumServiceTimeInSeconds = std::stod(argv[2]) * 60;
    double randomSeed = std::stod(argv[3]);
    
//    std::cout << 1/customersPerSecond << "\n" << maximumServiceTimeInSeconds << "\n" << randomSeed << "\n";
    
    long globalTimeInSeconds = 0;
    long workdayInSeconds = 12*60*60;
    long lineTime = 0;
    int registerCount = 6;
    
    srand(randomSeed);
    std::priority_queue<event*, std::vector<event*>, compareEvents> eventQueue;
    std::queue<long> lineTimes;
    
    //TODO close enough to number..?
    for (int i = 0; i < workdayInSeconds; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0);
            eventQueue.push(eventPtr);
        }
    }
    
    double totalEvents = 0;
    double customers = eventQueue.size();
    while (eventQueue.size() != 0) {
//        std::cout << eventQueue.top()->eventTime << "\n";
        event* currentEventPtr = eventQueue.top();
        currentEventPtr->handleEvent(globalTimeInSeconds, lineTime, lineTimes, eventQueue, registerCount);
        
        void handleEvent(long &globalTime, long &totalLineTime, std::queue<long> &lineTimes, std::priority_queue<event, std::vector<event>, compareEvents> &eventQueue, int &freeRegisters);

        eventQueue.pop();
        totalEvents++;
    }
    assert(totalEvents == customers * 2);
}

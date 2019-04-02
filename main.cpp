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
    std::vector<long> customerTimes;
    
    //TODO close enough to number..?
    for (int i = 0; i < workdayInSeconds/10; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0);
            eventQueue.push(eventPtr);
        }
    }
    
    double totalEvents = 0;
    double customers = eventQueue.size();
    while (eventQueue.size() != 0) {
        std::cout << eventQueue.top()->eventTime << "\n";
        event* currentEventPtr = eventQueue.top();
        eventQueue.pop();
        currentEventPtr->handleEvent(globalTimeInSeconds, lineTime, lineTimes, eventQueue, registerCount);
        
        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
        
        totalEvents++;
    }
    assert(totalEvents == customers * 2);
    
    for (long time : customerTimes) {
        std::cout << time << "\n";
    }
    
    std::cout << "Bank service time in minutes: ";
    printPercentiles(customerTimes);
    
    
}

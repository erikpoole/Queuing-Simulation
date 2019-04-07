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

const long endTime = 12*60*60;

std::vector<line> getBankLine(){
    std::vector<line> bankLines;
    bankLines.push_back(line(6));
    return bankLines;
}

std::vector<line> getMarketLines(){
    std::vector<line> marketLines;
    for (int i = 0; i < 6; i++) {
        marketLines.push_back(line(1));
    }

    return marketLines;
}

void fillEventQueue(std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue,  double customersPerSecond,
    double maximumServiceTimeInSeconds){
    for (int i = 0; i < endTime; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0, -1);
            eventQueue.push(eventPtr);
        }
    }
}

void printServiceResult(std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue,
    std::vector<line> &Lines, std::vector<long>& customerTimes, int randomSeed){
    srand(randomSeed);
    long currentTime = 0;
    while (eventQueue.size() != 0 && currentTime < endTime) {

        event* currentEventPtr = eventQueue.top();
        eventQueue.pop();

        currentEventPtr->handleEvent(currentTime, Lines, eventQueue);

        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
    }

    //reuse prupose
    while(eventQueue.size() !=0){
        eventQueue.pop();
    }

    std::sort(customerTimes.begin(), customerTimes.end());
    printPercentiles(customerTimes);

    //resue purpose
    customerTimes.clear();
}


int main(int argc, const char * argv[]) {
    
    double customersPerSecond = std::stod(argv[1]) / 60;
    double maximumServiceTimeInSeconds = std::stod(argv[2]) * 60;
    int randomSeed = std::stod(argv[3]);

    
    srand(randomSeed);
    std::priority_queue<event*, std::vector<event*>, compareEvents> eventQueue;
    std::vector<long> customerTimes;

    //Simulate bank service
    std::vector<line> bankline = getBankLine();
    fillEventQueue(eventQueue, customersPerSecond, maximumServiceTimeInSeconds);
    printServiceResult(eventQueue, bankline, customerTimes, randomSeed);

    //Simulate SupermarketService
    std::vector<line> marketLines = getMarketLines();
    fillEventQueue(eventQueue, customersPerSecond, maximumServiceTimeInSeconds);
    printServiceResult(eventQueue, marketLines, customerTimes, randomSeed);
    
}

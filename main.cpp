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

const long globalTimeInSeconds = 0;
const long workdayInSeconds = 12*60*60;

std::vector<long> getBankLine(){
    std::vector<line> bankLines;
    bankLines.push_back(line(6));
    return bankLines;
}

std::vector<long> getMarketLines(){
    std::vector<line> marketLines;
    for (int i = 0; i < 6; i++) {
        marketLines.push_back(line(1));
    }

    return marketLines;
}


void printServiceResult(std::priority_queue<event*, std::vector<event*>, compareEvents> &eventQueue,
    std::vector<line> &Lines, std::vector<long>& customerTimes){
    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {

        event* currentEventPtr = eventQueue.top();
        eventQueue.pop();

        currentEventPtr->handleEvent(globalTimeInSeconds, Lines, eventQueue);

        if (currentEventPtr->timeTaken != 0) {
            customerTimes.push_back(currentEventPtr->timeTaken);
        }
    }

    while(eventQueue.size() !=0){
        eventQueue.pop();
    }

    std::sort(customerTimes.begin(), customerTimes.end());
    printPercentiles(customerTimes);

    customerTimes.clear();
}


int main(int argc, const char * argv[]) {
    
    double customersPerSecond = std::stod(argv[1]) / 60;
    double maximumServiceTimeInSeconds = std::stod(argv[2]) * 60;
    int randomSeed = std::stod(argv[3]);

    
    srand(randomSeed);
    std::priority_queue<event*, std::vector<event*>, compareEvents> eventQueue;
    std::vector<long> customerTimes;
    
    // Fill out the eventQueue
    for (int i = 0; i < workdayInSeconds; i++) {
        if (rand() % (long) (1/customersPerSecond) == 0) {
            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0, -1);
            eventQueue.push(eventPtr);
        }
    }

    //Simulate bank service
    std::vector<long> bankline = getBankLine();
    printServiceResult(eventQueue, bankline, customerTimes);
    //Simulate SupermarketService
    std::vector<long> marketLines = getMarketLines();
    printServiceResult(eventQueue, marketLines, customerTimes);
    
////    std::cout << "Total Customers: " << eventQueue.size() << "\n\n";
//    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {
//
//        event* currentEventPtr = eventQueue.top();
//        eventQueue.pop();
//
//        currentEventPtr->handleEvent(globalTimeInSeconds, bankLines, eventQueue);
//
////        std::cout << currentEventPtr->timeTaken << "\n";
//        if (currentEventPtr->timeTaken != 0) {
//            customerTimes.push_back(currentEventPtr->timeTaken);
//        }
//    }
//
//    while(eventQueue.size() !=0){
//        eventQueue.pop();
//    }
//
////    for (double time : customerTimes) {
////        std::cout << time << "\n";
////    }
//
////    std::cout << "Customers Served: " << customerTimes.size() << "\n";
//    std::sort(customerTimes.begin(), customerTimes.end());
////    std::cout << "Bank service time in minutes:\n";
//    printPercentiles(customerTimes);
    
    
    


//    globalTimeInSeconds = 0;
//
//
//    srand(randomSeed);
//    eventQueue = std::priority_queue<event*, std::vector<event*>, compareEvents>();
//    customerTimes = std::vector<long>();
//    assert(eventQueue.size() == 0 && customerTimes.size() == 0);
//
//    std::vector<line> marketLines;
//    for (int i = 0; i < 6; i++) {
//        marketLines.push_back(line(1));
//    }
//
//
//    //TODO close enough to number..?
//    for (int i = 0; i < workdayInSeconds; i++) {
//        if (rand() % (long) (1/customersPerSecond) == 0) {
//            long serviceTime = rand() % (long) maximumServiceTimeInSeconds;
//            newPersonEvent* eventPtr = new newPersonEvent(i, serviceTime, 0, -1);
//            eventQueue.push(eventPtr);
//        }
//    }
//
//    while (eventQueue.size() != 0 && globalTimeInSeconds < workdayInSeconds) {
//
//        event* currentEventPtr = eventQueue.top();
//        eventQueue.pop();
//
//        currentEventPtr->handleEvent(globalTimeInSeconds, marketLines, eventQueue);
//
////        std::cout << currentEventPtr->timeTaken << "\n";
//        if (currentEventPtr->timeTaken != 0) {
//            customerTimes.push_back(currentEventPtr->timeTaken);
//        }
//    }
//
////    for (double time : customerTimes) {
////        std::cout << time << "\n";
////    }
//
//    std::cout << "Customers Served: " << customerTimes.size() << "\n";
//    std::sort(customerTimes.begin(), customerTimes.end());
//    std::cout << "Supermarket service time in minutes:\n";
//    printPercentiles(customerTimes);

    
    
}

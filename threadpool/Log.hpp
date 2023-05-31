#pragma once

#include<iostream>
#include<ctime>
#include<pthread.h>

std::ostream &Log()
{
    std::cout << "For Debug |" << " timestamp: " << (uint64_t)time(nullptr) 
    << " | " << " Thread[" << pthread_self() << "] | ";

    return std::cout;
}
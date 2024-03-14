//
// Created on 2024/3/13.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONY_SINGLETON_H
#define HARMONY_SINGLETON_H
#include "PullToRefreshNode.h"
#include <iostream>
#include <ostream>
class Singleton
{
public:
    ~Singleton(){
        std::cout<<"destructor called!"<<std::endl;
    }
 
    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&)=delete;
 
    static Singleton& getInstance(){
        static Singleton instance;
        return instance;
    }
 
private:
    Singleton(){
        std::cout<<"constructor called!"<<std::endl;
    }
public:
    rnoh::PullToRefreshNode pullNode;
};

#endif //HARMONY_SINGLETON_H

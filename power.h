#pragma once
#include "mathematical.h"

template<typename T>
class Power : public Mathematical<T>{
    public:
        Tensor<T> *res1;
    
    Power(Tensor<T> *res1){
        this->res1 = res1;
    }
    void backward(std::vector<T> grad);
    Tensor<T> forward();
};

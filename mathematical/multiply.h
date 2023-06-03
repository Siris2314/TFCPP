#pragma once
#include "mathematical.h"
template<typename T>
class Multiply : public Mathematical<T>{
    public:
        Tensor<T> *res1, *res2;
    
    Multiply(Tensor<T> *res1, Tensor<T> *res2){
        this->res1 = res1;
        this->res2 = res2;
    }
    void backward(std::vector<T> grad);
    Tensor<T> forward();
};

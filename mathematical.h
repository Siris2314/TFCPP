#pragma once
#include "common.h"

template<typename T>
class Tensor;

template<typename T>
class Mathematical{

    public:
        Tensor<T> *res1, *res2;

        virtual void backward(std::vector<T> grad) = 0;

        virtual Tensor<T> forward() = 0;



};

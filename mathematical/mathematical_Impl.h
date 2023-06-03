#pragma once
#include "mathematical.h"
#include "multiply.h"
#include "add.h"
#include "../tensor/tensor.h"
#include "division.h"
#include "power.h"
#include "overloads.h"

template <typename T>
void Multiply<T>::backward(std::vector<T> grad){
    this->res1->backward(grad * this->res2->value); 
    this->res2->backward(grad * this->res1->value);
}


template <typename T>
Tensor<T> Multiply<T>::forward(){
       return Tensor<T>(this->res1->value * this->res2->value, this);
 }

template <typename T>
 void Add<T>::backward(std::vector<T> grad){
    this->res1->backward(grad); 
    this->res2->backward(grad);
}

template <typename T>
Tensor<T> Add<T>::forward(){
    return Tensor<T>(this->res1->value + this->res2->value, this);
 }

template <typename T>
void Division<T>::backward(std::vector<T> grad){
    this->res1->backward(grad/this->res2->value); 
    //Cast to Vector
    std::vector<T> temp = grad*this->res1->value;
    this->res2->backward((temp * ( (T)(-1) / (this->res2->value)^(T)2)));
}


template <typename T>
Tensor<T> Division<T>::forward(){
       return Tensor<T>(this->res1->value / this->res2->value, this);
 }



template <typename T>
void Power<T>::backward(std::vector<T> grad){
    this->res1->backward(grad*exponential(this->res1->value));
}


template <typename T>
Tensor<T> Power<T>::forward(){
       return Tensor<T>(exponential(this->res1->value), this);
 }

 
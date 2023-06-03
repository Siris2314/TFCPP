#pragma once 
#include "../tensor/common.h"
#include <cmath>

template <typename T>
std::vector<T> operator * (std::vector<T> &v1, const std::vector<T> &v2){
    assert(v1.size() == v2.size() && "Vectors must be of same size");
    std::vector<T> res;
    for(int i = 0; i < v1.size(); i++){
        res.push_back(v1[i] * v2[i]);
    }
    return res;
}

template <typename T>
std::vector<T> operator + (std::vector<T> &v1, const std::vector<T> &v2){
    assert(v1.size() == v2.size() && "Vectors must be of same size");
    std::vector<T> res;
    for(int i = 0; i < v1.size(); i++){
        res.push_back(v1[i] + v2[i]);
    }
    return res;
}

template <typename T>
std::vector<T> operator / (std::vector<T> &v1, const std::vector<T> &v2){
    assert(v1.size() == v2.size() && "Vectors must be of same size");
    std::vector<T> res;
    for(int i = 0; i < v1.size(); i++){
        res.push_back(v1[i] / v2[i]);
    }
    return res;
}



//Scalar operations
template <typename T>
std::vector<T> operator / (T v1, const std::vector<T> &v2){
    std::vector<T> res;
    for(int i = 0; i < v2.size(); i++){
        res.push_back(v1 / v2[i]);
    }
    return res;
}

template <typename T>
std::vector<T> operator ^ (const std::vector<T> &v2, T v1){
    std::vector<T> res;
    for(int i = 0; i < v2.size(); i++){
        res.push_back(pow(v2[i], v1));
    }
    return res;
}

template <typename T>
std::vector<T> exponential(const std::vector<T> &v1){
    std::vector<T> res;
    for(int i = 0; i < v1.size(); i++){
        res.push_back(exp(v1[i]));
    }
    return res;
}
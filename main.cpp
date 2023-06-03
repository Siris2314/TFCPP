#include <iostream>
#include "./tensor/tensor.h"
#include "./mathematical/mathematical.h"
#include "./mathematical/matrix.h"

template <typename T>
void printTensor(std::vector<T> &a){

    for(auto i: a){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void sigmoidChecker(){
    Tensor<float> w0(std::vector<float> {2});
    Tensor<float> x0(std::vector<float> {-1});

    Tensor<float> w1(std::vector<float> {-3});
    Tensor<float> x1(std::vector<float> {-2});

    Tensor<float> w3(std::vector<float> {-3});

    Tensor<float> a = w0*x0;
    Tensor<float> b = w1*x1;
    Tensor<float> c = a+b;
    Tensor<float> d = c+w3;
    Tensor<float> e = Tensor<float>(std::vector<float> {-1});
    Tensor<float> f = d*e;
    Tensor<float> g = f.exp();
    Tensor<float> h = Tensor<float>(std::vector<float> {1});
    Tensor<float> i = h+g;
    Tensor<float> j = Tensor<float>(std::vector<float> {1});
    Tensor<float> k = j/i;
    k.backward(std::vector<float> {1});

    printTensor(w0.grad);
    printTensor(x0.grad);
    printTensor(w1.grad);
    printTensor(x1.grad);
    printTensor(w3.grad);
}

int main(){
    
    Matrix<float> a({1,2,4,5,6,7}, {3,2});
    Matrix<float> a2({1,2,4,5,6,7}, {2,3});
    auto m3  = a.dot(a2);
    std::cout<<m3<<std::endl;
    return 0;
}


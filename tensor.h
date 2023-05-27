#pragma once

#include "mathematical_Impl.h"
#include "multiply.h"
#include "add.h"
#include "division.h"
#include "power.h"


template <typename T>
class Tensor{
    public:
    std::vector<T> value; //Contains value within Tensor
    std::vector<T> grad; //Contains gradient of Tensor
    Mathematical<T> *frontOp = NULL, *backOp = NULL; //Contains the operation that created this tensor

    Tensor(){
        //default constructor
    }

    Tensor(std::vector<T> value){
        this->value = value;
    }

    Tensor(std::vector<T> value, Mathematical<T>* op){
        this->value = value;
        this->backOp = op;
        
    }

    Tensor(const Tensor<T>* obj){
        //default constructor
        this->backOp = obj->backOp;
        this->frontOp = obj->frontOp;
        this->value = obj->value;
        this->grad = obj->grad;
    } 


    void backward(std::vector<T> grad){
        this->grad = grad;
        if(this->backOp != NULL){
                this->backOp->backward(grad);
        }
    }


    Tensor<T> operator * (Tensor<T> &obj){
        this->frontOp = new Multiply<T>(this,&obj);
        obj.frontOp = this->frontOp;
        return this->frontOp->forward();

    }

    Tensor<T> operator * (const Tensor<T> &obj){
        Tensor<T>* temp = new Tensor<T>(&obj);
        this->frontOp = new Multiply<T>(this,temp);
        temp->frontOp = this->frontOp;
        return this->frontOp->forward();

    }

    Tensor<T> operator + (Tensor<T> &obj){
        this->frontOp = new Add<T>(this,&obj);
        obj.frontOp = this->frontOp;
        return this->frontOp->forward();

    }

    Tensor<T> operator + (const Tensor<T> &obj){
        Tensor<T>* temp = new Tensor<T>(&obj);
        this->frontOp = new Add<T>(this,temp);
        temp->frontOp = this->frontOp;
        return this->frontOp->forward();

    }

     Tensor<T> operator / (Tensor<T> &obj){
        this->frontOp = new Division<T>(this,&obj);
        return this->frontOp->forward();

    }

      Tensor<T> const operator / (const Tensor<T> &obj){
        Tensor<T>* temp = new Tensor<T>(&obj);
        this->frontOp = new Division<T>(this,temp);
        temp->frontOp = this->frontOp;
        return this->frontOp->forward();

    }

    Tensor<T> exp(){
        this->frontOp = new Power<T>(this);
        return this->frontOp->forward();

    }

};



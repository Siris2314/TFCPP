#pragma once
#include "../tensor/common.h"

template<typename T>
class Matrix{
    private:
    std::vector<int> traversed;
    bool isVector(const std::vector<T> &value,const std::vector<int> &shape){
        int size = 1;
        for(int i = 0; i < shape.size(); i++){
            size *= shape[i];
        }

        if(value.size() == size){
            return true;
        }
        else{
            return false;
        }
    }

    bool shapeVerify(const std::vector<T> &value,const std::vector<int> &shape){
       int pos = 1;
       for(int i = 0; i<shape.size(); i++){
           pos *= shape[i];
       }

       if(value.size() == pos){
           return true;
       }
       else{
           return false;
       }
    }

    std::vector<int> shape_calc(const std::vector<int> &shape){
        std::vector<int> traversed(shape.size(),0);
        int pos = 1;
        for(int i = shape.size()-1; i>=0; i--){
            traversed[i] = pos;
            pos *= shape[i];
        }

        return traversed;
    }

    bool dot_product_assert(const std::vector<int> shape){
       if(shape.size() < 2 || this->shape.size() != 2){
           return false;
       }
       int first_row = shape[shape.size()-2];
       int first_col = shape[shape.size()-1];
       int second_row = this->shape[this->shape.size()-2];
       int second_col = this->shape[this->shape.size()-1];

        if(first_col != second_row){
              return false;
         }
    
          return true;
    }

    void dot_product(const Matrix<T> &m2, std::vector<T> &final, int pos, int pos_final){
        int row1 = this->shape[this->shape.size()-2];
        int col1 = this->shape[this->shape.size()-1];
        int row2 = m2.shape[m2.shape.size()-2];
        int col2 = m2.shape[m2.shape.size()-1];

        assert(col1 == row2 && "Shapes must be compatible");

        for(int i = 0; i<row1; i++){
            for(int k = 0; k<col2; k++){
                T sum = 0;
                for(int j = 0; j<col1; j++){
                    sum += this->value[pos + i*col1 + j] * m2.value[j*col2 + k];
                }
                final[pos_final + i*col2 + k] = sum;
            }
        }


    }

    void matrix_mul(const Matrix<T> &m2, std::vector<T> &final, std::vector<int> &idx, std::vector<int> &finalElems, int dims){
        if(idx.size() == this->shape.size() - 2){

            int pos = 0;
            int pos_final = 0;
            for(int i = 0; i< idx.size(); i++){
                pos += idx[i] * traversed[i];
                pos_final += idx[i]*finalElems[i];
            }
            dot_product(m2, final, pos,pos_final);
            return;

        }

        for(int i = 0; i< this->shape[dims]; i++){
            idx.push_back(i);
            matrix_mul(m2, final, idx, finalElems, dims+1);
            idx.pop_back();
        }

    }

    std::ostream & print(std::ostream &out, std::vector<int> &stack, int dims){
        if(stack.size() == this->shape.size()-1){
            int pos = 0;
            for(auto i = 0; i<stack.size(); i++){
                pos += stack[i];
            }
            out<<"[ ";
            for(auto i = 0; i<this->shape.at(dims); i++){
                out<<this->value.at(pos + i)<<" ";
            }
            out<<"]";
            return out;
        }
        out<<"[ ";
        for(auto i = 0; i<this->shape.at(dims); i++){
            stack.push_back(traversed[dims]*i);
            print(out, stack, dims+1);
            stack.pop_back();
        }
        out<<" ]";
        return out;
    }
    public:
    std::vector<T> value;
    std::vector<int> shape;
    Matrix(std::vector<T> value, std::vector<int> shape){
        assert(isVector(value, shape) && "Shape and value must be compatible");
        this->value = value;
        this->shape = shape;
        this->traversed = shape_calc(shape);
    }  

    Matrix<T> operator + (const Matrix<T> &m2){
        assert(shapeVerify(shape) && "Shapes must be equal");
        return Matrix<T>(value + m2.value, shape);
    }

     Matrix<T> operator * (const Matrix<T> &m2){
        assert(shapeVerify(shape) && "Shapes must be equal");
        return Matrix<T>(value * m2.value, shape);
    }

     Matrix<T> operator / (const Matrix<T> &m2){
        assert(shapeVerify(shape) && "Shapes must be equal");
        return Matrix<T>(value / m2.value, shape);
    }

    Matrix<T> dot(const Matrix<T> &m2){
        assert(dot_product_assert(m2.shape) && "Shapes must be equal");
        std::vector <int> finalShape;
        int size = 1;
        for(int i = 0; i < this->shape.size()-1; i++){
            size *= this->shape[i];
            finalShape.push_back(this->shape[i]);
        }
        finalShape.push_back(m2.shape[1]);
        size *= m2.shape[1];
        std::vector<T> final(size, 0);
        std::vector<int> idx(0,0);
        auto finalElems = shape_calc(finalShape);
        matrix_mul(m2, final,idx,finalElems, 0);

        return Matrix<T>(final, finalShape);
    }

    template<typename E>
    friend std::ostream & operator << (std::ostream &out, Matrix<E> &m);



};

template<typename E>
std::ostream & operator << (std::ostream &out, Matrix<E> &m){

    std::vector<int> stack;
    return m.print(out, stack, 0);
}
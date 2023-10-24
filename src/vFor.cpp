//
// Created by mfrfo on 9/28/2023.
//

#include "vFor.hpp"


vFor::vFor(std::vector<float> &a, std::vector<float> &b) {
    if(a.size()>b.size()){
        int s = (int)a.size();
        float c_x = (float)s / 8.0f;
        int c_x_i = (int)std::ceil(c_x);
        a.resize(c_x_i*8);
        b.resize(a.size());
    }else{
        int s = (int)b.size();
        float c_x = (float)s / 8.0f;
        int c_x_i = (int)std::ceil(c_x);
        b.resize(c_x_i*8);
        a.resize(b.size());
    }
//        arr1 = a.data();
//        arr2 = b.data();
    arr1 = new float[a.size()];
    std::copy(a.begin(),a.end(),arr1);
    arr2 = new float[b.size()];
    std::copy(b.begin(),b.end(),arr2);
    length = a.size();
    result = new float[a.size()];
}

vFor::~vFor(){
    delete[] result;
    delete[] arr1;
    delete[] arr2;
}

void vFor::change_array(std::vector<float> &passed, int position) {
    switch (position) {
        case 0:
            if(passed.size() > length){
                resize(2,(int)passed.size());
                delete[] arr1;
                arr1 = new float[passed.size()];
                std::copy(passed.begin(),passed.end(),arr1);
            }else{
                std::cerr << "Passed Array is smaller than the Previous Array\n";
                delete[] arr1;
                arr1 = new float[length];
                std::copy(passed.begin(),passed.end(),arr1);
            }
            break;
        case 1:
            if(passed.size() > length){
                resize(1,(int)passed.size());
                delete[] arr2;
                arr2 = new float[passed.size()];
                std::copy(passed.begin(),passed.end(),arr2);
            }else{
                std::cerr << "Passed Array is smaller than the Previous Array\n";
                delete[] arr2;
                arr2 = new float[length];
                std::copy(passed.begin(),passed.end(),arr2);
            }
            break;
        default:
            throw std::exception("Wrong Parameters Passed");
    }
}

void vFor::add_arrays() {
    for (int i = 0; i < length; i += 8) {
        __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
        __m256 b_vec = _mm256_loadu_ps(&arr2[i]);
        __m256 c_vec = _mm256_add_ps(a_vec, b_vec);
        _mm256_storeu_ps(&result[i], c_vec);
    }
}


void vFor::sub_arrays(){
    for(int i=0;i<length;i += 8){
        __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
        __m256 b_vec = _mm256_loadu_ps(&arr2[i]);
        __m256 c_vec = _mm256_sub_ps(a_vec, b_vec);
        _mm256_storeu_ps(&result[i], c_vec);
    }
}


void vFor::divide_arrays(){
    for(int i=0;i<length;i += 8){
        __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
        __m256 b_vec = _mm256_loadu_ps(&arr2[i]);
        __m256 c_vec = _mm256_div_ps(a_vec, b_vec);
        _mm256_storeu_ps(&result[i], c_vec);
    }
}


void vFor::mul_arryas(){
    for(int i=0;i<length;i += 8){
        __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
        __m256 b_vec = _mm256_loadu_ps(&arr2[i]);
        __m256 c_vec = _mm256_mul_ps(a_vec, b_vec);
        _mm256_storeu_ps(&result[i], c_vec);
    }
}


void vFor::add_scalar(float scalar,int arr){
    if(arr == 0){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_add_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else if(arr == 1){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr2[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_add_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else{
        throw std::exception("Wrong Parameters");
    }
}


void vFor::sub_scalar(float scalar,int arr){
    if(arr == 0){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_sub_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else if(arr == 1){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr2[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_sub_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else{
        throw std::exception("Wrong Parameters");
    }
}

void vFor::div_scalar(float scalar,int arr){
    if(arr == 0){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_sub_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else if(arr == 1){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr2[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_div_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else{
        throw std::exception("Wrong Parameters");
    }
}


void vFor::mul_scalar(float scalar,int arr){
    if(arr == 0){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr1[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_sub_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else if(arr == 1){
        for(int i=0;i<length;i += 8){
            __m256 a_vec = _mm256_loadu_ps(&arr2[i]);
            __m256 sc = _mm256_set_ps(scalar,scalar,scalar,scalar,scalar,scalar,scalar,scalar);
            __m256 c_vec = _mm256_mul_ps(a_vec, sc);
            _mm256_storeu_ps(&result[i], c_vec);
        }
    }else{
        throw std::exception("Wrong Parameters");
    }
}

std::vector<float> vFor::get_result(){
    std::vector<float> v(result, result + length);
    return v;
}

void vFor::resize(int arr_num,int new_size){
    float *tmp = new float[new_size];
    switch (arr_num) {
        case 1:
            std::copy(arr1,arr1+length,tmp);
            delete[] arr1;
            arr1 = tmp;
            break;
        case 2:
            std::copy(arr2,arr2+length,tmp);
            delete[] arr2;
            arr2 =tmp;
            break;
        default:
            throw std::exception("Invalid Parameters");
    }
}
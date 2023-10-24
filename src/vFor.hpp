//
// Created by mfrfo on 9/28/2023.
//

#ifndef CPPVECTORISEDLOOPS_VFOR_HPP
#define CPPVECTORISEDLOOPS_VFOR_HPP

#include <vector>
#include <type_traits>
#include <immintrin.h>
#include <cmath>
#include <iostream>
/*!
 * @brief This is a Vectorised Loop Class That Performs Operation Based On THE AVX2 Enhanced Instruction SET.
 */
class vFor {
public:
    /*!
     * @brief This Initiates 2 Heap Allocated Arrays That Will Perform Vectorised Operations
     * @param a This Is The 1st 1D Vector That Will Be copied into a head memory to Perform Vectorised Operation
     * @param b This Is The 2nd 1D Vector That Will Be copied into a head memory to Perform Vectorised Operation
     */
    vFor(std::vector<float> &a , std::vector<float> &b);
    ~vFor();

    /*!
     * @brief Change Any of the two arrays you are currently working with
     * @param passed this is the new array that will replace specified previous array
     * @param position this is which of the 2 arrays you will replace , 0 means the 1st array will be replaced  and 1 means the 2nd array will be replaced
     */
    void change_array(std::vector<float> &passed, int position);

    void add_arrays();
    void sub_arrays();
    void divide_arrays();
    void mul_arryas();
    void add_scalar(float scalar,int arr);
    void sub_scalar(float scalar,int arr);
    void div_scalar(float scalar,int arr);
    void mul_scalar(float scalar,int arr);


    std::vector<float> get_result();


private:
    float *arr1;
    float *arr2;
    float *result;
    size_t length;


    void resize(int arr_num,int new_size);

};


#endif //CPPVECTORISEDLOOPS_VFOR_HPP

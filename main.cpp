#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#include "src/vFor.hpp"


long long timeFunction(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration.count();
}

int main() {
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    std::vector<float> x1(100000000);
    std::vector<float> x2(100000000);
    for(int i=0;i<100000000;i++){
        x1[i] = 1;
        float temp = (float)uniform_dist(e1);
        x2[i] = temp;
    }

    vFor g1(x1,x2);

    // Addition - AVX2
    std::cout << "For Addition\n";
    std::function<void()> func_add = [ObjectPtr = &g1] { ObjectPtr->add_arrays(); };
    long long addition_time = timeFunction(func_add);
    std::cout << "For Our Vectorised Loop The Time Taken :" << addition_time << "\n";

    // Addition Normal
    auto t3 = std::chrono::high_resolution_clock::now();
    std::vector<float> x3(100000000);
    for(int i=0;i<100000000;i++){
        x3[i] = x1[i] + x2[i];
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
    std::cout << "For a Single Threaded Normal C++ Loop Time Taken : " << time2.count() << "\n";
    // Addition Factor
    std::cout << "Speed up Factor " << (float)time2.count()/addition_time * 1.0f << " \n";

    // Subtraction AVX2
    std::cout << "For Subtraction\n";
    std::function<void()> func_sub = [ObjectPtr = &g1] { ObjectPtr->sub_arrays(); };
    long long sub_time = timeFunction(func_sub);
    std::cout << "For Our Vectorised Loop The Time Taken :" << sub_time << "\n";

    // Subtraction Normal
    t3 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<100000000;i++){
        x3[i] = x1[i] - x2[i];
    }
    t4 = std::chrono::high_resolution_clock::now();
    time2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
    std::cout << "For a Single Threaded Normal C++ Loop Time Taken : " << time2.count() << "\n";
    // Sub Factor
    std::cout << "Speed up Factor " << (float)time2.count()/sub_time * 1.0f << " \n";

    // Multiplication AVX2
    std::cout << "For Multiplication\n";
    std::function<void()> func_mul = [ObjectPtr = &g1] { ObjectPtr->mul_arryas(); };
    long long mul_time = timeFunction(func_mul);
    std::cout << "For Our Vectorised Loop The Time Taken :" << sub_time << "\n";

    // Multiplication Normal
    t3 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<100000000;i++){
        x3[i] = x1[i] * x2[i];
    }
    t4 = std::chrono::high_resolution_clock::now();
    time2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
    std::cout << "For a Single Threaded Normal C++ Loop Time Taken : " << time2.count() << "\n";
    // Mul Factor
    std::cout << "Speed up Factor " << (float)time2.count()/mul_time * 1.0f << " \n";


    // Division AVX2
    std::cout << "For Division\n";
    std::function<void()> func_div = [ObjectPtr = &g1] { ObjectPtr->divide_arrays(); };
    long long div_time = timeFunction(func_div);
    std::cout << "For Our Vectorised Loop The Time Taken :" << sub_time << "\n";

    // Division Normal
    t3 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<100000000;i++){
        x3[i] = x1[i] / x2[i];
    }
    t4 = std::chrono::high_resolution_clock::now();
    time2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
    std::cout << "For a Single Threaded Normal C++ Loop Time Taken : " << time2.count() << "\n";
    // div Factor
    std::cout << "Speed up Factor " << (float)time2.count()/div_time * 1.0f << " \n";

    return EXIT_SUCCESS;
}



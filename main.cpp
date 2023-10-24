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
//    auto t1 = std::chrono::high_resolution_clock::now();
//    g1.add_arrays();
//    auto t2 = std::chrono::high_resolution_clock::now();
//    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::function<void()> func = [ObjectPtr = &g1] { ObjectPtr->add_arrays(); };
    long long x = timeFunction(func);

    std::cout << "For Our Vectorised Loop The Time Taken :" << x << "\n";


    auto t3 = std::chrono::high_resolution_clock::now();
    std::vector<float> x3(100000000);
    for(int i=0;i<100000000;i++){
        x3[i] = x1[i] + x2[i];
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
    std::cout << "For a Single Threaded Normal C++ Loop Time Taken : " << time2.count() << "\n";
    return EXIT_SUCCESS;
}



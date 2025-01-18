#include <iostream>
#include <cassert>
#include <chrono>
#include <vector>
#include <algorithm>
#include "FuncClass.h"

void testFuncA() {
    FuncClass funcClass;

    // Test case 1: n = 0, x = 0
    std::cout << "Running Test case 1" << std::endl;
    assert(funcClass.FuncA(0, 0) == 1.0);
    std::cout << "Test case 1 passed." << std::endl;

    // Test case 2: n = 1, x = 1
    std::cout << "Running Test case 2" << std::endl;
    assert(funcClass.FuncA(1, 1) == 1.0);
    std::cout << "Test case 2 passed." << std::endl;

    // Test case 3: n = 2, x = 1
    std::cout << "Running Test case 3" << std::endl;
    assert(funcClass.FuncA(2, 1) == 2.0);
    std::cout << "Test case 3 passed." << std::endl;

    // Test case 4: n = 3, x = 1
    std::cout << "Running Test case 4" << std::endl;
    assert(funcClass.FuncA(3, 1) == 2.5);
    std::cout << "Test case 4 passed." << std::endl;

    // Test case 5: n = 4, x = 1
    std::cout << "Running Test case 5" << std::endl;
    assert(funcClass.FuncA(4, 1) == 2.6666666666666665);
    std::cout << "Test case 5 passed." << std::endl;
}

void testLongComputation() {
    FuncClass calculator;

    std::vector<double> aValues;
    aValues.reserve(2000000); // Pre-allocate memory

    auto t1 = std::chrono::high_resolution_clock::now();

    // Generate values using FuncA with different x inputs
    for (int i = 0; i < 2000000; i++) {
        double x = i * 0.001; // Increment x by small amounts
        aValues.push_back(calculator.FuncA(5, x)); // Use 5 terms for Taylor series
    }

    for (int i = 0; i < 500; i++) {
        std::sort(begin(aValues), end(aValues));
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    int iMS = int_ms.count();
    std::cout << "Long computation test took " << iMS << " milliseconds." << std::endl;
}

int main() {
    std::cout << "Starting tests..." << std::endl;
    testFuncA();
    testLongComputation();
    std::cout << "All tests passed." << std::endl;
    return 0;
}

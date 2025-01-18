#include <iostream>
#include <cassert>
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

int main() {
    std::cout << "Starting tests..." << std::endl;
    testFuncA();
    std::cout << "All tests passed." << std::endl;
    return 0;
}

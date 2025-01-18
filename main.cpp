#include <iostream>
#include "FuncClass.h"

int main() {
    FuncClass obj;
    int n = 10; // Number of terms
    double x = 1.0; // Exponent
    std::cout << "FuncA result: " << obj.FuncA(n, x) << std::endl;
    return 0;
}

#include "fibonacci.h"

int fibonacci() {

    int n = 25;
    int t1 = 0;
    int t2 = 1;
    int nextTerm = 0;
    int i = 1;

    //std::cout << "Enter the number of terms: ";
    //std::cin >> n;

    //std::cout << "Fibonacci Series: ";

    while (i < n) {
        if (i == 1) {
            //std::cout << t1 << ", ";
        }
        else if (i == 2) {
            //std::cout << t2 << ", ";
        }
        else
        {
            nextTerm = t1 + t2;
            t1 = t2;
            t2 = nextTerm;
            //std::cout << nextTerm << ", ";
        }
        i = i + 1;
    }
    return 0;
}
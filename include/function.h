// function.h
#ifndef FUNCTION_H
#define FUNCTION_H
#define _USE_MATH_DEFINES 

enum function_to_integrate
{
    func_1 = 1,
    func_2,
    func_3,
    func_4,
    func_5,
};

#include <math.h>
double f1(double x) {
    return (pow(x, 2) + pow(M_E, x))/(pow(x, 3) + 3 * pow(M_E, x));  
}

double f2(double x) {
    return (x * atanl(4 * x));  
}

double f3(double x) {
    return (pow(sin(x / 4), 2) * pow(cos(x / 4), 2));  
}

double f4(double x) {
    return (1 / (pow(x, 2 / 3) + 2* pow(x, 1 / 2)));  
}

double f5(double x) {
    return ((pow(x, 3) + 2 * pow(x, 2) - 5 * x + 7)/(pow(x, 3) - 2 * pow(x, 2) + x));  
}
#endif // FUNCTION_H

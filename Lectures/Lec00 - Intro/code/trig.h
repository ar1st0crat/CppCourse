#include <iostream>

//  ================= Пример inline-функции ===================
inline
double trigomagic(double x)
{
    return pow(sin(x), 2) + pow(cos(x), 2);
}

// компилятор генерирует другой код для таких функций (если получится)



void trigo_iteration()
{
    static double x = 0.0;          // пример static-переменной

    std::cout << x << std::endl;

    x += 0.1;
}

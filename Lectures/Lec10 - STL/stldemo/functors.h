#pragma once

#include <functional>


// Функция (константа "4" прошивается в коде)

bool findNum(std::pair<const int, int>& x)
{
    return x.second == 4;
}

// Ниже описываются способы, как можно параметр в функцию передавать (из другой функции), а не прошивать.
// До С++11 для этого можно применять только функторы;
// начиная с С++11 можно пользоваться std::bind() для преобразования самих функций


// ПЕРВЫЙ способ: унарный функтор с параметром-членом структуры

// унарный функтор вызывается так на каждом элементе контейнера:
// foo(pair_1)      // параметр 4 хранится в состоянии объекта
// foo(pair_2)
// ...
// foo(pair_N)

struct NumFinder : public std::unary_function<std::pair<const int, int>, bool>
{
    int param_;

    bool operator()(std::pair<const int, int>& num_pair)
    {
        return num_pair.second == param_;
    }
};


// ВТОРОЙ способ: бинарный функтор с параметром функции (вторым)

// бинарный функтор вызывается так на каждом элементе контейнера:
//foo(pair1, 4)
//foo(pair2, 4)
//foo(pair3, 4)

// вопрос: как указать алгоритму, что второй параметр должен подаваться в функцию?
// ответ - смотри в вызове самого алгоритма и функции std::bind2nd()

struct NumBinFinder : public std::binary_function<std::pair<const int, int>, int, bool>
{
    bool operator()(std::pair<const int, int>& num_pair, int x) const
    {
        return num_pair.second == x;
    }
};


// функция (для демонстрации алгоритма std::count_if)
bool isNegative(int elem)
{
    return elem < 0;
}

// функтор (для демонстрации алгоритма std::count_if)
struct NegativeCounter : std::unary_function<int, bool>
{
    bool operator()(int elem)
    {
        return elem < 0;
    }
};

void print(int x)
{
    std::cout << x << " ";
}

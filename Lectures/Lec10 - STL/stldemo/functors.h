#pragma once

#include <string>
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

// Person засветится как в демонстрации векторов,
// так и в демонстрации ассоциативных контейнеров

class Person
{
public:
    Person(std::string name, int age) : name_(name), age_(age)
    {
    }

    // это нужно, чтобы Person мог быть использован
    // в качестве ключа в unordered_map

    friend bool operator==(const Person& lhs, const Person& rhs);
    friend struct std::hash<Person>;

    // и оператор "меньше", если в обычном мэпе:
    friend bool operator<(const Person& lhs, const Person& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Person& p);

protected:
    std::string name_;
    int age_;
};


bool operator==(const Person& lhs, const Person& rhs)
{
    return lhs.name_ == rhs.name_ && lhs.age_ == rhs.age_;
}

bool operator<(const Person& lhs, const Person& rhs)
{
    return lhs.name_ < rhs.name_;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << p.name_ << " (" << p.age_ << " years old)";
    return os;
}

// custom specialization of std::hash can be injected in namespace std
namespace std
{
    template<>
    struct hash<Person>
    {
        typedef Person argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& s) const
        {
            result_type const h1 ( std::hash<std::string>{}(s.name_) );
            result_type const h2 ( std::hash<int>{}(s.age_) );
            return h1 ^ (h2 << 1);
        }
    };
}

// custom hash can be a standalone function object:
//struct MyHash
//{
//    std::size_t operator()(Person const& p) const
//    {
//        std::size_t h1 = std::hash<std::string>{}(p.name_);
//        std::size_t h2 = std::hash<int>{}(p.age_);
//        return h1 ^ (h2 << 1);
//    }
//};

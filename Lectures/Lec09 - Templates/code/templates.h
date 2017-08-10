#include <iostream>
#include <typeinfo>

// ======================== пример шаблонной функции
template <typename T>
bool startsWith(T* arr, T elem)
{
    return arr[0] == elem;
}

// ===================== явная специализация для символов
// ===================== (добавлен функционал регистронезависимости)
template <>
bool startsWith(char* arr, char elem)
{
    return ::toupper(arr[0]) == ::toupper(elem);
}


// ============================ пример шаблонного класса
template <class T, int N>
class Container
{
public:
    void print()
    {
        std::cout << N << " " << typeid(T).name() << std::endl;
    }

protected:
    T a_[N];
};

// ======================== пример №1 частичной специализации
template <int N>
class Container<int, N>
{
public:
    void print()
    {
        std::cout << N << " integers!" << std::endl;
    }

protected:
    int a_[N];
};


//
// Generic programming
// SFINAE       Substitution
//              Failure
//              Is
//              Not
//              An
//              Error
//


// ======================= пример №2 частичной специализации
template <typename T>
struct Get
{
    const static int Size = sizeof(T);
};

// для всех указателей компилятор будет подставлять именно эту версию структуры

template <typename T>
struct Get<T*>
{
    const static int Size = 0;

    void printYear()
    {
        T obj;

        // и только уже дойдя до этого места, компилятор
        // выдаст ошибку, если у типа T нет age
        std::cout << "Year: " << obj.getYear() << std::endl;
    }
};


// Своя версия трейтов

template <class T>
struct type_trait
{
    const static bool isIntegral = false;
};

template <>
struct type_trait<int>
{
    // typedef нужен для SFINAE (вводится только в int-овой и short-овой специализациях)
    typedef int integral_type;
    // эту константу также можно использовать в каких-либо целях
    const static bool isIntegral = true;
};

template <>
struct type_trait<short>
{
    typedef short integral_type;
    const static int isIntegral = true;
};

// данная функция будет считаться компилятором подходящей только для тех типов,
// в которых объявлен тип integral_type
template <typename T>
void printNumber(T elem, typename type_trait<T>::integral_type flag = 0)
{
    std::cout << elem << std::endl;
}
// Примечание: ноль в суффиксе "= 0" не играет никакой роли (можно хоть 500 написать)
// Главное здесь - в сигнатуру метода добавить нечто сигнальное, чтобы компилятор не пропустил
// в случае нарушения каких-то условий. С другой стороны, чтобы printNumber() можно
// было вызывать без второго чисто вспомогательного параметра, мы ему даем значение по умолчанию.


// ====================== Еще примеры шаблонов и метапрограммирования

// =========================================== Ex.1 (classic example)

/* this is taken when I is even */
template<int I>
void center(char(*)[I % 2 == 0] = 0)
{
    std::cout << "EVEN!" << std::endl;
}

/* this is taken when I is odd */
template<int I>
void center(char(*)[I % 2 == 1] = 0)
{
    std::cout << "ODD!" << std::endl;
}


// ================================== Ex.2 (even more classic example)
template <int N>
struct Factorial
{
    enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0>
{
    enum { value = 1 };
};



class Book
{
public:
    Book() : year_(2000), name_("")
    {

    }

    short getYear() const
    {
        return year_;
    }

protected:
    std::string name_;
    short year_;
};

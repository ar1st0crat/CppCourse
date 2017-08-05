#pragma once

#include <iostream>
#include "driver.h"
#include "operator.h"

// Предположим, что мы осознали необходимость в таком хитром классе,
// как "Водитель-оператор" (он сам себе и водитель, и оператор, и
// имеет некоторые тонкости в своей реализации,
// например, по-другому будет принимать и обрабатывать заказы)

class DriverOperator : public Driver, public Operator
{
    // вот эта секция:
    //
    // protected:
    //     std::string name_;
    //     std::string phone_;
    //     tm reg_date_;
    //     bool is_on_trial_;
    //
    // продублируется от Водителя и от Оператора
};


/*
    // Чтобы избежать этого дублирования (a.k.a. diamond problem),
    // используется виртуальное наследование:

class Driver : virtual public Employee
{
    //...
};

class Operator: virtual public Employee
{
    // ...
};

    // Но вообще множественное наследование реализации не рекомендуется
    // и в C# и Java, например, его вообще попросту нет

*/



// Виды наследования:

// 1) публичное (открытое)
//    class B: public A
//		в потомке B родительские спецификаторы доступа из A останутся как есть

// 2) защищенное
//    class B: protected A
//		в потомке B все публичное родительское из А станет protected

// 3) приватное (закрытое)
//    class B: private A
//		в потомке B все родительское из A станет закрытым

// Виды 2 и 3 довольно специфичны
// в С# и Java, например, их вообще и нет

class Base
{
public:
    int x_;
protected:
    int y_;
private:
    int z_;

public:
    Base() : x_(1), y_(2), z_(3)
    {
    }
};

class PrivatelyInherited : private Base
{
public:
    // здесь будет все нормально ...
    void print()
    {
        std::cout << x_ << " " << y_;
    }

// ... но данные станут вот такими:
//
// private:
//    int x_;
//    int y_;
//    int z_;

// из main(), например, уже доступа к x_ не будет

// более того! вообще ни к каким методам и данным из родительского класса доступа не будет

};



// См. финальные строчки main() в поисках того, что мы с ним делать будем ))

class EasyToHack
{
public:
    EasyToHack() : foo_(100), bar_(3.14)
    {
    }

    void print() const
    {
        std::cout << foo_ << " " << bar_ << std::endl;
    }

private:
    int foo_;
    double bar_;
};

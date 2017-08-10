#include <iostream>

// ================= Примеры макросов: =================

#define OUT std::cout <<
#define NEWLINE std::cout << std::endl

#define SHOW(S) std::cout << S

#define SUM(a, b) (a + b)

#define QNAME(ns, name) ns::name

#define interface struct

#define EMPTY_CLASS(NAME) class NAME { public: virtual~NAME() {} }

#define implements : public
#define and_implements , public
#define inherits : public

// =====================================================

// сделаем пустой класс с помощью наших макросов...

EMPTY_CLASS(Object);

// ...и интерфейс

interface IDemo
{
    virtual ~IDemo() {}
    virtual void demo() = 0;
};


// о как

class Cool inherits Object and_implements IDemo
{
public:
    void demo()
    {
        std::cout << "macro demo" << std::endl;
    }
};


void macro_demo()
{
    OUT "Hello World!\n";

    SHOW("Yes!\n");

    int res = SUM(2, 3) * SUM(5, 7);

    OUT res;

    NEWLINE;

    QNAME(std, cout) << "OK!" << QNAME(std, endl);

    Object obj;

    Object* o = new Cool;
    delete o;

    Cool cool;
    cool.demo();
}

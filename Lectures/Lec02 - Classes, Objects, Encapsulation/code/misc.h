#include <iostream>

class Empty
{
};

// 1) ради интереса - сколько байт занимает объект пустого класса?
//    Ответ: 1 байт

// 2) он таки пустой-пустой?
//    Ответ: нет, для любого класса компилятор создает автоматически 4 метода
//           (если программист не написал их сам):

/*
class Empty
{
public:
    // 1) конструктор по умолчанию
    Empty();

    // 2) копирующий конструктор
    Empty(const Empty& empty);

    // 3) оператор присваивания
    Empty& operator=(const Empty& empty);

    // 4) деструктор
    ~Empty();

    // в c++11 создаются еще 2 метода с move-семантикой:
    // 5)
    Empty(Empty&& empty);
    // 6)
    Empty& operator=(Empty&& empty);
};
*/



class GlobalScreen
{
public:
    static void hello()
    {
        std::cout << "Hello!" << std::endl;
    }

    static void bye()
    {
        std::cout << "Bye!" << std::endl;
    }

private:
    GlobalScreen();
    // конструктор в секции private - принципиально запрещаем создавать
    // объект класса GlobalScreen где бы то ни было
};



class Quiz
{
public:
    Quiz()
    {
        Quiz(25);   // компилируется, но смысла не имеет,
                    // т.к. просто будет создан на стеке временный объект Quiz
                    // и тут же уничтожится
    }

    Quiz(int n) : number_(n)
    {
    }

public:
    // отличается ли чем-то метод класса, тело которого
    // написано прямо в определении класса?
    double avg(double x, double y)
    {
        return (x + y)/ 2;
    }

    // Ответ: да;
    // в этом случае компилятор будет пробовать делать этот метод inline

private:
    int number_;
};

#include <iostream>
#include "car.h"
#include "truck.h"
#include "misc.h"

int main()
{
    // демонстрация подкласса на примере класса Car
    {
        Car car("Toyota", "Lexus", "a965ea", Color::WHITE, 2013);

        // =================== последовательность вызова конструкторов:
        // -> car.Vehicle();
        // -> car.Car();
        // ================= деструкторы вызываются в обратном порядке

        car.print();      // print() достался от базового Vehicle
    }

    std::cout << std::endl;

    // демонстрация доопределения, переопределения с помощью класса Truck
    {
        Truck truck;

        // у Truck есть свои методы в дополнение к методам родителя
        // Например, сеттер маскимального веса. Это *доопределение*
        truck.setMaxWeight(1500);

        // Truck определяет свою версию print()
        // это *переопределение* (не путать с сокрытием)
        truck.print();

        // а так мы можем доступиться до родительского print()
        // (равно как и до любых публичных данных родителя)
        truck.Vehicle::print();


        // демо проблемного участка
        // (переопределение Vehicle::color_ в подклассе Truck)
        // truck.repaint() затронет родительский (Vehicle) color_!

        truck.repaint(Color::GREEN);

        if (truck.getColor() == Color::GREEN)
        {
            std::cout << "The truck is green now!" << std:: endl;
        }
        else
        {
            std::cout << "The truck is NOT green!" << std:: endl;
        }

        if (truck.Vehicle::getColor() == Color::GREEN)
        {
            std::cout << "The truck's parent is green now!" << std:: endl;
        }
        else
        {
            std::cout << "The truck's parent is NOT green!" << std:: endl;
        }
    }

    std::cout << std::endl;

    // демонстрация сокрытия с помощью классов Operator и Employee
    {
        std::time_t now = std::time(0);
        tm time = *localtime(&now);

        Operator sidorova("Sidorova A.E.", "000-111-22-33", time);
        sidorova.setId(17614);

        // Т.к. есть using, то print() сотрудника "просочился" в неймспейс оператора
        sidorova.print(true);

        std::cout << std::endl << "Print as employee:" << std::endl;

        sidorova.print();
        // без using внутри Operator тут будет ошибка
    }

    std::cout << std::endl;



    // демонстрация результата private-наследования

    PrivatelyInherited demo;

    // есть доступ только к методу print()
    demo.print();


    std::cout << std::endl;


    // ============================== Эй хакнем! ============================

    EasyToHack lolkek;
    lolkek.print();

    // lolkek.foo_ = 300;         // не получится
    // lolkek.bar_ = 6.28;     // не получится

    // а так:
    int* iptr = (int*)&lolkek;

    *iptr = 300;        // !

    iptr++;             // смещаемся дальше на размер инта
    iptr++;             // вопрос на засыпку: а еще раз зачем???

    double* dptr = (double*)iptr;
    *dptr = 6.28;

    lolkek.print();

    return 0;
}

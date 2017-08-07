#include <iostream>
#include <typeinfo>
#include "driver.h"
#include "operator.h"


// тела будут ниже
int library_function(std::string& s);
void our_function(const std::string& s);


int main()
{
    // Механизмов т.н. рефлексии С++ "из коробки" не дает,
    // но какую-никакую интроспекцию осуществить можно

    // 2 способа:

    // 1) оператор typeid, структура type_info
    // 2) динамический каст dynamic_cast<>


    // Поработаем еще с массивчиком из прошлой лекции:

    Operator ivanova("Ivanova A.E.");

    const Vehicle car("Ford", "Focus", "x276ae", Color::WHITE, 2011);

    Employee* employees[4] =
    {
        new Employee("Vasechka"),
        new Operator("Johnny"),
        new Driver("Eddie", car),
        &ivanova
    };


    // Можно ли динамически узнать, на объект какого типа в хипе указывает каждый указатель?

    // Воспользуемся typeid...

    // но такой код ничего нам не дает:

    for (std::size_t i = 0; i < 4; ++i)
    {
        std::cout << typeid(employees[i]).name() << std::endl;
        std::cout << typeid(employees[i]).__is_pointer_p() << std::endl;
    }


    // а такой - вуаля!

    for (std::size_t i = 0; i < 4; ++i)
    {
        std::cout << typeid(*employees[i]).name() << std::endl;
        std::cout << typeid(*employees[i]).__is_pointer_p() << std::endl;
    }


    for (std::size_t i = 0; i < 4; ++i)
    {
        Driver* driver = dynamic_cast<Driver*>(employees[i]);

        if (driver)
        {
            std::cout << driver->getName() << " drives " << driver->getVehicle()->getModel() << std::endl;
        }
        else
        {
            std::cout << employees[i]->getName() << " is not a driver" << std::endl;
        }
    }


    // "А нужна ли вообще аналитика?" (с) Галыгин и Харламов
    // а нужен ли вообще dynamic_cast<>, если можно сделать так в сишном стиле:

    Driver* vodila = (Driver*)employees[2];         // тут таки водитель
    std::cout << vodila->getName() << std::endl;

    // Да, здесь нам повезло.

    // Впрочем, первая строчка никогда не таит опасности,
    // а вот - вторая может подкинуть проблем

    vodila = (Driver*)employees[1];                 // тут оператор
    std::cout << vodila << std::endl;

    // выводит какой-то адрес, но не ноль!
    // т.е. каст "типа произошел", но доступ по указателю к данным именно водительской части
    // вышвырнет нас куда подальше

    // std::cout << vodila->getVehicle()->getModel() << std::endl;




    // Указатель может быть 0/nullptr, а если работаем с ссылками?

    Driver jason_statham("Jason Statham");
    Employee& employee1 = jason_statham;

    Operator penny("Penny");
    Employee& employee2 = penny;

    // здесь все нормально
    Driver& d = dynamic_cast<Driver&>(employee1);
    std::cout << d.getName() << std::endl;

    // а здесь никакие проверки не помогут,
    // т.к. каст бросит исключение bad_cast;
    // исключение надо перехватывать (об исключениях - через лекцию)

    // d = dynamic_cast<Driver&>(employee2);




    // ======================== Семейство cast-ов в С++ =======================

    // static_cast<> - делает преобразование еще на этапе компиляции
    //
    // это самый безопасный каст из всех,
    // т.к. ошибка не позволит даже скомпилироваться программе

    int pi = static_cast<int>(3.1415);
    std::cout << pi << std::endl;

    // сишный статический каст более опасен:

    int hun = 100;

    // тут ошибки не всплывет (и плохо)
    double* ptr = (double*)&hun;

    // здесь вылетим, потому что указатель проброшен на 4-байтовую область
    // а сам указатель - на double, т.е. будет попытка записать 8 байт на место четырех

    // *ptr = 45.56;


    // а статик_каст не скомпилируется здесь (и хорошо):
    // int *ptr = static_cast<int*>(&e);


    // для иерархий классов-подклассов статик_каст использовать не надо!
    // в данном случае все будет нормально,
    // но и статик_каст на другой подкласс тоже пройдет успешно
    // и вылетим уже потом при доступе

    // ========================================================= не надо так
    vodila = static_cast<Driver*>(employees[2]);
    std::cout << vodila->getVehicle()->getModel() << std::endl;
    // ========================================================= не надо так


    // демонстрация const_cast
    // возможное применение - снять константность/волатильность с указателя/ссылки,
    // если какая-то внешняя 3rd-party функция прнимает не константный параметр

    our_function("Hello world!");


    // демонстрация reinterpret_cast

    int chars = 0x61626364;

    // трактуем int как последовательность 4 char-ов

    char* str = reinterpret_cast<char*>(&chars);
    for (std::size_t i = 0; i < 4; ++i)
    {
        std::cout << str[i] << std::endl;
    }

    // little-endian



    // подчистим память
    for (std::size_t i = 0; i < 4; ++i)
    {
        delete employees[i];
    }

    return 0;
}


// чтобы вызвать эту функцию, нужно подать ссылку не константную строку
int library_function(std::string& s)
{
    return s.length();
}

// а у нас, допустим, она константная
// значит, надо явно снять константность
void our_function(const std::string& s)
{
    std::string& tmp = const_cast<std::string&>(s);
    int n = library_function(tmp);
    std::cout << n << std::endl;
}

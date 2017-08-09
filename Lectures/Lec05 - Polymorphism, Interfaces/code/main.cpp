#include <iostream>
#include "taxigeoservice.h"
#include "operator.h"
#include "driver.h"


// тело будет ниже, после функции main()
void showObjectAddress(IPrintable& printable);


int main()
{
    // ======================== PART 1 =========================
    // ===================== ПОЛИМОРФИЗМ =======================
    // =========================================================

    Employee emp("Somebody 2 luv", "000-888-77-22", tm());
    Operator ivanova("Ivanova A.E.", "000-555-88-99", tm());

    // здесь уже на этапе компиляции понятно,
    // метод какого класса будет вызываться:

    std::cout << "Employee's bonus: " << emp.salaryBonus(1000) << std::endl;
    std::cout << "Operator's bonus: " << ivanova.salaryBonus(1000) << std::endl;


    // а теперь морально готовимся к полиморфизму:
    Employee* employee = new Employee("Somebody 2 luv", "000-111-22-23", tm());
    Employee* petrova = new Operator("Petrova A.E.", "000-111-22-33", tm());

    // Внимательно! Тут написано что-то новенькое:
    //
    //      Employee* X = new Operator Y;
    //
    // Т.е. тип слева и справа от оператора присваивания разный


    // Но так написать нельзя:
    //
    // Operator* person = new Employee;
    //
    // Чтобы понять почему так, просто вспомним, как в памяти хранится
    // родитель и подкласс


    // ... Прэподаватель рисует на доске напоминание ...



    // Благодаря полиморфизму, выведутся разные надбавки к зарплате
    // (здесь результат такой же, как и выше, но по совершенно другой причине!
    //  здесь только во время ВЫПОЛНЕНИЯ программы бло решено, какой метод вызвать)

    std::cout << "Employee's bonus: " << employee->salaryBonus(1000) << std::endl;
    std::cout << "Operator's bonus: " <<  petrova->salaryBonus(1000) << std::endl;


    // Однакож, если метод не будет помечен как virtual, то полиморфизма не будет!
    // и будет вызываться метод класса Employee в обоих случаях.
    // Специально для демо мы сделали benefit() не виртуальным, а обычным

    std::cout << "Employee's benefits: " << employee->benefits() << std::endl;
    std::cout << "Operator's benefits: " <<  petrova->benefits() << std::endl;

    // Если что, в Java слово virtual не нужно,
    // потому что ВСЕ методы класса там являются виртуальными по умолчанию



    // Еще раз приведем в порядок мысли:

    // 1) virtual делает метод полиморфным,
    //    но если метод вызывается на стековых объектах, полиморфизма не будет
    //    (будет работать механизм простого переопределения метода)

    // 2) если метод не помечен как virtual,
    //    то вызывающий класс будет определен еще на этапе компиляции
    //    на основании типа, стоящего ДО оператора присваивания



    // стандартная для универов по всему миру демонстрация полиморфизма
    // на примере массива из указателей:
    Employee* employees[4] =
    {
        new Employee("Vasechka"),
        new Operator("Johnny"),
        new Driver("Eddie"),
        &ivanova
    };

    std::cout << "Bonuses for 1) Vasechka, 2) Johnny, 3) Eddie, 4) Ivanova" << std::endl;

    for (std::size_t i = 0; i < 4; ++i)
    {
        std::cout << "Bonus " << i+1 << ": " << employees[i]->salaryBonus(1000) << std::endl;
    }

    // привент зе мемори лик
    for (std::size_t i = 0; i < 4; ++i)
    {
        delete employees[i];
    }

    // Полиморфизм будет происходить и с ссылками (&) :
    // Driver driver;
    // Employee& employee = driver;
    // std::cout << employee.salaryBonus(1000) << std::endl;



    // а теперь убедимся, что таблицы виртуальных функций таки существуют:

    class A
    {
    public:
        void foo();
    };

    class ASubclass : public A {};

    class VirtualA
    {
    public:
        virtual void foo() {}
    };

    // любой подкласс также получает доп. указатель
    class VirtualASubclass : public VirtualA {};

    std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
    std::cout << "sizeof(ASubclass) = " << sizeof(ASubclass) << std::endl;
    std::cout << "sizeof(VirtualA) = " << sizeof(VirtualA) << std::endl;
    std::cout << "sizeof(VirtualASubclass) = " << sizeof(VirtualASubclass) << std::endl;



    // ======================= PART 2 ==========================
    // ========== Демонстрация абстрактного класса =============
    // =========================================================

    std::cout << std::endl << "GeoService abstract class demo" << std::endl;

    TaxiGeoService geo_service({41.523, 23.872});

    TaxiGeoService::Position position =
            geo_service.addressToPosition("Donetsk, Artema, 500");

    std::cout << position.langitude << " " << position.latitude << std::endl;

    // так не получится (и правильно):
    // 1) GeoService gs;                        // ни так
    // 2) GeoService* gs = new GeoService;      // ни так


    // так нормально:

    GeoService* gs = new TaxiGeoService({41.523, 23.872});

    std::string* addresses = gs->makeRoute("Donetsk, DonNU", "Donetsk, DonNTU");

    std::cout << addresses[0] << " -> " << addresses[1] << std::endl;

    delete []addresses;     // довольно неприятный момент -
                            // вытекание ресурса из метода наружу
                            // (лечится разными способами, об этом - не сейчас)
    delete gs;


    // и так нормально:

    GeoService& service = geo_service;
    std::cout << service.calculateDistance("Donetsk, DonNU", "Donetsk, DonNTU") << " km" << std::endl;

    //
    // Т.е. создать можно только какую-то реализацию абстракции (ее конкретное наполнение)
    // ==================================================================================




    // ======================= PART 3 ==========================
    // ========== Демонстрация интерфейса IPrintable ===========
    // =========================================================

    std::cout << std::endl << "IPrintable interface demo" << std::endl;

    Driver* vasya = new Driver("Vasya");

    Vehicle car("Ford", "Focus", "x915ae", Color::WHITE, 2012);

    showObjectAddress(ivanova);
    showObjectAddress(*vasya);
    showObjectAddress(car);


    // а эти не скомпилируются, потому что мы не обозначили, что
    // в классах Employee и TaxiGeoService есть функционал вывода на экран
    // (они не реализуют интерфейс IPrintable)

    // show_object_address(*employee);
    // show_object_address(*petrova);
    // show_object_address(geo_service);

    // Подумайте, а чем petrova то провинилась? ))


    delete employee;
    delete petrova;
    delete vasya;



    // Бонус: нюанс с закрытым наследованием
    // Предположим, у нас есть такие классы:
    /*
        class Parent
        {
            // ...
        };

        class Child: private Parent
        {
             // ...
        };

        В клиентском коде
        компилятор даже не даст написать так:

        Parent* c = new Child;

        // подумайте, почему
     */


    return 0;
}


// вот эта функция, которая принимает любой принтэбл объект

void showObjectAddress(IPrintable& printable)
{
    std::cout << " === The object === " << std::endl;
    printable.print();

    std::cout << " === has address === " << std::endl;
    std::cout << &printable << std::endl << std::endl;
}


    // ================================================ In general:
    // Polymorphism:
    //
    // 1. Subclass polymorphism
    // 2. Function overload:    print()   print(std::string header)
    //							  =>	    =>
    //                          print()   print("aaa");
    // 3. int x = 2 + 3
    //    Point p = p1 + p2;
    // 4. C++ Templates
    // ============================================================


/*
 *
 * еще пример интерфейса:
 *
 *
enum FileFormat
{
    TXT,
    XML,
    JSON
};

// Интерфейс конвертирования файлов одного формата в другой

class IFileConverter
{
    virtual void convert(FileFormat inFormat, FileFormat outFormat) = 0;
    virtual void save() = 0;
    virtual ~IFileConverter() {}
};
*/

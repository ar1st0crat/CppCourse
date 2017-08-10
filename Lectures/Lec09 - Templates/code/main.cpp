#include <iostream>
#include "macros.h"
#include "templates.h"
#include "vehicle.h"
#include "booking.h"
#include "daytimecollection.h"

int main()
{
    // все демки по макросам собраны в этой функции:

    macro_demo();


    // демо по шаблонам:

    std::cout << std::endl << "Demo of templates and SFINAE:" << std::endl;

    // примеры вызовов шаблонной функции startsWith<T>

    int a[] = { 1, 2, 3, 4, 5 };
    if (startsWith(a, 1))
    {
        std::cout << "Array a starts with 1" << std::endl;
    }

    double b[] = { 1.0, 2.0, 3.0, 4., 5. };
    if (startsWith<double>(b, 1.0))
    {
        std::cout << "Array b starts with 1.0" << std::endl;
    }

    char s[] = "OK";
    if (startsWith(s, 'o'))
    {
        std::cout << "Array s starts with 'o'" << std::endl;
    }


    // примеры инстанцирования шаблонных классов

    Container<Book, 20> booklist;
    booklist.print();

    Container<double, 100> dlist;
    dlist.print();

    Container<int, 10> ilist;
    ilist.print();


    // пример с частичной специализацией для указателей (тип Т*) и SFINAE

    std::cout << "Size of short: " << Get<short>::Size << std::endl;
    std::cout << "Size of a pointer (should be zero): " << Get<int*>::Size << std::endl;


    Get<Book*> book_helper;
    book_helper.printYear();

    Get<Vehicle*> car_helper;
    car_helper.printYear();

    Get<Book> gb;            // у Get<Book> нет даже метода printYear()


    // еще демо SFINAE:

    printNumber(23);
    //printNumber(23.56);       // здесь компилятор выдаст ошибку


    std::cout << "center<12>(): ";
    center<12>();
    std::cout << "center<15>(): ";
    center<15>();

    std::cout << "6! = " << Factorial<6>::value << std::endl; // = 720
    std::cout << "0! = " << Factorial<0>::value << std::endl; // = 1

    std::cout << std::endl;


    // демонстрация нашего шаблонного контейнера DaytimeCollection

    std::tm time;
    time.tm_min = 30;
    time.tm_sec = 45;

    time.tm_hour = 20;
    Booking b1("Olimpiyskii", "Planetarium", time);

    time.tm_hour = 16;
    Booking b2("Cosmos Circus", "Kirshavel", time);

    time.tm_hour = 22;
    Booking b3("DonNU", "DonNMU", time);

    time.tm_hour = 6;
    Booking b4("Donbass Arena", "Railway Station", time);


    DaytimeCollection<Booking> bookings;

    bookings.add(b1);
    bookings.add(b2);
    bookings.add(b3);
    bookings.add(b4);

    std::cout << "=== Morning bookings: ===" << std::endl << std::endl;
    bookings.printMorningEntries();

    std::cout << "=== Day bookings: ===" << std::endl << std::endl;
    bookings.printDayEntries();

    std::cout << "=== Night bookings: ===" << std::endl << std::endl;
    bookings.printNightEntries();
}

# Лекция 9 - Шаблонные функции и классы, идиома SFINAE

План:

* Макросы
* Шаблонные функции
* Шаблонные классы, особенности наследования и static
* Явная специализация шаблона, частичная специализация шаблона
* SFINAE (**S**ubstitution **F**ailure **I**s **N**ot **A**n **E**rror)
* Traits
* Метапрограммирование


Примеры макросов (в том числе забавных) можно найти в файле ```macros.h```.

Примеры шаблонных функций и классов, явной и частичной специализации шаблонов, трейтов и метапрограммирования с помощью шаблонов, находятся в файле ```templates.h```.

В рамках проекта TaxiService написан шаблонный класс-контейнер **DaytimeCollection**. Это такой контейнер, который позволяет хранить любые объекты, но с автоматической их группировкой по времени суток (утренние, дневные, вечерние). Например, класс какого-то события, мероприятия, спортивного матча, заказа и т.д. Объект должен быть типа, предоставляющего метод ```std::tm getTime()```.

```C++
    // демонстрация шаблонного контейнера DaytimeCollection

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

```

Чтобы этот код скомпилировался, тип Т должен иметь метод ```std::tm T::getTime()```. [Есть более серьезные и правильные SFINAE-based способы проверки того, что тип Т содержит конкретный метод, но в данной лекции они не рассматриваются. Например, [Эрб Саттер предлагает трейты](http://www.gotw.ca/gotw/071.htm)]

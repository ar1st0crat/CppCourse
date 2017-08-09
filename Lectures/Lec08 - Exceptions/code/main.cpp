#include <iostream>
#include <typeinfo>
#include "operator.h"
#include "booking.h"
#include "wrongaddressexception.h"


// читаем https://isocpp.org/wiki/faq/exceptions


void exception_demo();

int main()
{
    // ======================================== Стратегии обработки ошибок

    // 1) Return Codes:

    // например, есть функция, которая может возвращать разные коды ошибок
    // openFile() ->
    //    const int FILE_SUCCESS = 0	- успешное открытие файла
    //    const int FILE_NOT_FOUND = 1	- файл не найден
    //    const int FILE_IS BUSY = 2	- файл занят
    //
    // int errno = openFile();

    // if (errno == FILE_NOT_FOUND)
    // {
    //	 // ...
    //	 return;
    // }
    // else if (errno == FILE_IS_BUSY)
    // {
    // 	 // ...
    //	 return;
    // }

    // при этом, куски кода, которые подчищают память и делают
    // другую подчищающую работу, могут дублироваться (а это не DRY)

    // Также неудобно, если вызывались вложенные функции
    // и нужно при каком-то флаге во внутренней функции
    // сразу вернуться в самую "верхнюю" функцию


    // 2) Exceptions

    // демонстрация #1 работы с exception-ами
    // (механизм и синтаксис try..throw..catch)

    try
    {
        exception_demo();
    }
    catch (const int error)
    {
        std::cout << "Error " << error << std::endl;
    }
    catch (const char* message)
    {
        std::cout << message << std::endl;
    }
    catch (...)
    {
        std::cout << "Something mysterious happened!" << std::endl;
    }

    // ПРИМЕЧАНИЕ.
    // catch(int) и catch(double) - разные вещи! инт не поднимется до дабла автоматически!



    // демонстрация #2 работы с exception-ами
    // (исключения в более ООП-шном ключе)

    std::time_t now = std::time(0);
    Booking booking("address1", "address2", *localtime(&now));

    try
    {
        booking[0] = booking[5];

        std::cout << booking;
    }
    catch (std::out_of_range& exc)
    {
        std::cout << exc.what() << std::endl;
    }



    Employee petrov("Petrov A.E.");

    try
    {
        Operator& person = dynamic_cast<Operator&>(petrov);

        person.print();
        person.processBooking(tm());
    }
    catch (const std::bad_cast& ex)
    {
        std::cout << "Some problem!" << std::endl;
        std::cout << ex.what() << std::endl;
    }


    // а если не знаем или забыли, какое исключение
    // генерируется в этом случае? тогда можно перехватить
    // базовый std::exception по ссылке и заюзать RTTI:

    try
    {
        Operator& person = dynamic_cast<Operator&>(petrov);

        person.print();
        person.processBooking(tm());
    }
    catch (const std::exception& ex)
    {
        std::cout << typeid(ex).name() << std::endl;
        std::cout << ex.what() << std::endl;
    }



    // демонстрация #3 работы с exception-ами
    // (свое собственное исключение WrongAddressException)
    // (для примера. Можно было бы спокойно использовать std::invalid_argument)

    try
    {
        booking += "";              // бяка
        std::cout << booking;
    }
    catch (const WrongAddressException& wrong_address)
    {
        std::cout << wrong_address.what() << std::endl;
        std::cout << wrong_address.trace() << std::endl;
    }



    // ПРИМЕЧАНИЯ

    // В конструкторах исключение бросить можно, но объект не создастся до конца!
    // А если не создастся, то какой бы корректный деструктор ни был указан,
    // он просто не вызовется. Поэтому если в конструкторе до генерации исключения
    // будет выделена память, она никогда не освободится
    // (даже если исключение будет перехвачено корректно).

    /*
    Booking::Booking(const std::string addresses[],
                     std::size_t address_count,
                     tm time)
    {
        addresses_ = new std::string [address_count];       // если выделить память здесь, то при
                                                            // выбросе исключения, будет раскручен стек
                                                            // и произойдет мемори лик
        if (address_count < 2)
        {
            throw std::invalid_argument("There should be at least 2 addresses!")
        }

        for (std::size_t i = 0; i < address_count; ++i)
        {
            addresses_[i] = addresses[i];
        }

        address_count_ = address_count;
    }

        // [address_count >= 2]  -  это инвариант (условие в методе, которое должно строго выполняться);
        //                          проверку инварианта можно сделать исключениями или Return Code-ами;
        //                          с помощью assert(address_count >= 2) можно завершить программу при некорректных данных

    */



    // В деструкторах исключения бросать нежелательно!
    // Если исключения все-таки бросаются, то перехватывать нужно внутри же деструктора,
    // иначе оно уже нигде не перехватится, а вызовется завершение программы через std::terminate

    return 0;
}


// функции для демонстрации исключений в начале лекции

int inner_operation(int x, int y)
{
    if (y == 0)
    {
        throw "Zero argument!";     // можно бросать строки
    }
    return x / y;
}

void exception_demo()
{
    int x, y;

    std::cout << "Enter x: ";
    std::cin >> x;

    if (x == 0)
    {
        throw 0;        // в С++ можно бросать и числа
    }

    std::cout << "Enter y: ";
    std::cin >> y;

    int res = inner_operation(x, y);

    std::cout << "x / y = " << res << std::endl;
}


/*
// Код для демонстрации SEH
// (скомпилируется только майкрософтовским компилятором)

#include <stdexcept>
#include <windows.h>

void SEH_test()
{
    // ааа, это провокация!
    int* p = 0;

    __try
    {
        *p = 42;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "AAAAARGH! NULL!!!" << std::endl;
    }

    // обычным траем ничего не поймаем
}
*/


// еще интересный момент:
// catch (Exception& ex) -> все равно копия!

// почитать еще материал, так или иначе касающийся safe code:
// https://cwe.mitre.org/data/index.html  -  Code weaknesses

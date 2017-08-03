#include <iostream>
#include "booking.h"

int main()
{
    std::time_t now = std::time(0);

    tm time1 = *localtime(&now);    // 8:15:20
    time1.tm_hour = 8;
    time1.tm_min = 15;
    time1.tm_sec = 20;

    tm time2 = *localtime(&now);    // 9:44:32
    time2.tm_hour = 9;
    time2.tm_min = 44;
    time2.tm_sec = 32;


    Booking booking_artema("Artema Str., 516", "Artema Str., 100", time1);
    Booking booking_circus("Circus", "Planetarium", time2);


    // можно добавить еще адрес к заказу через операцию +=

    booking_circus += "Donbass Arena";


    booking_artema.print();
    booking_circus.print();


    // заказ можно инкрементировать;
    // смысл этой операции для заказа - перенести время заказа на 1 минуту

    Booking copy = ++booking_circus;

    std::cout << "Booking Circus -> ... has been altered to 1 minute later" << std::endl;

    booking_circus.print();
    copy.print();            // должно вывести то же самое



    // пункты-адреса заказа можно получать по индексу

    booking_circus[0] = booking_artema[1];

    std::cout << "Change address in booking Circus -> ..." << std::endl;
    booking_circus.print();


    // скомбинировать два заказа
    // (теперь заказ охватывает все адреса из заказа1 и заказа2)

    Booking booking = booking_artema + booking_circus;
    booking.print();


    // сравнить два заказа:
    // если заказ был сделан раньше, то он "меньше"

    if (booking_artema < booking_circus)
    {
        std::cout << "Booking Artema preceeds booking Circus" << std::endl;
    }
    else
    {
        std::cout << "Booking Circus preceeds booking Artema" << std::endl;
    }


    // Еще демо копи-конструктора, оператора присваивания и инкремента

    Booking tmp = booking_artema;
    tmp.print();

    tmp = booking_circus++;
    tmp.print();

    booking_circus.print();

    return 0;
}

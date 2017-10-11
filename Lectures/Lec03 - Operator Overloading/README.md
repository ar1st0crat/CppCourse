# Лекция 3 - Перегрузка операторов

План:

* Общий смысл перегрузки операторов
* Перегрузка операторов в виде методов класса и в виде глобальных функций
* Особенности возврата из функции копии, указателя и ссылки, RVO
* Перегрузка бинарных операторов на примере "+" и "<"
* Перегрузка оператора индексации "[]", обсуждение l-value
* Перегрузка префиксного и постфиксного инкремента/декремента
* Перегрузка оператора присваивания, идиома copy-and-swap
* Rule of Big Three


### Класс заказа Booking

В информацию о клиентском заказе у нас будет пока входить:

- массив адресов заказа *(в большинстве случаев адрес отправки и назначения, но могут быть и промежуточные пункты)*
- время отправки клиента
- время доставки клиента
- расстояние
- стоимость

*Примечание. Последовательность адресов кодируется пока что динамическим массивом. Так, конечно, не делается в нормальных проектах, но до знакомства с ```std::vector<std::string>``` пишем еще так. Также функцией этого динамического массива является демонстрация глубокого копирования.*

Вместо тысячи слов продемонстрируем пример использования класса с перегруженными операторами:


```C++
    Booking booking_artema("Artema Str., 516", "Artema Str., 100", time1);
    Booking booking_circus("Circus", "Planetarium", time2);


    // можно добавить еще адрес к заказу через операцию +=

    booking_circus += "Donbass Arena";

    // Аналогично можно было бы написать метод вроде такого:
    // booking_circus.addAddress("Donbass Arena");


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

```

![uml](https://github.com/ar1st0crat/CppCourse/blob/master/Lectures/Lec03%20-%20Operator%20Overloading/uml.png)

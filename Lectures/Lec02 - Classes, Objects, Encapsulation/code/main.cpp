#include <iostream>
#include <string>
#include "misc.h"
#include "driver.h"

int main()
{
    // ========================== PART 1 ===============================
    // Класс Car: демо конструкторов, сеттеров, const, mutable
    // =================================================================

    // 1) создаем ОБЪЕКТ unknown КЛАССА Car на стеке : вызовется конструктор без параметров
    Car unknown;

    // 2) создаем *константный* ОБЪЕКТ ford КЛАССА Car на стеке :
    //    вызовется основной параметризированный конструктор
    const Car ford("Ford", "Focus", "e888ap", Color::BLUE, 2010);

    // 3) создаем ОБЪЕКТ lada КЛАССА Car на стеке : вызовется конструктор с одним параметром (!)
    Car lada = 2015;

    // полностью эквивалентно такой записи (см. также explicit конструктор в классе Driver):
    // Car lada(2015);

    lada.setMake("LADA");
    lada.setModel("Kalina");
    lada.setNo("o379ac");
    lada.setColor(Color::RED);

    // так не получится, потому что данные - private:
    // lada.make_ = "LADA"
    // lada.model_ = "Kalina"
    // ...


    // 4) создаем константный ОБЪЕКТ lexus КЛАССА Car в хипе :
    //    вызовется основной параметризированный конструктор
    const Car* lexus = new Car("Toyota", "Lexus", "a777aa", Color::GRAY, 2011);

    // хоть lexus и константный объект,
    // но его color_ объявлен как mutable, а метод repaint() - с модификатором const,
    // поэтому можно вызвать этот метод:
    lexus->repaint(Color::WHITE);

    std::cout << std::endl;

    unknown.print();
    ford.print();
    lada.print();
    lexus->print();

    std::cout << std::endl;

    // еще можно так написать: на ходу создать объект класса и вызвать его метод
    Car().print();                                              // 1
    std::cout << std::endl;

    Car("VAZ", "2109", "c111cc", Color::BLACK, 2007).print();   // 2
    std::cout << std::endl;



    // ========================== PART 2 =================================
    // Класс Driver: демо explicit конструктора, статических членов и this
    // ===================================================================

    Driver ivanov("Ivanov", lada);
    ivanov.print();

    std::cout << "Two years later..." << std::endl;

    ivanov.setCar(*lexus);
    ivanov.print();

    Driver petrov("Petrov");  // создать объект можно только явным вызовом конструктора, т.к. он помечен explicit!

                              // вот так уже не сойдет (как в случае с Car lada = 2015):
                              // Driver petrov = std::string("Petrov");
    petrov.print();

    ivanov.setRate(7.9);
    petrov.setRate(8.4);

    // Обращение к статическим членам может идти по-разному:

    std::cout << "Top rate among drivers: " << std::endl;
    std::cout << Driver::top_rate << std::endl;
    std::cout << ivanov.top_rate << std::endl;
    std::cout << petrov.top_rate << std::endl;

    // но суть одинакова: статические данные -
    // это по сути глобальные данные, помещенные в scope класса



    // =========================== PART 3 ==================================
    // Классы из файла misc.h: демо пустого класса и приватного конструктора
    // =====================================================================

    std::cout << std::endl << "misc demos:" << std::endl;

    Empty empty;
    std::cout << "Size of empty: " << sizeof(empty) << std::endl;


    // Закомментированный код не скомпилируется, т.к. конструктор - private:

    // GlobalScreen screen;
    // screen.hello();

    GlobalScreen::hello();
    GlobalScreen::bye();

    std::cout << std::endl;


    // напоследок полюбуемся лексусом Иванова )))
    const Car* car = ivanov.getCar();
    car->print();

    delete lexus;

    // если попробуем снова написать так:
    //
    // car->print();
    //
    // то вылетим, т.к. car Иванова указывает на lexus, который мы только что удалили.

    // Может смутить такая кажущаяся ненадежность кода,
    // но в нашем случае мы концептуально так и решили изначально -
    // возложить ответственность за сохранность данных не на водителей,
    // а на внешний код - здесь это функция main(), она должна следить за ссылками

    return 0;
}

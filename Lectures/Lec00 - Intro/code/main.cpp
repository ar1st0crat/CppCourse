// =============== ЗАГОЛОВОЧНЫЕ ФАЙЛЫ =========================

// директива #include подключает заголовочный файл в проект
// (просто подставляет на это место содержимое файла iostream)
#include <iostream>
#include <fstream>
#include <iomanip>

// заголовочные файлы, начинающиеся с символа 'с' пришли из языка С
#include <cstdio>
#include <cmath>
#include <ctime>

// локальные файлы указываются в кавычках
#include "car.h"
#include "trig.h"

// ============================================================


// точка входа в программу
int main(int argc, char *argv[])
{
    int num = 73;
    std::string name = "unknown";


    // ================== PART 1 =====================
    // Работа с потоками ввода-вывода (консоль, файлы)
    // ===============================================

    // iostream - потоковый С++ ввод-вывод

    std::cout << "Hello from std::cout!" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter some number: ";
    std::cin >> num;
    std::cout << "We care about only last digit " << num % 10 << ", " << name;
    std::cout << std::endl << std::endl;


    // cstdio - C-style ввод-вывод (тоже жив курилка )))

    printf("Hello from printf()!\n");
    char name_buf[32];
    printf("Enter your name: ");
    scanf("%s", name_buf);          // можно ввести так (до первого пробела)
    //gets(name_buf);               // или так (вся строка корректно введется)
    printf("Enter some number: ");
    scanf("%d", &num);
    printf("We care about only last digit %d, %s\n\n", num % 10, name_buf);

    // Какие проценты можно указать, смотрим в стандарте:
    // http://www.cplusplus.com/reference/cstdio/printf/
    /*
        specifier	Output                                      Example
        --------------------------------------------------------------------
        %d or %i    Signed decimal integer                      392
        %u          Unsigned decimal integer                    7235
        %o          Unsigned octal                              610
        %x          Unsigned hexadecimal integer                7fa
        %X          Unsigned hexadecimal integer (uppercase)	7FA
        %f          Decimal floating point, lowercase           392.65
        %F          Decimal floating point, uppercase           392.65
        %e          Scientific notation
                    (mantissa/exponent), lowercase              3.9265e+2
        %E          Scientific notation
                    (mantissa/exponent), uppercase              3.9265E+2
        %g          Use the shortest representation: %e or %f	392.65
        %G          Use the shortest representation: %E or %F	392.65
        %a          Hexadecimal floating point, lowercase       -0xc.90fep-2
        %A          Hexadecimal floating point, uppercase       -0XC.90FEP-2
        %c          Character                                   a
        %s          String of characters                        sample
    */

    // примеры форматирования с помощью iostream+iomanip и cstdio:

    printf("PI = %4.2f\n", 3.1416);
    printf("%10d%10d\n", 123, 456);

    std::cout << "PI = " << std::setw(4)
                         << std::setprecision(3)
                         << 3.1416 << std::endl;
    std::cout << std::setw(10) << 123 <<
                 std::setw(10) << 456 << std::endl;


    // ФАЙЛОВЫЙ ввод-вывод программируется с помощью iostream
    // точно так же, как и консольный, т.к. это всё потоки:

    // запишем в файл temp.txt:

    std::ofstream f("temp.txt");
    f << std::setw(4)
      << std::setprecision(3)
      << 3.1416 << std::endl;
    f << std::setw(10) << 123 <<
         std::setw(10) << 456 << std::endl;

    // т.е. просто меняем std::cout на переменную f
    // (почему так можно легко все сделать, узнаем позже)

    f.close();
    // можно файл и не закрывать,
    // ofstream так устроен, что файл закроется сам, когда
    // дойдем до ближайшей закрывающей "{"


    // прочитаем из файла temp.txt:

    std::ifstream input("temp.txt");
    double pi;
    int n1, n2;
    input >> pi >> n1 >> n2;

    std::cout << "Read from file: " << pi << ", " << n1 << ", " << n2;
    std::cout << std::endl << std::endl;


    // Файловый ввод-вывод с помощью cstdio, в целом, также аналогичен консольному
    // (нужно создать файл и все функции предварять символом "f"):

    FILE* file = fopen("ctemp.txt", "wt");
    fprintf(file, "PI = %4.2f\n", 3.1416);
    fprintf(file, "%10d%10d\n", 123, 456);
    fclose(file);
    // здесь закрывать обязательно



    // ================== PART 2 =====================
    // Простые типы данных, sizeof, инструкция typedef
    // ===============================================

    // Простые типы данных почти такие же, как в C#;
    // но в C# нет таких проблем с переносимостью, как в С++:
    // например, в С++ long может быть как 4 байта, так и 8

    long chuck_norris_iq = 1263257636523464L;
    std::cout << "Chuck's IQ: " << sizeof(chuck_norris_iq) << " bytes = ";

    // "Это у других не влезет, а у меня влезет... гляди, Пятачок" (с)
    std::cout << chuck_norris_iq << std::endl;

    int64_t long64 = 111222333444555L;  // влезет
    int32_t long32 = 111222333444555L;  // не влезет

    std::cout << "long64: " << sizeof(long64) << " bytes = ";
    std::cout << long64 << std::endl;

    std::cout << "long32: " << sizeof(long32) << " bytes = ";
    std::cout << long32 << std::endl << std::endl;


    // кроме того, можно вводить синоним для типа
    typedef unsigned char byte;

    // ...typedef полезен, и к нему еще вернемся...


    byte little_numba = 23;

    std::cout << "little numba:" << std::endl;

    // к сожалению, при выводе на консоль есть неудобство:
    // т.к. byte - это завуалированный char, вывод будет символьный,
    // поэтому в этом случае надо явно преобразовывать к инту
    std::cout << (int)little_numba << std::endl;
    // в с++ это правильно делать так:
    std::cout << static_cast<int>(little_numba) << std::endl;

    // даже в этом случае надо кастовать:
    uint8_t little_numba_t = 23;
    std::cout << static_cast<int>(little_numba_t) << std::endl << std::endl;



    // ================== PART 3 =====================
    // Возможности из cmath, ctime, cstdlib
    // ===============================================

    // задать семя рандомизатора
    srand(123);
    // часто делают так (случайность берут из текущего времени)
    srand(time(0));

    std::cout << "log2(128) = " << log2(128.0) << std::endl;

    auto x = rand() % 100;
    std::cout << "sin(x)^2 + cos(x)^2 = " << trigomagic(x) << std::endl << std::endl;



    // ================== PART 4 =====================
    // Ключевое слово static:
    //      перед переменной/функцией в файле
    //      перед переменной внутри функции
    //      перед переменной/методом в классе
    // ===============================================

    std::cout << "Demo of static variable inside function" << std::endl;

    for (int i = 0; i < 5; ++i)
    {
        trigo_iteration();
    }

    std::cout << std::endl;

    // REMEMBER: static - это синоним глобальности



    // ============= PART 5 (ВАЖНО!) =================
    // Пример использования структуры (Car),
    //                      перечисления (Color),
    //                      пространства имен (domain)
    // (см. файлы car.h, color.h)
    // ===============================================

    domain::Car car1;
    car1.make_ = "Ford";
    car1.model_ = "Focus";
    car1.year_ = 2008;
    car1.color_ = Color::WHITE;
    car1.no_ = "a319om";
    car1.print();

    domain::Car car2;
    car2.make_ = "LADA";
    car2.model_ = "Kalina";
    car2.year_ = 2011;
    car2.color_ = Color::RED;
    car2.no_ = "c915aa";
    car2.print();



    // ======== PART 6 (необязательная) ==============
    // Пример объединения (union) и битовых полей
    // ===============================================

    union Format
    {
        double dvalue;
        int ivalue;
    }
    format1, format2;

    format1.dvalue = 54.67;
    // sizeof(format1) вернет размер double (8 байт)

    format2.ivalue = 54;
    // sizeof(format2) также вернет размер double (8 байт)


    union Bits
    {
        char type: 2;
        char value: 5;
    }
    bits;

    bits.type = 1;
    bits.value = 17;

    return 0;
}

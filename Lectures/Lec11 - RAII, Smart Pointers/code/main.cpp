#include <cstring>
#include <iostream>
#include <memory>
#include "safeptr.h"
#include "safefile.h"
#include "point.h"

// RAII
// Resource Acquisition Is Initialization

int main()
{
    // продемонстрируем наш безопасный файл
    {
        SafeFile f("a.txt");

        printf("enter string:\n");

        char buf[255];
        std::cin.getline(buf, 255);

        if (strlen(buf) > 7)
        {
            printf("STOP!\n");
            return 1;
        }
        // и здесь должен корректно закрыться

        f.write(buf);
    }
    // и здесь должен корректно закрыться


    // демонстрация нашего умного указателя SafePtr

    int* p = new int(10);

    // ... традиционная работа с указателем

    delete p;   // но всегда надо писать этот дилит ((


    SafePtr<int> iptr(new int(5));

    {
        SafePtr<int> tmp(new int(10));
        std::cout << *tmp << std::endl;
    }
    // утечки памяти не будет, т.к. дилит вызовется в деструкторе


    std::cout << *iptr << std::endl;

    // демонстрация перегрузки оператора->

    SafePtr<Point> pptr(new Point(12, 17));
    std::cout << pptr->x_ << " " << pptr->y_ << std::endl;



    // smart pointers (C++11):
    // unique_ptr, shared_ptr, make_shared, weak_ptr, lock


    // семантика единоличного владения ресурсом:

    std::unique_ptr<int> uptr1(new int(900));
    std::cout << *uptr1 << std::endl;

    std::unique_ptr<int> uptr2 = std::move(uptr1);
    std::cout << *uptr2 << std::endl;


    // семантика разделяемого владения ресурсом с подсчетом ссылок (use_count)

    std::shared_ptr<int> sp = std::make_shared<int>(1200);
    // use_count = 1

    {
        std::shared_ptr<int> copy = sp; 	// use_count++  (use_count = 2)
    }
    // use_count--     (use_count = 1)

    std::shared_ptr<int> copy = sp;			// use_count = 2

    std::cout << *sp << " " << *copy << std::endl;
    std::cout << sp.use_count() << std::endl;

    copy.reset();           // delete int
    // use_count = 1

    std::cout << sp.use_count() << std::endl;

    // не надо так, а то вылетите:
    // std::cout << *copy << std::endl;


    // семантика слабой ссылки

    std::weak_ptr<int> wp;

    {
        std::shared_ptr<int> sptr = std::make_shared<int>(500);
        // use_count = 1

        wp = sptr;
        // use_count = 1
    }

    try
    {
        std::shared_ptr<int> shared_leto = wp.lock();
        // хаха, Shared Leto = 0
        // камеди отдыхаетъ

        if (!wp.expired())
        {
            std::cout << *shared_leto << std::endl;
        }
        else
        {
            std::cout << "Pointer expired!" << std::endl;
        }

        // вот тут бросится исключение
        std::shared_ptr<int> s(wp);
    }
    catch (std::bad_weak_ptr& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }



    // был еще такой auto_ptr, но о нем можно забыть, ибо:

    // std::vector<std::auto_ptr<Point>> vec;
    // vec.push_back(std::auto_ptr<Point>(new Point(1, 2)));

    // std::auto_ptr<Point> p = vec[0];			// move
    //
    // // work with p

    // std::cout << vec[0]->x_ << std::endl;

    // // delete

    return 0;
}

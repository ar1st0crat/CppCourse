#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <bitset>
#include <iterator>
#include <algorithm>
#include <functional>
#include "functors.h"

class Person
{
public:
    Person(std::string name, int age) : name_(name), age_(age)
    {
    }
protected:
    std::string name_;
    int age_;
};


void sequential_containers_demo()
{
    // 1) КОНТЕЙНЕРЫ

    // последовательные контейнеры STL: vector, deque, list

    std::cout << "vector demo: " << std::endl;

    std::vector<int> v{2, 7, 4, -3, -4, 1};

    /*
     * Как выше, увы, в С++ до стандарта 11 написать нельзя
     *
     * Поэтому в старом С++ пишут просто:
     *
    std::vector<int> v;
    v.push_back(2);
    v.push_back(7);
    v.push_back(4);
    v.push_back(-3);
    v.push_back(-4);
    v.push_back(1);
    */

    std::deque<int> dq;
    dq.push_front(7);

    std::list<int> il;
    il.push_back(12);

    // по вектору можно пройтись, как по массиву,
    // т.к. у него итератор - произвольный и перегружен оператор []
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    // адаптеры контейнеров: stack, queue, priority_queue

    std::cout << "stack demo: " << std::endl;

    std::stack<double, std::vector<double>> s;
    s.push(2);
    s.push(4);
    s.push(5);

    std::cout << s.top() << " ";
    s.pop();
    std::cout << s.top() << " ";
    s.pop();

    std::cout << std::endl << std::endl;

    std::cout << "queue demo: " << std::endl;

    std::queue<double> q;
    q.push(2);
    q.push(4);
    q.push(5);

    std::cout << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << q.front() << " " << q.back() << std::endl;
    q.pop();

    std::cout << std::endl << std::endl;


    // 2) ИТЕРАТОРЫ

    /* Iterators:
     *      Random access iterators:    ++, --, [] + arithmetics, read, write
     *      Bidirectional iterators:    ++, --, read, write
     *      Forward iterators:          ++, read, write
     *      Input iterators:            ++, read
     *      Output iterators            ++, write
     *
     *      Reverse iterators
     *
     *      Advanced:
     *          back_inserter, front_inserter, inserter
     *          istream_iterator, ostream_iterator
     */


    std::cout << "iterators demo: " << std::endl;

    std::vector<int>::iterator it;
    for (it = v.begin(); it != v.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    std::cout << "reverse iterator demo: " << std::endl;

    typedef std::vector<int>::reverse_iterator moonwalker;

    for (moonwalker walker = v.rbegin(); walker != v.rend(); ++walker)
    {
        std::cout << *walker << " ";
    }
    std::cout << std::endl << std::endl;


    //std::vector<Person> subscribers;      // композиция
    std::vector<Person*> subscribers;       // агрегация

    subscribers.push_back(new Person("Ivanov", 20));
    subscribers.push_back(new Person("Petrov", 21));

    // если делаем агрегацию, то чистим память сами
    std::vector<Person*>::iterator pit;
    for (pit = subscribers.begin(); pit != subscribers.end(); ++pit)
    {
        delete *pit;
    }
    subscribers.clear();

    // впрочем, чтобы это удаление постоянно не писать, можно использовать умные указатели



    /* std functors:
     *  less, greater, equal_to
     *  minus, plus, divides, modulus, multiplies
     *  logical_not, logical_and, logical_or
     *  bind1st, bind2nd, not1, not2
     *  mem_fun, fun_ptr
     */


    std::bind2nd(std::less<int>(), 10);
    std::bind1st(std::modulus<size_t>(), 512);
    std::not1(std::logical_not<bool>());

    std::size_t cnt = std::count_if(
                v.begin(), v.end(), std::bind2nd(std::less<int>(), 3));  // x < 3

    std::cout << std::endl << cnt << std::endl;

    std::vector<std::string> ws;
    std::for_each(ws.begin(), ws.end(), std::mem_fun_ref(&std::string::clear));

    std::vector<int> tv(v.size());
    std::vector<int> cv(v.size());
    std::transform(v.begin(), v.end(), tv.begin(), std::bind2nd(std::multiplies<int>(), 2));
    std::copy(tv.begin(), tv.end(), cv.begin());




    std::copy(v.begin(), v.end(), std::ostream_iterator<int32_t>(std::cout, " "));

    std::vector<double> vcopy;
    std::copy(v.begin(), v.end(), std::back_inserter(vcopy));

    std::copy(vcopy.begin(), vcopy.end(), std::ostream_iterator<double>(std::cout, " "));

//    std::ifstream file("input.txt");
//    std::vector<int> fvec((std::istream_iterator<int>(file)),
//                          std::istream_iterator<int>());

//    std::for_each(begin(fvec), end(fvec), [](int x) {
//        std::cout << x << std::endl;
//    });



    // IDIOMS:

    // 1) remove element by value
    tv.erase(std::remove(tv.begin(), tv.end(), 2), tv.end());
    std::copy(tv.begin(), tv.end(), std::ostream_iterator<double>(std::cout, " "));

    // 2) remove unique elements
    std::sort(cv.begin(), cv.end());
    cv.erase(std::unique(cv.begin(), cv.end()), cv.end());
    std::copy(cv.begin(), cv.end(), std::ostream_iterator<double>(std::cout, " "));

    // more:
    // std::next_permutation, std::prev_permutation
    // nth-element, merge, partition


    std::cout << std::endl;


    // 3) АЛГОРИТМЫ И ФУНКТОРЫ

    std::cout << "algorithm demo (count_if): " << std::endl;

    // алгоритм в функциональном стиле
    std::cout << std::count_if(v.begin(), v.end(), isNegative) << " negatives" << std::endl;

    // алгоритм в смеси функционального с ООП-стилем (функция завернута в объект-функтор)
    NegativeCounter counter;
    std::cout << std::count_if(v.begin(), v.end(), counter) << " negatives" << std::endl;

    // алгоритмы можно запускать и на обычных массивах
    int arr[] = {1, 2, 3, -5, -6, -7, 4, 3, 2, -10};
    std::cout << std::count_if(arr, arr + 10, NegativeCounter()) << " negatives" << std::endl;

    // Можно свой функтор и не писать, если есть его стандартный аналог:
    std::cout << std::count_if(arr, arr + 10, std::bind2nd(std::less<int>(), 0)) << " negatives" << std::endl;

    /*
     *  Еще примеры:
     *
     *  std::bind2nd(std::less<int>(), 10);
        std::bind1st(std::modulus<std::size_t>(), 512);
        std::not1(std::logical_not<bool>());
     */


    std::vector<int> numbazz(10);
    std::iota(begin(numbazz), end(numbazz), 1);
    std::for_each(numbazz.begin(), numbazz.end(), print);

    std::cout << std::endl;


    // ============================================== vector<bool> and bitset demo
    std::vector<bool> hehehe(5, true);
    hehehe[2] = false;

    for (auto b : hehehe)
    {
        std::cout << b << " ";
    }
    std::cout << std::endl;


    std::bitset<7> bits;
    bits.set(1);
    bits.set(5);
    std::cout << bits << std::endl;

    auto xl =  bits.to_ullong();
    std::cout << xl << std::endl;
}

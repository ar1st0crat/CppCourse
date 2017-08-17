#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <iterator>
#include <functional>
#include "functors.h"


void associative_containers_demo()
{
    std::cout << "Char Map (Dictionary):" << std::endl;

    // ============================= простой пример map

    std::map<char, int> char_dict;

    // 1) первый способ добавления пары "ключ-значение" в словарь

    char_dict['a'] = 3;
    char_dict['c'] = 2;
    char_dict['a']++;        // можно так
    char_dict['d']++;        // и даже так можно (на несуществующем ранее ключе)

    // 2) второй способ добавления (создать пару явно)

    std::pair<char, int> p;
    p.first = 'm';
    p.second = 15;
    char_dict.insert(p);

    // 3) третий способ (предпочтительный - создание пары фабричным методом)

    char_dict.insert(std::make_pair('g', 12));

    std::map<char, int>::iterator it;
    for (it = char_dict.begin(); it != char_dict.end(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }


    // ============= второй пример map (Ключ "ОС": Значение "набор тегов, связанной с ОС")

    std::cout << "OS Dictionary:" << std::endl;

    typedef std::map<std::string, std::vector<std::string>> osmap;

    osmap os;
    os["Windows"].push_back("Wow!");
    os["Windows"].push_back("Cool!");
    os["Windows"].push_back("Nope!");

    os["Linux"].push_back("Hmm!");
    os["Linux"].push_back("Yeah!");

    for (osmap::iterator it = os.begin(); it != os.end(); ++it)
    {
        std::cout << it->first << " : ";
        for (std::size_t i = 0; i < it->second.size(); ++i)
        {
            std::cout << it->second[i] << " ";
        }
        std::cout << std::endl;
    }


    // ============================== еще один пример map

    std::cout << "Mapping: number -> number:" << std::endl;

    std::map<int, int> numbers;

    numbers.insert(std::make_pair(17, 0));
    numbers.insert(std::make_pair(12, 4));
    numbers.insert(std::make_pair(15, 2));

    std::cout << "12 -> " << numbers[12] << std::endl;
    std::cout << "15 -> " << numbers[15] << std::endl;


    // демонстрация унарного функтора с членом-параметром

    NumFinder unary_finder;
    unary_finder.param_ = 2;

    std::map<int, int>::iterator mi =
            std::find_if(numbers.begin(), numbers.end(), unary_finder);

    std::cout << "Value 2 : Key " << mi->first << std::endl;


    // демонстрация std::bind2nd()

    NumBinFinder num_finder;

    mi = std::find_if(numbers.begin(), numbers.end(), std::bind2nd(num_finder, 4));

    std::cout << "Value 4 : Key " << mi->first << std::endl;

    mi = std::find_if(numbers.begin(), numbers.end(), std::bind2nd(num_finder, 0));

    std::cout << "Value 0 : Key " << mi->first << std::endl;

    // фактически bind() делает из одной функции c 2 переменными другую
    // функцию с 1 переменной (или из одного функтора другой). Что-то вроде:

    // foo(pair, 4)  -> /bind(foo, 4)/ ->   foo_bind_4(pair) {  return foo(pair, 4); }

    // Это называется "частичное применение функции".
    // Также в функциональном программировании есть "каррирование".



    std::map<std::string, int, std::greater<std::string>> team;

    team.insert(std::make_pair("Thierry", 11));
    team.insert(std::make_pair("Zinedine", 5));
    team.insert(std::make_pair("Lionel", 10));
    team.insert(std::make_pair("Cristiano", 7));

    for (const auto& player : team)
    {
        std::cout << player.first << " #" << player.second << std::endl;
    }


    // под капотом map лежит красно-черное дерево;
    // многие привыкли, что словари реализуются на основе хеш-таблиц...

    // Начиная с С++11, доступен именно основанный на хеш-таблицах мэп
    //                        unordered_map
    // (ну раз уж С++11, то и проинициализируем в стиле С++11)

    std::unordered_map<std::string, std::string> phonebook
    {
        { "Petrov", "000-111-22-33" },
        { "Ivanov", "000-222-22-33" },
        { "Sidorov", "000-333-22-33" }
    };

    for (const auto& entry : phonebook)
    {
        std::cout << entry.first << ", Tel: " << entry.second << std::endl;
    }

    // можем посмотреть, что именно он там нахешировал:

    auto hash_func = phonebook.hash_function();

    std::cout << std::endl << "Hashes:" << std::endl;
    std::cout << "Petrov: " << hash_func("Petrov") << std::endl;
    std::cout << "Ivanov: " <<  hash_func("Ivanov") << std::endl;
    std::cout << "Sidorov: " <<  hash_func("Sidorov") << std::endl;


    std::unordered_map<Person, int> salaries
    {
        { Person("Bob", 24), 5000 },
        { Person("Alice", 28), 8000 },
        { Person("Stevie", 20), 3000 }
    };

    for (const auto& record : salaries)
    {
        std::cout << record.first << ", Salary: " << record.second << std::endl;
    }



    // =================================== пример множества set
    std::set<int> odd;
    odd.insert(1);
    odd.insert(3);
    odd.insert(5);
    odd.insert(7);
    odd.insert(9);

    std::set<int> squares;
    squares.insert(4);
    squares.insert(9);

    std::set<int> res;
    std::set_union(odd.begin(), odd.end(),
                   squares.begin(), squares.end(),
                   std::inserter(res, res.begin()));

    std::cout << "{1, 3, 5, 7, 9} UNION {4, 9}:" << std::endl;
    std::for_each(res.begin(), res.end(), print);
    std::cout << std::endl;
}

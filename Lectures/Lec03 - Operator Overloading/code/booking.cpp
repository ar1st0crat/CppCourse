#include <iostream>
#include "booking.h"

// Конструктор без параметров
// все равно выделяет память под два неизвестных пока адреса
// и устанавливает время в текущее

Booking::Booking() : distance_(0.0), price_(0.0)
{
    addresses_ = new std::string[2] { "unknown", "unknown" };       // C++11 initialization
    address_count_ = 2;

    std::time_t now = std::time(0);
    time_from_ = *localtime(&now);
}

// Конструктор с двумя адресами и временем оформления заказа

Booking::Booking(const std::string& address_from,
                 const std::string& address_to,
                 tm time)
    : time_from_(time), time_to_(time), distance_(0.0), price_(0.0)
{
    addresses_ = new std::string[2] { address_from, address_to };
    address_count_ = 2;
}

// Конструктор с массивом адресов и временем оформления заказа

Booking::Booking(const std::string addresses[],
                 std::size_t address_count,
                 tm time)
    : time_from_(time), time_to_(time), distance_(0.0), price_(0.0)
{
    addresses_ = new std::string [address_count];

    for (std::size_t i = 0; i < address_count; ++i)
    {
        addresses_[i] = addresses[i];
    }

    address_count_ = address_count;
}


// Т.к. объекты Booking держат динамические данные,
// следующие два метода надо обязательно переопределить:

// Копирующий конструктор ...

Booking::Booking(const Booking &b)
{
    // глубокое копирование массива адресов:
    address_count_ = b.address_count_;
    addresses_ = new std::string [address_count_];
    for (std::size_t i = 0; i < address_count_; ++i)
    {
        addresses_[i] = b.addresses_[i];
    }
    // копируем все остальное:
    time_from_ = b.time_from_;
    time_to_ = b.time_to_;
    distance_ = b.distance_;
    price_ = b.price_;
}

// ... и оператор присваивания тут как тут

Booking& Booking::operator=(Booking b)
{
    swap(b);        // делаем модно - идиома copy-and-swap
    return *this;
}

// copy-and-swap idiom
void Booking::swap(Booking b)
{
    std::swap(addresses_, b.addresses_);
    std::swap(address_count_, b.address_count_);
    std::swap(time_from_, b.time_from_);
    std::swap(time_to_, b.time_to_);
    std::swap(distance_, b.distance_);
    std::swap(price_, b.price_);
}


/*
// обычный способ перегрузки оператора присваивания
// (похож на конструктор копирования, только надо удалить прежний массив адресов)

Booking& Booking::operator=(const Booking& b)
{
    // обязательно проверяем это:
    if (this == &b)
        return *this;

    delete []addresses_;

    // копируем всё

    address_count_ = b.address_count_;
    addresses_ = new std::string [address_count_];
    for (std::size_t i = 0; i < address_count_; ++i)
    {
        addresses_[i] = b.addresses_[i];
    }
    time_from_ = b.time_from_;
    time_to_ = b.time_to_;
    distance_ = b.distance_;
    price_ = b.price_;

    return *this;
}
*/


// скажем утечкам памяти "нет"

Booking::~Booking()
{
    delete []addresses_;
}




std::string* Booking::getAddresses() const
{
    return addresses_;
}

std::size_t Booking::getAddressCount() const
{
    return address_count_;
}

tm Booking::getTime() const
{
    return time_from_;
}

void Booking::print() const
{
    std::cout << "Booking "
              << time_from_.tm_hour << ":" << time_from_.tm_min << ":" << time_from_.tm_sec
              << std::endl;

    for (std::size_t i = 0; i < address_count_ - 1; ++i)
    {
        std::cout << addresses_[i] << " -> ";
    }
    std::cout << addresses_[address_count_ - 1];
    std::cout << std::endl << std::endl;
}




// ===================== ПЕРЕГРУЗКА ОПЕРАТОРОВ ======================

// по-хорошему здесь надо проверить выход index за "пределы разумного"
// (но пока не делаем эту проверку)
std::string& Booking::operator[](std::size_t index) const
{
    return addresses_[index];
}

// префиксный инкремент
Booking& Booking::operator++()
{
    time_from_.tm_min++;
    return *this;
}

// постфиксный инкремент
Booking Booking::operator++(int)
{
    Booking b(*this);

    time_from_.tm_min++;

    return b;
}

Booking& Booking::operator+=(const std::string& address)
{
    std::string* addresses = new std::string [address_count_ + 1];

    for (std::size_t i = 0; i < address_count_; ++i)
    {
        addresses[i] = addresses_[i];
    }
    addresses[address_count_++] = address;

    delete []addresses_;
    addresses_ = addresses;

    return *this;
}


// ========================================================
// ========== Внимание! Это глобальные функции ============
// ==== Если их сделать friend, то кода будет поменьше ====
// ============= Но это тема другой лекции ================
// ========================================================

// простая логика

bool operator<(const Booking& b1, const Booking& b2)
{
    tm time1 = b1.getTime();
    tm time2 = b2.getTime();

    return difftime(mktime(&time1), mktime(&time2)) < 0;
}

// чуть более хитрая логика

Booking operator+(const Booking& b1, const Booking& b2)
{
    std::size_t count1 = b1.getAddressCount();
    std::size_t count2 = b2.getAddressCount();
    std::size_t total_count = count1 + count2;

    std::string* addresses1 = b1.getAddresses();
    std::string* addresses2 = b2.getAddresses();

    // дополнительная плюшка - проверяем, а не является ли
    // конечный пункт первого заказа начальным пунктом второго

    if (addresses1[count1 - 1] == addresses2[0])
    {
        // если да, то не будем дублировать последний пункт первого заказа

        total_count--;
        count1--;
    }

    std::string* addresses = new std::string [total_count];

    // конкатенириуем два массива адресов:

    std::size_t i = 0, j = 0;
    while (i < count1)
    {
        addresses[i++] = addresses1[j++];
    }
    j = 0;
    while (i < total_count)
    {
        addresses[i++] = addresses2[j++];
    }

    // и создаем комбинированный заказ:
    Booking b(addresses, total_count, b1.getTime());

    delete []addresses;

    return b;
}

// ========================================================

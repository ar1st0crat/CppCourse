#include <iostream>
#include "booking.h"


// Конструктор с двумя адресами и временем оформления заказа

Booking::Booking(const std::string& address_from,
                 const std::string& address_to,
                 tm time)
    : time_from_(time), time_to_(time),
      distance_(0.0), price_(0.0),
      is_vip_(false), is_truck_(false)
{
    addresses_ = new std::string[2] { address_from, address_to };
    address_count_ = 2;
}

// Конструктор с массивом адресов и временем оформления заказа

Booking::Booking(const std::string addresses[],
                 std::size_t address_count,
                 tm time)
    : time_from_(time), time_to_(time),
      distance_(0.0), price_(0.0),
      is_vip_(false), is_truck_(false)
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
    is_vip_ = b.is_vip_;
    is_truck_ = b.is_truck_;
}

// ... и оператор присваивания тут как тут

Booking& Booking::operator=(Booking b)
{
    swap(*this, b);        // делаем модно - идиома copy-and-swap
    return *this;
}

// copy-and-swap idiom (done right!)

void swap(Booking& b1, Booking& b2)
{
    using std::swap;

    swap(b1.addresses_, b2.addresses_);
    swap(b1.address_count_, b2.address_count_);
    swap(b1.time_from_, b2.time_from_);
    swap(b1.time_to_, b2.time_to_);
    swap(b1.distance_, b2.distance_);
    swap(b1.price_, b2.price_);
    swap(b1.is_truck_, b2.is_truck_);
    swap(b1.is_vip_, b2.is_vip_);
}


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

bool Booking::isTruck() const
{
    return is_truck_;
}

bool Booking::isVip() const
{
    return is_vip_;
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
// ====== В классе Booking они объявлены как friend =======
// ===== Поэтому имеют доступ ко всем данным Booking ======
// ========================================================

// простая логика

bool operator<(const Booking& b1, const Booking& b2)
{
    tm start = b1.time_from_;
    tm end = b2.time_from_;

    return difftime(mktime(&start), mktime(&end)) < 0;
}

// чуть более хитрая логика

Booking operator+(const Booking& b1, const Booking& b2)
{
    std::size_t count = b1.address_count_;
    std::size_t total_count = b1.address_count_ + b2.address_count_;

    // дополнительная плюшка - проверяем, а не является ли
    // конечный пункт первого заказа начальным пунктом второго

    if (b1.addresses_[count - 1] == b2.addresses_[0])
    {
        // если да, то не будем дублировать последний пункт первого заказа

        total_count--;
        count--;
    }

    std::string* addresses = new std::string [total_count];

    // конкатенириуем два массива адресов:

    std::size_t i = 0, j = 0;
    while (i < count)
    {
        addresses[i++] = b1.addresses_[j++];
    }
    j = 0;
    while (i < total_count)
    {
        addresses[i++] = b2.addresses_[j++];
    }

    // и создаем комбинированный заказ:
    Booking b(addresses, total_count, b1.time_from_);

    delete []addresses;

    return b;
}


// перегруженный оператор потокового вывода

std::ostream& operator<<(std::ostream& os, const Booking& b)
{
    os << "Booking " << b.time_from_.tm_hour << ":"
                     << b.time_from_.tm_min << ":"
                     << b.time_from_.tm_sec << " -> "
                     << b.time_to_.tm_hour << ":"
                     << b.time_to_.tm_min << ":"
                     << b.time_to_.tm_sec << std::endl;

    for (std::size_t i = 0; i < b.address_count_ - 1; ++i)
    {
        os << b.addresses_[i] << " -> ";
    }
    os << b.addresses_[b.address_count_ - 1];
    os << std::endl << std::endl;

    return os;
}

// ========================================================

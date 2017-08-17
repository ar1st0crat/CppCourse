#include <iostream>
#include "booking.h"


// Конструктор с двумя адресами и временем оформления заказа

Booking::Booking(const std::string& address_from,
                 const std::string& address_to,
                 std::tm time)
    : time_from_(time),
      time_to_(time),
      distance_(0.0),
      price_(0.0),
      is_vip_(false),
      is_truck_(false)
{
    addresses_.push_back(address_from);
    addresses_.push_back(address_to);
}

// Конструктор с массивом адресов и временем оформления заказа

Booking::Booking(std::vector<std::string>::const_iterator first,
                 std::vector<std::string>::const_iterator last,
                 std::tm time)
    : time_from_(time),
      time_to_(time),
      distance_(0.0),
      price_(0.0),
      is_vip_(false),
      is_truck_(false)
{
    std::copy(first, last, std::back_inserter(addresses_));
}


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
    swap(b1.time_from_, b2.time_from_);
    swap(b1.time_to_, b2.time_to_);
    swap(b1.distance_, b2.distance_);
    swap(b1.price_, b2.price_);
    swap(b1.is_truck_, b2.is_truck_);
    swap(b1.is_vip_, b2.is_vip_);
}


std::size_t Booking::getAddressCount() const
{
    return addresses_.size();
}

std::tm Booking::getTime() const
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

std::string& Booking::operator[](std::ptrdiff_t index)
{
    if (index < 0 || index >= addresses_.size())
    {
        throw std::out_of_range("Invalid address index!");

        // в принципе, можно использовать
        //
        //     addresses_.at(index)
        //
        // эта функция тоже бросит исключение, в отличие от векторского индексатора
    }
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
    addresses_.push_back(address);
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
    std::tm start = b1.time_from_;
    std::tm end = b2.time_from_;

    return std::difftime(std::mktime(&start), std::mktime(&end)) < 0;
}

// чуть более хитрая логика

Booking operator+(const Booking& b1, const Booking& b2)
{
    // дополнительная плюшка - проверяем, а не является ли
    // конечный пункт первого заказа начальным пунктом второго
    std::size_t offset = 0;

    if (b1.addresses_.back() == b2.addresses_.front())
    {
        // если да, то не будем дублировать последний пункт первого заказа
        offset = 1;
    }

    // создаем комбинированный заказ

    // сначала копируем все из первого:
    Booking result(b1.addresses_.begin(), b1.addresses_.end(), b1.time_from_);

    // конкатенириуем со вторым (возможно со смещением 1):
    std::copy(b2.addresses_.begin() + offset,
              b2.addresses_.end(),
              std::back_inserter(result.addresses_));

    return result;
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

    auto iter = b.addresses_.begin();

    while (iter+1 != b.addresses_.end())
    {
        os << *(iter++) << " -> ";
    }
    os << b.addresses_.back();
    os << std::endl << std::endl;

    return os;
}

// ========================================================

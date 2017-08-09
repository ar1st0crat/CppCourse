#pragma once

#include <string>
#include <ctime>

class Booking
{
public:
    Booking(const std::string& address_from, const std::string& address_to, tm time);
    Booking(const std::string addresses[], std::size_t count, tm time);
    Booking(const Booking& b);
    Booking& operator=(Booking b);
    ~Booking();

    std::string& operator[](std::size_t index) const;
    Booking& operator+=(const std::string& address);
    Booking& operator++();
    Booking operator++(int);

public:
    std::string* getAddresses() const;
    std::size_t getAddressCount() const;
    tm getTime() const;
    bool isTruck() const;
    bool isVip() const;

public:
    friend Booking operator+(const Booking& b1, const Booking& b2);
    friend bool operator<(const Booking& b1, const Booking& b2);
    friend std::ostream& operator<<(std::ostream& o, const Booking& b);
    friend void swap(Booking& b1, Booking& b2);

    // объявлены два класса друзьями (только для примера!)
    friend class Operator;
    friend class Driver;

private:
    std::string* addresses_;        // динамический массив адресов в заказе
    std::size_t address_count_;
    double distance_;
    double price_;
    tm time_from_;
    tm time_to_;
    bool is_truck_;
    bool is_vip_;
};

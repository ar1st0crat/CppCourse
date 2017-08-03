#pragma once

#include <string>
#include <ctime>

class Booking
{
public:
    Booking();
    Booking(const std::string& address_from, const std::string& address_to, tm time);
    Booking(const std::string addresses[], std::size_t count, tm time);
    Booking(const Booking& b);
    Booking& operator=(Booking b);
    void swap(Booking b);
    ~Booking();

    std::string& operator[](std::size_t index) const;
    Booking& operator+=(const std::string& address);
    Booking& operator++();
    Booking operator++(int);

public:
    std::string* getAddresses() const;
    std::size_t getAddressCount() const;
    tm getTime() const;

    void print() const;

private:
    std::string* addresses_;        // динамический массив адресов в заказе
    std::size_t address_count_;
    double distance_;
    double price_;
    tm time_from_;
    tm time_to_;
};

Booking operator+(const Booking& b1, const Booking& b2);
bool  operator<(const Booking& b1, const Booking& b2);

#pragma once

#include <string>
#include <ctime>
#include <vector>

class Booking
{
public:
    Booking(const std::string& address_from, const std::string& address_to, std::tm time);
    Booking(std::vector<std::string>::const_iterator first,
            std::vector<std::string>::const_iterator last,
            std::tm time);
    Booking& operator=(Booking b);

    std::string& operator[](std::ptrdiff_t index);
    Booking& operator+=(const std::string& address);
    Booking& operator++();
    Booking operator++(int);

public:
    std::size_t getAddressCount() const;
    tm getTime() const;
    bool isTruck() const;
    bool isVip() const;

public:
    friend Booking operator+(const Booking& b1, const Booking& b2);
    friend bool operator<(const Booking& b1, const Booking& b2);
    friend std::ostream& operator<<(std::ostream& o, const Booking& b);
    friend void swap(Booking& b1, Booking& b2);

    // объявлены два класса друзьями (только для примера)
    friend class Operator;
    friend class Driver;

private:
    std::vector<std::string> addresses_;
    double distance_;
    double price_;
    std::tm time_from_;
    std::tm time_to_;
    bool is_truck_;
    bool is_vip_;
};

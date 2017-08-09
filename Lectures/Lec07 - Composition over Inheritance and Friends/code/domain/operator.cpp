#include <iostream>
#include "operator.h"

Operator::Operator() : Employee(), id_(0)
{
}

Operator::Operator(const std::string& name)
    : Employee(name), id_(0)
{
}

Operator::Operator(const std::string& name,
                   const std::string& phone,
                   tm reg_date)
    : Employee(name, phone, reg_date), id_(0)
{
}

void Operator::print() const
{
    std::cout << "ID: " << id_ << " - "<< name_ << " (" << phone_ << ")" << std::endl;
}

void Operator::setId(unsigned int id)
{
    id_ = id;
}

unsigned int Operator::getId() const
{
    return id_;
}

double Operator::salaryBonus(double salary) const
{
    return salary * 0.1;
}

std::string Operator::benefits() const
{
    return "free lunch, swimming pool";
}

// новая функция оператора - обрабокта и подготовка заказа:

Booking* Operator::processBooking(std::tm call_time)
{
    // оператор спрашивает адрес отправки и доставки:

    std::string address_from, address_to;

    std::cout << "Your address?" << std::endl;
    std::getline(std::cin, address_from);
    std::cout << "Where are you heading?" << std::endl;
    std::getline(std::cin, address_to);

    // формирует заказ

    Booking* booking = new Booking(address_from, address_to, call_time);

    // дополняет заказ информацией о типе машины, которая нужна

    std::cout << "Do you need a car (c) or a truck (t)?" << std::endl;
    char choice = 'c';
    std::cin >> choice;
    std::cin.ignore(256, '\n');
    booking->is_truck_ = (choice == 't') ? true : false;

    // еще оператор может сформировать признак VIP-шности заказа, но это потом ))

    return booking;
}

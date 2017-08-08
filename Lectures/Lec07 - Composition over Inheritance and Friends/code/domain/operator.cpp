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

double Operator::salary_bonus(double salary) const
{
    return salary * 0.1;
}

std::string Operator::benefit() const
{
    return "free lunch, swimming pool";
}

Booking* Operator::processBooking(std::tm call_time)
{
    std::string address_from, address_to;

    std::cout << "Your address?" << std::endl;
    std::getline(std::cin, address_from);
    std::cout << "Where are you heading?" << std::endl;
    std::getline(std::cin, address_to);

    return new Booking(address_from, address_to, call_time);
}

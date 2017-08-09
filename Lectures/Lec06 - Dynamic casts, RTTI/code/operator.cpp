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

#include <iostream>
#include "operator.h"

Operator::Operator() : Employee(), id_(0)
{
}

Operator::Operator(const std::string& name,
                   const std::string& phone,
                   tm reg_date)
    : Employee(name, phone, reg_date), id_(0)
{
}

void Operator::print(bool show_id) const
{
    if (show_id)
    {
        std::cout << "ID: " << id_ << std::endl;
    }

    Employee::print();
}

void Operator::setId(unsigned int id)
{
    id_ = id;
}

unsigned int Operator::getId() const
{
    return id_;
}

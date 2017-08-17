#include <iostream>
#include "employee.h"

Employee::Employee()
    : name_("unknown"), phone_(""), is_on_trial_(false)
{
    std::time_t now = std::time(0);
    reg_date_ = *localtime(&now);
}

Employee::Employee(const std::string& name)
    : name_(name), phone_(""), is_on_trial_(false)
{
    std::time_t now = std::time(0);
    reg_date_ = *localtime(&now);
}

Employee::Employee(const std::string& name, const std::string& phone, tm reg_date)
    : name_(name), phone_(phone), reg_date_(reg_date), is_on_trial_(false)
{
}

void Employee::setName(const std::string& name)
{
    name_ = name;
}

std::string Employee::getName() const
{
    return name_;
}

void Employee::setOnTrial(bool on_trial)
{
    is_on_trial_ = on_trial;
}

bool Employee::getOnTrial() const
{
    return is_on_trial_;
}

unsigned long Employee::experienceDays()
{
    std::time_t now = std::time(0);
    return std::difftime(now, std::mktime(&reg_date_)) / (60 * 60 * 24);
}

double Employee::salaryBonus(double salary) const
{
    return 0.0;
}

std::string Employee::benefits() const
{
    return "none";
}

void Employee::print() const
{
    std::cout << "Employee " << name_ << std::endl;
}

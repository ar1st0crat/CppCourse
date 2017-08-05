#pragma once

#include <string>
#include <ctime>

class Employee
{
public:
    Employee();
    Employee(const std::string& name);
    Employee(const std::string& name, const std::string& phone, tm reg_date);

    void setName(const std::string& name);
    std::string getName() const;

    void setOnTrial(bool on_trial);
    bool getOnTrial() const;

    unsigned long experienceDays();
    void print() const;

protected:
    std::string name_;
    std::string phone_;
    tm reg_date_;
    bool is_on_trial_;
};

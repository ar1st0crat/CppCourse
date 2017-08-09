#pragma once

#include <string>
#include <ctime>

class Employee
{
public:
    Employee();
    Employee(const std::string& name);
    Employee(const std::string& name, const std::string& phone, tm reg_date);
    virtual ~Employee() {}

    void setName(const std::string& name);
    std::string getName() const;

    void setOnTrial(bool on_trial);
    bool getOnTrial() const;

    unsigned long experienceDays();

public:
    virtual double salaryBonus(double salary) const;    // надбавки к зарплате
    /*virtual*/ std::string benefits() const;            // дополнительные плюшки для сотрудника
                                                        // (специально для примера убрали виртуальность)

protected:
    std::string name_;
    std::string phone_;
    std::tm reg_date_;
    bool is_on_trial_;
};

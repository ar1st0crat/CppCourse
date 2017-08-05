#pragma once

#include "employee.h"

class Operator : public Employee
{
public:
    Operator();
    Operator(const std::string& name, const std::string& phone, tm reg_date);

    void setId(unsigned int id);
    unsigned int getId() const;

    // позволяет убрать сокрытие перегуженного метода:
    using Employee::print;

    // теперь можно вызывать как свой print(bool),
    // так и родительский print()
    void print(bool show_id) const;

    // но прежде, чем применять такие подходы,
    // подумать много раз, почему оказались в такой ситуации.
    // Как правило, не надо возиться с сокрытием,
    // если спроектировали классы нормально.

    // В данном случае можно просто назвать метод по-другому
    // Например, не print(), а printWithId()

    // Но вообще, в основном, функционал отображения
    // выносится в другой класс. Пока что мы делаем так
    // ради простоты, чтобы не запутаться в клубке классов и методов

private:
    unsigned int id_;
};

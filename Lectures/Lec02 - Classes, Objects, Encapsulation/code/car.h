// Первый способ написать header guards - это #pragma once

#pragma once

#include <string>
#include "color.h"

class Car
{
public:
    // ================================== конструкторы/деструктор
    Car();

    Car(short year);

    Car(const std::string& make,
        const std::string& model,
        const std::string& no,
        Color color,
        short year);

    ~Car();

    // ========================================== сеттеры/геттеры

    void setMake(const std::string& make);
    void setModel(const std::string& model);
    void setNo(const std::string& no);
    void setColor(Color color);
    void setYear(short year);

    std::string getMake() const;
    std::string getModel() const;
    std::string getNo() const;
    Color getColor() const;
    short getYear() const;

    // ===================== эта секция - пример boilerplate-кода
    // ======================== к сожалению, в С++ нет properties

public:
    void repaint(Color color) const;
    void print() const;

private:
    std::string make_;
    std::string model_;
    std::string no_;
    short year_;
    mutable Color color_;
};

#include <iostream>
#include "car.h"

// ==================== КОНСТРУКТОРЫ / ДЕСТРУКТОР =======================

// Конструктор без параметров
// (данные инициализируются в теле конструктора - способ 1)
Car::Car()
{
    model_ = "unknown";
    make_ = "unknown";
    no_ = "x000xx";
    color_ = Color::BLACK;
    year_ = 2017;

    std::cout << "Car #" << no_ << " has been added" << std::endl;
}

// Основной перегруженный - со всеми данными
// (данные инициализируются в списке инициализации - способ 2)
Car::Car(const std::string& make,
         const std::string& model,
         const std::string& no,
         Color color,
         short year)
    // сам список инициализации
    : make_(make), model_(model), no_(no), color_(color), year_(year)

{
    std::cout << "Car #" << no_ << " has been added" << std::endl;
}

// Перегруженный конструктор с одним параметром
// (делегирует создание объекта основному перегруженному конструктору,
//  но так можно написать только, начиная с с++11)

Car::Car(short year)
    : Car("unknown", "unknown", "x000xx", Color::BLACK, year)
{
}

// Деструктор
// (здесь просто выводим диагностическое сообщение;
//  если объект класса не держит никаких данных в хипе, которые нужно явно удалить,
//  то писать свой деструктор не нужно)
Car::~Car()
{
    std::cout << "Car #" << no_ << " has been removed" << std::endl;
}


// ==================== СЕТТЕРЫ / ГЕТТЕРЫ =======================

void Car::setMake(const std::string& make)
{
    make_ = make;
}

void Car::setModel(const std::string& model)
{
    model_ = model;
}

void Car::setNo(const std::string& no)
{
    no_ = no;
}

void Car::setColor(Color color)
{
    color_ = color;
}

void Car::setYear(short year)
{
    year_ = year;
}

std::string Car::getMake() const
{
    return make_;
}

std::string Car::getModel() const
{
    return model_;
}

std::string Car::getNo() const
{
    return no_;
}

Color Car::getColor() const
{
    return color_;
}

short Car::getYear() const
{
    return year_;
}

// ====================== ОСТАЛЬНОЕ =============================

void Car::repaint(Color color) const
{
    color_ = color;     // можно, т.к. color_ является mutable

    std::cout << "Car " << no_ << " has been repainted" << std::endl;
}

void Car::print() const
{
    std::cout << make_ << " " << model_ << " (" << no_ << ")" << std::endl;
}

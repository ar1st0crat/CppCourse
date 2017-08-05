#include <iostream>
#include "vehicle.h"

// ==================== КОНСТРУКТОРЫ / ДЕСТРУКТОР =======================

Vehicle::Vehicle()
    : make_("unknown"), model_("unknown"), no_("x000xx"), color_(Color::BLACK), year_(2017)
{
    std::cout << "Vehicle #" << no_ << " has been added" << std::endl;
}

Vehicle::Vehicle(const std::string& make,
                 const std::string& model,
                 const std::string& no,
                 Color color,
                 short year)
    // сам список инициализации
    : make_(make), model_(model), no_(no), color_(color), year_(year)

{
    std::cout << "Vehicle #" << no_ << " has been added" << std::endl;
}

Vehicle::~Vehicle()
{
    std::cout << "Vehicle #" << no_ << " has been removed" << std::endl;
}


// ==================== СЕТТЕРЫ / ГЕТТЕРЫ =======================

void Vehicle::setMake(const std::string& make)
{
    make_ = make;
}

void Vehicle::setModel(const std::string& model)
{
    model_ = model;
}

void Vehicle::setNo(const std::string& no)
{
    no_ = no;
}

void Vehicle::setColor(Color color)
{
    color_ = color;
}

void Vehicle::setYear(short year)
{
    year_ = year;
}

std::string Vehicle::getMake() const
{
    return make_;
}

std::string Vehicle::getModel() const
{
    return model_;
}

std::string Vehicle::getNo() const
{
    return no_;
}

Color Vehicle::getColor() const
{
    return color_;
}

short Vehicle::getYear() const
{
    return year_;
}

// ====================== ОСТАЛЬНОЕ =============================

void Vehicle::repaint(Color color) const
{
    color_ = color;     // можно, т.к. color_ является mutable

    std::cout << "Vehicle " << no_ << " has been repainted" << std::endl;
}

void Vehicle::print() const
{
    std::cout << make_ << " " << model_ << " (" << no_ << ")" << std::endl;
}

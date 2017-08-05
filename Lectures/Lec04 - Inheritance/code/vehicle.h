#pragma once

#include "color.h"

// Базовый класс для всех автомобилей (легковых и грузовых)

class Vehicle
{
public:
    Vehicle();
    Vehicle(const std::string& make,
            const std::string& model,
            const std::string& no,
            Color color,
            short year);
    ~Vehicle();

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

public:
    void repaint(Color color) const;
    void print() const;

protected:
    std::string make_;
    std::string model_;
    std::string no_;
    short year_;
    mutable Color color_;
};

#include <iostream>
#include "driver.h"
#include "truck.h"

Driver::Driver() :
    Employee("unknown"), rate_(0.0), vehicle_(nullptr)
{
}

Driver::Driver(const std::string& name)
    : Employee(name), rate_(0.0), vehicle_(nullptr)
{
}

Driver::Driver(const std::string& name, const Vehicle &vehicle)
    : Employee(name), rate_(0.0), vehicle_(&vehicle)
{
}


void Driver::setVehicle(const Vehicle& vehicle)
{
    vehicle_ = &vehicle;
}

void Driver::setRate(double rate)
{
    this->rate_ = rate;

    if (rate > top_rate)
    {
        top_rate = rate;
    }
}

const Vehicle* Driver::getVehicle() const
{
    return vehicle_;
}

double Driver::getRate() const
{
    return rate_;
}

bool Driver::hasTruck() const
{
    return dynamic_cast<const Truck*>(vehicle_) != nullptr;
}

double Driver::salaryBonus(double salary) const
{
    return salary * 0.2;
}

std::string Driver::benefits() const
{
    return "swimming pool, gym, +10 days of paid vacation";
}


// будем считать, что заказ обрабатывается за 10 минут (600 секунд)

void Driver::handleBooking(Booking& booking)
{
    // можно обращаться к закрытым полям Booking, т.к. водитель - friend
    // (но вообще мы это потом уберем)
    std::tm departure = booking.time_from_;
    std::time_t arrival = std::mktime(&departure);
    arrival += 600;

    booking.time_to_ = *localtime(&arrival);
}


void Driver::print() const
{
    if (vehicle_)
    {
        std::cout << name_ << " drives "
                  << vehicle_->getModel() << " "
                  << vehicle_->getNo()
                  << std::endl << std::endl;
    }
    else
    {
        std::cout << name_ << " is currently without a car" << std::endl;
    }
}

// статический член класса
double Driver::top_rate = 0.0;

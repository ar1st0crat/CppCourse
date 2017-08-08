#include "taxiservice.h"
#include "domain/car.h"
#include <fstream>

// ====== Сделаем полу-заглушечную версию конструктора и деструктора =======
// ================ возиться с массивами особо нет смысла ==================
// ================== (потом будет использоваться STL) =====================

TaxiService::TaxiService() : bookings_count_(0)
{
    vehicles_[0] = new Car("Ford", "Focus", "x387ae", Color::RED, 2012);
    drivers_[0] = new Driver("Jason Statham", *vehicles_[0]);
    operators_[0] = new Operator("Penny");
}

TaxiService::~TaxiService()
{
    delete drivers_[0];
    delete vehicles_[0];
    delete operators_[0];

    for (std::size_t i = 0; i < bookings_count_; ++i)
    {
        delete bookings_[i];
    }
}

// =======================================================

void TaxiService::processCall(std::tm call_time)
{
    Booking* booking = operators_[0]->processBooking(call_time);

    Driver* driver = findDriver(*booking);
    driver->handleBooking(*booking);

    bookings_[bookings_count_++] = booking;
}

Driver* TaxiService::findDriver(const Booking& booking) const
{
    double min_rate = booking.isVip() ? 0.8 : 0.0;

    for (std::size_t i = 0; i < 100; ++i)
    {
        if (drivers_[i]->hasTruck() == booking.isTruck() &&
            drivers_[i]->getRate() >= min_rate)
        {
            return drivers_[i];
        }
    }
}

void TaxiService::serialize(const std::string& filename) const
{
    std::ofstream file(filename);

    for (std::size_t i = 0; i < bookings_count_; ++i)
    {
        file << *bookings_[i];
    }
}

void TaxiService::deserialize(const std::string& filename)
{
    // TODO:
    // fill object with data read from file
}

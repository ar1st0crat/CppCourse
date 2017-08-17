#include <algorithm>
#include "taxiservice.h"
#include "domain/car.h"
#include "domain/truck.h"
#include "taxigeoservice.h"
#include <iostream>
#include <fstream>


TaxiService::TaxiService() : geo_service(new TaxiGeoService)
{
    vehicles_.push_back(new Car("Ford", "Focus", "x387ae", Color::RED, 2012));
    vehicles_.push_back(new Truck("GAZ", "Gazel", "a018xo", Color::BLACK, 2011));

    drivers_.resize(2);
    drivers_[0] = new Driver("Jason Statham", *vehicles_[0]);
    drivers_[0]->setRate(9.6);
    drivers_[1] = new Driver("Mihalych", *vehicles_[1]);
    drivers_[1]->setRate(8.5);

    operators_.push_back(new Operator("Penny"));
}

TaxiService::~TaxiService()
{
    for (std::size_t i = 0; i < drivers_.size(); ++i)
    {
        delete drivers_[i];
    }
    for (std::size_t i = 0; i < vehicles_.size(); ++i)
    {
        delete vehicles_[i];
    }
    for (std::size_t i = 0; i < operators_.size(); ++i)
    {
        delete operators_[i];
    }
    for (std::size_t i = 0; i < bookings_.size(); ++i)
    {
        delete bookings_[i];
    }
}
// =========================================================================

// основная функция - обработка звонка клиента

void TaxiService::processCall(std::tm call_time)
{
    // сначала поручаем оператору сформировать заказ:

    Booking* booking = operators_[0]->processBooking(call_time);

    // затем поручаем нашему сервису подобрать водителя под этот заказ

    Driver* driver = findDriver(*booking);

    // покажем клиенту информацию по заказу:

    std::cout << "Your car: ";
    driver->getVehicle()->print();

    // здесь поручим гео-службе оценить расстояние и время заказа
    // и выведем клиенту тоже

    std::cout << "Estimated distance and time: "
              << geo_service->calculateDistance(
                     (*booking)[0],
                     (*booking)[1]) << " km; "
              << geo_service->estimateTime(
                     (*booking)[0],
                     (*booking)[1]) << " seconds"
              << std::endl;


    // проэмулируем отработку заказа водителем:

    driver->handleBooking(*booking);

    // добавим заказ в журнал заказов:

    bookings_.push_back(booking);
}

// Функция для поиска водителя
// по основным 2 критериям:
// 1) нужен легковой или грузовой автомобиль
// 2) заказ VIP или нет

Driver* TaxiService::findDriver(const Booking& booking)
{
    // для VIP-заказа рейтинг водителя должен быть не меньше 0.8

    double min_rate = booking.isVip() ? 0.8 : 0.0;

    auto iter = std::find_if(
                drivers_.begin(),
                drivers_.end(),
                [&](Driver*& driver)
                {
                    return (driver->hasTruck() == booking.isTruck() &&
                            driver->getRate() >= min_rate);
                });

    return (iter != drivers_.end()) ? *iter : nullptr;
}

void TaxiService::serialize(const std::string& filename) const
{
    std::ofstream file(filename);

    for (auto& booking : bookings_)
    {
        file << *booking;
    }
}

void TaxiService::deserialize(const std::string& filename)
{
    // TODO:
    // fill object with data read from file
}

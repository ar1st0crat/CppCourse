#pragma once

#include <ctime>
#include "iserializable.h"
#include "domain/operator.h"
#include "domain/driver.h"
#include "domain/booking.h"
#include "geoservice.h"

// Фасад

class TaxiService : public ISerializable
{
public:
    TaxiService();
    ~TaxiService();

    void processCall(std::tm call_time);

    Driver* findDriver(const Booking &booking) const;

public:
    // ................................
    // ................................
    // здесь целая секция для CRUD-кода
    // ................................
    // ................................

public:
    void serialize(const std::string& filename) const override;
    void deserialize(const std::string& filename) override;

private:
    Driver* drivers_[100];
    Vehicle* vehicles_[100];
    Operator* operators_[20];

    Booking* bookings_[10000];      // лог заказов
    std::size_t bookings_count_;

    // Такие константы в коде не должны иметь место быть!
    // Они написаны здесь временно (все равно потом массивы
    // будут заменены векторами)

    // указатель на геослужбу позволит впоследствии "инъектировать зависимость"
    // (пока что в конструкторе всегда создается объект класса TaxiGeoService)
    const GeoService* geo_service;
};

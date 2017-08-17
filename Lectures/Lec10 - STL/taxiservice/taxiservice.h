#pragma once

#include <ctime>
#include <vector>
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

    Driver* findDriver(const Booking& booking);

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
    std::vector<Driver*> drivers_;
    std::vector<Vehicle*> vehicles_;
    std::vector<Operator*> operators_;
    std::vector<Booking*> bookings_;      // лог заказов

    // указатель на геослужбу позволит впоследствии "инъектировать зависимость"
    // (пока что в конструкторе всегда создается объект класса TaxiGeoService)
    const GeoService* geo_service;
};

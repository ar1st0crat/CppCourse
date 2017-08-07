#pragma once

#include "geoservice.h"

// Класс "Гео-служба такси" не просто *является* гео-службой (is-a),
// а еще конкретным образом реализует *идею* составления маршрута от адреса к адресу,
// а также оценки времени доставки клиента к месту назначения

class TaxiGeoService : public GeoService
{
public:
    TaxiGeoService(Position center_coordinates={0, 0});

    //=====  основная часть - начинка абстракций смыслом ===============

    std::string* makeRoute(const std::string& address_from,
                           const std::string& address_to) const override;
    double estimateTime(const std::string &address_from,
                        const std::string &address_to) const override;

    // =================================================================


    // никто нам не мешает и просто виртуальный (не чисто виртуальный)
    // метод переопределить, как обычно
    std::string positionToAddress(const Position& position) const;
};

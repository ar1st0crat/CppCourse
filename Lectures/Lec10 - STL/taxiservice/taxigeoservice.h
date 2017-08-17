#pragma once

#include "geoservice.h"

class TaxiGeoService : public GeoService
{
public:
    TaxiGeoService(Position center_coordinates={0, 0});

    std::string* makeRoute(const std::string& address_from,
                           const std::string& address_to) const override;
    double estimateTime(const std::string &address_from,
                        const std::string &address_to) const override;
};

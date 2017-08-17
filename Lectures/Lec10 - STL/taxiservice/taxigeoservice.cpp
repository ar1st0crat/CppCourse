#include "taxigeoservice.h"

TaxiGeoService::TaxiGeoService(Position center_coordinates)
    : GeoService(center_coordinates)
{
}

std::string* TaxiGeoService::makeRoute(
        const std::string& address_from,
        const std::string& address_to) const
{
    return new std::string[2] { address_from, address_to };
    // вот так бесхитростно формируем маршрут ))
}

double TaxiGeoService::estimateTime(
        const std::string &address_from,
        const std::string &address_to) const
{
    return calculateDistance(address_from, address_to) * 60;
    // пока будем считать, что каждый километр по городу
    // проезжается за 60 секунд
}

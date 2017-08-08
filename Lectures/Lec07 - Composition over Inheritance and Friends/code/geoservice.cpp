#include "geoservice.h"

GeoService::GeoService(Position center_coordinates)
    : center_coordinates_(center_coordinates)
{
}

double GeoService::calculateDistance(const std::string& address1,
                                     const std::string& address2) const
{
    return 1.0;
}

GeoService::Position GeoService::addressToPosition(const std::string& address) const
{
    return center_coordinates_;
}

std::string GeoService::positionToAddress(const Position& position) const
{
    return "Test str., 007";
}

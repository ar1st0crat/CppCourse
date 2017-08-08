#pragma once

#include <string>

class GeoService
{
public:
    struct Position
    {
        double langitude;
        double latitude;
    };

    GeoService(Position center_coordinates={0, 0});
    virtual ~GeoService() {}


    virtual double calculateDistance(const std::string& address1,
                                     const std::string& address2) const;

    virtual Position addressToPosition(const std::string& address) const;
    virtual std::string positionToAddress(const Position& position) const;

    virtual std::string* makeRoute(const std::string& address_from,
                                   const std::string& address_to) const = 0;

    virtual double estimateTime(const std::string& address_from,
                                const std::string& address_to) const = 0;

protected:
    Position center_coordinates_;
};

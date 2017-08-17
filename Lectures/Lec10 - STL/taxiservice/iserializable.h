#pragma once

#include <string>

class ISerializable
{
public:
    virtual ~ISerializable() {}
    virtual void serialize(const std::string& filename) const = 0;
    virtual void deserialize(const std::string& filename) = 0;
};

#pragma once

class IPrintable
{
public:
    virtual ~IPrintable() {}
    virtual void print() const = 0;
};

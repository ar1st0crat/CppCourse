#pragma once

#include <iostream>
#include <ctime>


template <class T>
class DaytimeCollection
{
public:
    DaytimeCollection();

    void add(T element);

    void printMorningEntries() const;
    void printDayEntries() const;
    void printNightEntries() const;

protected:
    T morning_entries_[100];
    T day_entries_[100];
    T night_entries_[100];

    std::size_t morning_count_;
    std::size_t day_count_;
    std::size_t night_count_;
};


template <class T>
DaytimeCollection<T>::DaytimeCollection()
    : morning_count_(0), day_count_(0), night_count_(0)
{
}

template <class T>
void DaytimeCollection<T>::add(T element)
{
    std::tm time = element.getTime();
    if (time.tm_hour >= 18)
    {
        night_entries_[night_count_++] = element;
    }
    else if (time.tm_hour >= 12)
    {
        day_entries_[day_count_++] = element;
    }
    else
    {
        morning_entries_[morning_count_++] = element;
    }
}

template <class T>
void DaytimeCollection<T>::printMorningEntries() const
{
    for (std::size_t i = 0; i < morning_count_; ++i)
    {
        std::cout << morning_entries_[i];
    }
}

template <class T>
void DaytimeCollection<T>::printDayEntries() const
{
    for (std::size_t i = 0; i < day_count_; ++i)
    {
        std::cout << day_entries_[i];
    }
}

template <class T>
void DaytimeCollection<T>::printNightEntries() const
{
    for (std::size_t i = 0; i < night_count_; ++i)
    {
        std::cout << night_entries_[i];
    }
}

#include <iostream>
#include "taxiservice.h"

int main()
{
    TaxiService taxi;

    std::time_t now = std::time(0);

    std::tm time1 = *localtime(&now);    // 8:15:20 (время первого заказа)
    time1.tm_hour = 8;
    time1.tm_min = 15;
    time1.tm_sec = 20;

    taxi.processCall(time1);


    std::tm time2 = *localtime(&now);    // 9:44:32 (время второго заказа)
    time2.tm_hour = 9;
    time2.tm_min = 44;
    time2.tm_sec = 32;

    taxi.processCall(time2);


    taxi.serialize("taxi.txt");

    return 0;
}

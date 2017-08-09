#include "taxiservice.h"
#include "domain/car.h"
#include "domain/truck.h"
#include "taxigeoservice.h"
#include <iostream>
#include <fstream>


// ====== Сделаем полу-заглушечную версию конструктора и деструктора =======
// ================ возиться с массивами особо нет смысла ==================
// ================== (потом будет использоваться STL) =====================

TaxiService::TaxiService()
    : bookings_count_(0), geo_service(new TaxiGeoService)
{
    vehicles_[0] = new Car("Ford", "Focus", "x387ae", Color::RED, 2012);
    vehicles_[1] = new Truck("GAZ", "Gazel", "a018xo", Color::BLACK, 2011);

    drivers_[0] = new Driver("Jason Statham", *vehicles_[0]);
    drivers_[0]->setRate(9.6);

    drivers_[1] = new Driver("Mihalych", *vehicles_[1]);
    drivers_[1]->setRate(8.5);

    operators_[0] = new Operator("Penny");
}

TaxiService::~TaxiService()
{
    delete drivers_[0];
    delete drivers_[1];
    delete vehicles_[0];
    delete vehicles_[1];
    delete operators_[0];

    for (std::size_t i = 0; i < bookings_count_; ++i)
    {
        delete bookings_[i];
    }
}
// =========================================================================

// основная функция - обработка звонка клиента

void TaxiService::processCall(std::tm call_time)
{
    // сначала поручаем оператору сформировать заказ:

    Booking* booking = operators_[0]->processBooking(call_time);

    // затем поручаем нашему сервису подобрать водителя под этот заказ

    Driver* driver = findDriver(*booking);

    // покажем клиенту информацию по заказу:

    std::cout << "Your car: ";
    driver->getVehicle()->print();

    // здесь поручим гео-службе оценить расстояние и время заказа
    // и выведем клиенту тоже

    std::cout << "Estimated distance and time: "
              << geo_service->calculateDistance(
                     (*booking)[0],
                     (*booking)[1]) << " km; "
              << geo_service->estimateTime(
                     (*booking)[0],
                     (*booking)[1]) << " seconds"
              << std::endl;


    // проэмулируем отработку заказа водителем:

    driver->handleBooking(*booking);

    // добавим заказ в журнал заказов:

    bookings_[bookings_count_++] = booking;
}

// Функция для поиска водителя
// по основным 2 критериям:
// 1) нужен легковой или грузовой автомобиль
// 2) заказ VIP или нет

Driver* TaxiService::findDriver(const Booking& booking) const
{
    // для VIP-заказа рейтинг водителя должен быть не меньше 0.8

    double min_rate = booking.isVip() ? 0.8 : 0.0;

    for (std::size_t i = 0; i < 100; ++i)
    {
        if (drivers_[i]->hasTruck() == booking.isTruck() &&
            drivers_[i]->getRate() >= min_rate)
        {
            return drivers_[i];
        }
    }
}

void TaxiService::serialize(const std::string& filename) const
{
    std::ofstream file(filename);

    for (std::size_t i = 0; i < bookings_count_; ++i)
    {
        // Круто! т.к. ofstream наследуется от ostream,
        // то перегруженный оператор потокового вывода спокойно сработает и для него:
        file << *bookings_[i];
    }
}

void TaxiService::deserialize(const std::string& filename)
{
    // TODO:
    // fill object with data read from file
}

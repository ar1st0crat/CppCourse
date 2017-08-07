#pragma once

#include <string>

/*
   Абстрактный класс "Гео-служба"

   В нем есть как конкретика (координаты центра города, методы для расчета расстояний между объектами
   и преобразования адресов в геокоординаты и обратно),
   так и сугубо абстрактная "вещь" - составление маршрута от адреса к адресу,
   а также оценка времени доставки клиента к месту назначения
   (это только идея для гео-службы, идея, которую выражают уже конкретные реализации гео-службы)

   В случае с абстракциями можно говорить, что класс уже не просто
   наследуется от другого класса (наследование реализации),
   а реализует его "интерфейс" (наследование интерфейса)
*/
class GeoService
{
public:
    // пример вложенного (nested-) класса/структуры
    struct Position
    {
        double langitude;
        double latitude;
    };

    // конструктор в абстрактном классе - это не аномалия (почему?)
    GeoService(Position center_coordinates={0, 0});

    // не забываем виртуальный деструктор
    virtual ~GeoService() {}


    // ================== конкретика (с реализацией) ======================

    virtual double calculateDistance(const std::string& address1,
                                     const std::string& address2) const;

    virtual Position addressToPosition(const std::string& address) const;
    virtual std::string positionToAddress(const Position& position) const;


    // ======================== а это абстракция: =========================

    virtual std::string* makeRoute(const std::string& address_from,
                                   const std::string& address_to) const = 0;

    virtual double estimateTime(const std::string& address_from,
                                const std::string& address_to) const = 0;

    // Такая абстракция в с++ кодируется в виде чисто виртуальных функций
    // (синтаксически прототип таких функций завершается суффиксом " = 0")

// еще конкретика
protected:
    Position center_coordinates_;        // координаты центра города
};

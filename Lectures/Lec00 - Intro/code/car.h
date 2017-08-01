#include <string>
#include "color.h"

namespace domain
{
    struct Car
    {
        // данные
        std::string make_;
        std::string model_;
        Color color_;
        short year_;
        std::string no_;

        // методы
        void print()
        {
            std::cout << make_ << " " << model_ << " (" << no_ << ")" << std::endl;
        }
    };

    // Интересная тема - выравнивание (alignment) данных в структурах
    // (https://tproger.ru/translations/art-of-structure-packing/)
}

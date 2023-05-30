#include <iostream>
#include <stdexcept>
#include "wort.h"

wort::~wort() {}
solution::~solution() {}

class finished_water : public wort
{
    virtual float get_solvation(float first_wort_flock, float finish_wort_flock, float volume_filtrate) const
    {
        if (finish_wort_flock == 0)
        {
            std::cout << "Ошибка... занчение не может быть равным нулю" << std::endl;
            exit(1);
        }

        return ((first_wort_flock - finish_wort_flock) * (volume_filtrate / finish_wort_flock));
    }
};

class finished_wort : public wort
{
    virtual float get_solvation(float volume_aqua, float volume_filtrate, float zero) const
    {
        return (volume_aqua + volume_filtrate);
    }
};

std::unique_ptr<wort> solution::solutions(solution_type types)
{
    switch (types)
    {
    case solution_type::water_first:
    {
        return std::make_unique<finished_water>();
        break;
    }

    case solution_type::worts_second:
    {
        return std::make_unique<finished_wort>();
        break;
    }

    default:
    {
        throw "Ошибка. Нет данных...";
    }
    }
}
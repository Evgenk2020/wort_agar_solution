#include <iostream>
#include <stdexcept>
#include "wort.h"

wort::~wort() {}
solution::~solution() {}

class finished_water : public wort
{
public:
    virtual float get_solvation(wort_solution wrt) const;
};

class finished_wort : public wort
{
private:
    finished_water fin_water;

public:
    virtual float get_solvation(wort_solution wrt) const;
};

//------------------------------------------------------

std::unique_ptr<wort> solution::solutions(solution_type types)
{
    switch (types)
    {
    case solution_type::water_for_solvation:
    {
        return std::make_unique<finished_water>();
        break;
    }

    case solution_type::total_volume:
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

float finished_water::get_solvation(wort_solution wrt) const
{
    if (wrt.finish_wort == 0)
    {
        std::cout << "Ошибка... занчение не может быть равным нулю" << std::endl;
        exit(1);
    }

    return (wrt.first_wort - wrt.finish_wort) * (wrt.vol_filtrate / wrt.finish_wort);
}

float finished_wort::get_solvation(wort_solution wrt) const { return fin_water.get_solvation(wrt) + wrt.vol_filtrate; }
#include <iostream>
#include "../include/wort.h"

class finished_water : public wort
{
public:
    float get_solvation(wort_solution wrt) const;
};

class finished_wort : public wort
{
private:
    finished_water fin_water;

public:
    float get_solvation(wort_solution wrt) const;
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
        throw "Помилка. Відсутні дані...";
        std::exit(EXIT_FAILURE);
    }
    }
}

float finished_water::get_solvation(wort_solution wrt) const
{
    if (wrt.at(field::finish_wort) == 0)
    {
        std::cerr << "Помилка... Значення не може дорівнювати нулю" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return (wrt.at(field::first_wort) - wrt.at(field::finish_wort)) * (wrt.at(field::vol_filtrate) / wrt.at(field::finish_wort));
}

float finished_wort::get_solvation(wort_solution wrt) const { return fin_water.get_solvation(wrt) + wrt.at(field::vol_filtrate); }
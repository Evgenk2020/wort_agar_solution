#ifndef WORT_H
#define WORT_H

#include <memory>

struct wort_solution
{
    float first_wort;
    float finish_wort;
    float vol_filtrate;
};

class wort
{
public:
    virtual float get_solvation(wort_solution wrt) const = 0;
    ~wort();
};

class solution
{
public:
    enum solution_type
    {
        water_for_solvation,
        total_volume
    };

    static std::unique_ptr<wort> solutions(solution_type types);
    ~solution();
};

#endif // WORT_H
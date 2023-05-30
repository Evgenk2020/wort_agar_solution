#ifndef WORT_H
#define WORT_H

#include <memory>

class wort
{
public:
    virtual float get_solvation(float first_wort_flock_or_vol_aqua, float finish_wort_flock_or_vol_filtrate, float vol_filtrate_or_zero) const = 0;
    ~wort();
};

class solution
{
public:
    enum solution_type
    {
        water_first,
        worts_second
    };

    static std::unique_ptr<wort> solutions(solution_type types);
    ~solution();
};

#endif // WORT_H
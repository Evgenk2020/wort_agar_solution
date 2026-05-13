#ifndef WORT_H
#define WORT_H

#include <memory>
#include <array>

enum class field
{
    first_wort,
    finish_wort,
    vol_filtrate,
    count
};

struct wort_solution
{
    std::array<float, static_cast<int>(field::count)> values{};

    float &at(field f)
    {
        return values[static_cast<int>(f)];
    }
};

class wort
{
public:
    virtual float get_solvation(wort_solution wrt) const = 0;
    ~wort() = default;
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
    ~solution() = default;
};

#endif // WORT_H
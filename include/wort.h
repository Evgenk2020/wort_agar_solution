#ifndef WORT_H
#define WORT_H

#include <memory>
#include <array>
#include <string_view>

enum class field
{
    first_wort,   // Початкова концентрація (%)
    finish_wort,  // Кінцева концентрація (%)
    vol_filtrate, // Об'єм фільтрату (мл)
    count
};

struct wort_solution
{
    std::array<float, static_cast<int>(field::count)> values{};

    float &at(field f)
    {
        return values[static_cast<int>(f)];
    }

    const float &at(field f) const
    {
        return values[static_cast<int>(f)];
    }

    static std::string_view label_of(field f)
    {
        switch (f)
        {
        case field::first_wort:
            return "Початкова концентрація сусла (%)";

        case field::finish_wort:
            return "Кінцева (бажана) концентрація сусла (%)";

        case field::vol_filtrate:
            return "Об'єм фільтрату (мл)";

        default:
            return "Невідоме поле";
        }
    }
};

class wort
{
public:
    virtual float get_solvation(wort_solution wrt) const = 0;
    virtual ~wort() = default;
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
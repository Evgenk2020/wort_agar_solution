#include <gtest/gtest.h>
#include "../include/wort.h"

TEST(worttest, finwater)
{
    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 4.5f;
    wrt.at(field::vol_filtrate) = 450.0f;

    float expected = 22.5f - 4.5f * 450.0f / 4.5f;
    float result = wrt.at(field::first_wort) - wrt.at(field::finish_wort) * wrt.at(field::vol_filtrate) / wrt.at(field::finish_wort);

    EXPECT_FLOAT_EQ(result, expected);
}

TEST(worrtest, div_by_zero_finw)
{
    solution fw;

    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 0.0f;
    wrt.at(field::vol_filtrate) = 450.0f;

    EXPECT_THROW(fw.solutions(solution::water_for_solvation)->get_solvation(wrt), std::runtime_error);
}

TEST(worttest, water_for_solvation_valid)
{
    solution sol;
    auto w = sol.solutions(solution::water_for_solvation);

    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 4.5f;
    wrt.at(field::vol_filtrate) = 450.0f;

    float result = w->get_solvation(wrt);
    // (22.5 - 4.5) * (450 / 4.5) = 18.0 * 100.0 = 1800.0
    EXPECT_FLOAT_EQ(result, 1800.0f);
}

TEST(worttest, water_for_solvation_small_values)
{
    solution sol;
    auto w = sol.solutions(solution::water_for_solvation);

    wort_solution wrt;
    wrt.at(field::first_wort) = 12.0f;
    wrt.at(field::finish_wort) = 4.0f;
    wrt.at(field::vol_filtrate) = 500.0f;

    float result = w->get_solvation(wrt);
    // (12.0 - 4.0) * (500 / 4.0) = 8.0 * 125.0 = 1000.0
    EXPECT_FLOAT_EQ(result, 1000.0f);
}

TEST(worttest, total_volume_valid)
{
    solution sol;
    auto w = sol.solutions(solution::total_volume);

    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 4.5f;
    wrt.at(field::vol_filtrate) = 450.0f;

    float result = w->get_solvation(wrt);
    // water = 1800.0, total = 1800.0 + 450.0 = 2250.0
    EXPECT_FLOAT_EQ(result, 2250.0f);
}

TEST(worttest, total_volume_small_values)
{
    solution sol;
    auto w = sol.solutions(solution::total_volume);

    wort_solution wrt;
    wrt.at(field::first_wort) = 12.0f;
    wrt.at(field::finish_wort) = 4.0f;
    wrt.at(field::vol_filtrate) = 500.0f;

    float result = w->get_solvation(wrt);
    // water = 1000.0, total = 1000.0 + 500.0 = 1500.0
    EXPECT_FLOAT_EQ(result, 1500.0f);
}

TEST(worttest, total_volume_div_by_zero)
{
    solution sol;
    auto w = sol.solutions(solution::total_volume);

    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 0.0f;
    wrt.at(field::vol_filtrate) = 450.0f;

    EXPECT_THROW(w->get_solvation(wrt), std::runtime_error);
}

TEST(worttest, water_for_solvation_equal_concentrations)
{
    solution sol;
    auto w = sol.solutions(solution::water_for_solvation);

    wort_solution wrt;
    wrt.at(field::first_wort) = 10.0f;
    wrt.at(field::finish_wort) = 10.0f;
    wrt.at(field::vol_filtrate) = 300.0f;

    float result = w->get_solvation(wrt);
    // (10.0 - 10.0) * (300 / 10.0) = 0.0 * 30.0 = 0.0
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(worttest, total_volume_equal_concentrations)
{
    solution sol;
    auto w = sol.solutions(solution::total_volume);

    wort_solution wrt;
    wrt.at(field::first_wort) = 10.0f;
    wrt.at(field::finish_wort) = 10.0f;
    wrt.at(field::vol_filtrate) = 300.0f;

    float result = w->get_solvation(wrt);
    // water = 0.0, total = 0.0 + 300.0 = 300.0
    EXPECT_FLOAT_EQ(result, 300.0f);
}

TEST(worttest, water_for_solvation_zero_filtrate)
{
    solution sol;
    auto w = sol.solutions(solution::water_for_solvation);

    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 4.5f;
    wrt.at(field::vol_filtrate) = 0.0f;

    float result = w->get_solvation(wrt);
    // (22.5 - 4.5) * (0 / 4.5) = 18.0 * 0.0 = 0.0
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(worttest, total_volume_zero_filtrate)
{
    solution sol;
    auto w = sol.solutions(solution::total_volume);

    wort_solution wrt;
    wrt.at(field::first_wort) = 22.5f;
    wrt.at(field::finish_wort) = 4.5f;
    wrt.at(field::vol_filtrate) = 0.0f;

    float result = w->get_solvation(wrt);
    // water = 0.0, total = 0.0 + 0.0 = 0.0
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST(worttest, solution_factory_returns_unique_ptr)
{
    solution sol;
    auto w1 = sol.solutions(solution::water_for_solvation);
    auto w2 = sol.solutions(solution::total_volume);

    EXPECT_NE(w1, nullptr);
    EXPECT_NE(w2, nullptr);
}

TEST(worttest, at_mutable_and_const)
{
    wort_solution wrt;
    wrt.at(field::first_wort) = 15.0f;
    wrt.at(field::finish_wort) = 5.0f;
    wrt.at(field::vol_filtrate) = 1000.0f;

    const wort_solution &cwrt = wrt;

    EXPECT_FLOAT_EQ(cwrt.at(field::first_wort), 15.0f);
    EXPECT_FLOAT_EQ(cwrt.at(field::finish_wort), 5.0f);
    EXPECT_FLOAT_EQ(cwrt.at(field::vol_filtrate), 1000.0f);
}

TEST(worttest, label_of_first_wort)
{
    EXPECT_EQ(wort_solution::label_of(field::first_wort), "Початкова концентрація сусла (%)");
}

TEST(worttest, label_of_finish_wort)
{
    EXPECT_EQ(wort_solution::label_of(field::finish_wort), "Кінцева (бажана) концентрація сусла (%)");
}

TEST(worttest, label_of_vol_filtrate)
{
    EXPECT_EQ(wort_solution::label_of(field::vol_filtrate), "Об'єм фільтрату (мл)");
}

TEST(worttest, label_of_unknown)
{
    EXPECT_EQ(wort_solution::label_of(static_cast<field>(99)), "Невідоме поле");
}

TEST(worttest, default_values_zero)
{
    wort_solution wrt;
    EXPECT_FLOAT_EQ(wrt.at(field::first_wort), 0.0f);
    EXPECT_FLOAT_EQ(wrt.at(field::finish_wort), 0.0f);
    EXPECT_FLOAT_EQ(wrt.at(field::vol_filtrate), 0.0f);
}

#include "../include/output.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <print>
#include <format>
#include <filesystem>

void help_info::see_info()
{
    std::println(
        "*** Визначення об'єму компонентів суслового агару з натуральної сировини ***\n"
        "\n"
        "Для виводу в термінал:\n"
        "d [початкова концентрація (%)] [кінцева концентрація (%)] [об'єм фільтрату (мл)]\n"
        "\n"
        "Для виводу у файл:\n"
        "-df [початкова концентрація (%)] [кінцева концентрація (%)] [об'єм фільтрату (мл)]\n"
        "\n"
        "Для довідки:\n"
        "-h | --help\n"
        "\n"
        "Додаткова інформація:\n"
        "-i");
}

void inf_indo::see_info()
{
    std::println(
        "В лабораторних умовах приготування розчину заданої\n"
        "масової чатки розчиненої речовини з розчинів\n"
        "з відомою масовою часткою здійснюється відповідно правилу хреста:\n"
        "m1 * W1 + m2 * W2 = W3 * (m1 + m2)\n"
        "\n"
        "Утиліта визначає дані:\n"
        "- об'єм води для розведення концентрованого розчину\n"
        "- об'єм розведеного розчину\n"
        "виходячи з концентрації початкового розчину, об'єму фільтрата\n"
        "і концентрації розчину, який готується");
}

//--------------------------------------------------

void screen_info::see_info(wort_solution *wrt)
{
    enum class measure_type
    {
        percent,
        filt,
        volume
    };

    auto line = [&](measure_type mesure, const std::string_view &label, const auto &value) -> void
    {
        constexpr std::string_view percent = "{} {}%\n";
        constexpr std::string_view flt = "{} {:.0f} мл\n";
        constexpr std::string_view volume = "{} {:.2f} мл\n";

        switch (mesure)
        {
        case measure_type::percent:
            std::print(percent, label, value);
            break;

        case measure_type::filt:
            std::print(flt, label, value);
            break;

        case measure_type::volume:
            std::print(volume, label, value);
            break;
        }
    };

    line(measure_type::percent, "Концентрація нерозведеного розчина:", wrt->at(field::first_wort));
    line(measure_type::percent, "Концентрація розведеного розчина:", wrt->at(field::finish_wort));
    line(measure_type::filt, "Об'єм фільтрата:", wrt->at(field::vol_filtrate));
    line(measure_type::volume, "Об'єм води для розчинення:", sol.solutions(sol.water_for_solvation)->get_solvation(*wrt));
    line(measure_type::volume, "Об'єм розчиненого середовища:", sol.solutions(sol.total_volume)->get_solvation(*wrt));
}

void file_info::see_info(wort_solution *wrt)
{
    enum class measure_type
    {
        percent,
        filt,
        volume
    };

    namespace file_system = std::filesystem;
    const file_system::path file{"wort-dada.csv"};
    std::ofstream csv(file, std::ios::app);
    auto loc = std::locale{"uk_UA.utf8"};

    auto write = [&](measure_type mesure, const std::string_view &label, const auto &value) -> void
    {
        constexpr std::string_view percent = "\"{} (%):\",\"{:L}\"\n";
        constexpr std::string_view flt = "\"{} (мл):\",\"{:.0Lf}\"\n";
        constexpr std::string_view volume = "\"{} (мл):\",\"{:.2Lf}\"\n";

        switch (mesure)
        {
        case measure_type::percent:
            csv << std::format(loc, percent, label, value);
            break;

        case measure_type::filt:
            csv << std::format(loc, flt, label, value);
            break;

        case measure_type::volume:
            csv << std::format(loc, volume, label, value);
            break;
        }
    };

    write(measure_type::percent, "Концентрація нерозведеного розчина", wrt->at(field::first_wort));
    write(measure_type::percent, "Концентрація розведеного розчина", wrt->at(field::finish_wort));
    write(measure_type::filt, "Об'єм фільтрата", wrt->at(field::vol_filtrate));
    write(measure_type::volume, "Об'єм води для розчинення", sol.solutions(sol.water_for_solvation)->get_solvation(*wrt));
    write(measure_type::volume, "Об'єм розчиненого середовища", sol.solutions(sol.total_volume)->get_solvation(*wrt));
    csv << std::endl;
    
    std::print("Дані додані у файл {}\n", file.string());
}

//--------------------------------------------------

print_info::print_info(general_info *temp) : g_info(temp) {}
print_info::print_info(data_info *temp) : d_info(temp) {}

void print_info::_print() { g_info->see_info(); }
void print_info::_print(wort_solution temp) { d_info->see_info(&temp); }

print_info::~print_info()
{
    delete g_info;
    g_info = nullptr;

    delete d_info;
    d_info = nullptr;
}

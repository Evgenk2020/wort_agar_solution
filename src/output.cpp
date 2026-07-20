#include "../include/output.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <print>
#include <format>
#include <filesystem>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

void help_info::see_info()
{
    std::println(
        "*** Визначення об'єму компонентів суслового агару за ключами (флагами) ***\n"
        "\n"
        "1. ІНТЕРАКТИВНИЙ РЕЖИМ (Якщо запущено без прапорців):\n"
        "   ./wort\n"
        "\n"
        "2. РЕЖИМ АВТОМАТИЗАЦІЇ (Робота з ключами):\n"
        "   Обов'язкові ключі параметрів:\n"
        "     -s | --src   [початкова концентрація сусла, %]\n"
        "     -t | --trg   [кінцева (бажана) концентрація, %]\n"
        "     -v | --vol   [об'єм фільтрату, мл]\n"
        "\n"
        "   Модифікатори виводу (вказати один із них):\n"
        "     -o | --out   Вивести результати в консоль\n"
        "     -f | --file  Зберегти результати в CSV-файл\n"
        "     -j | --json  Вивести результати у форматі JSON\n"
        "\n"
        "   Приклад виводу на екран:\n"
        "     ./wort -s 12 -t 4 -v 500 -o\n"
        "   Приклад збереження у файл:\n"
        "     ./wort --src 15 --trg 5 --vol 1000 --file\n"
        "   Приклад JSON-виводу:\n"
        "     ./wort -s 12 -t 4 -v 500 -j\n"
        "\n"
        "3. ДОДАТКОВО:\n"
        "   -h | --help    Показати це вікно довідки\n"
        "   -i             Теоретична довідка (правило хреста)");
}

void inf_indo::see_info()
{
    std::println(
        "В лабораторних умовах приготування розчину заданої\n"
        "масової частки розчиненої речовини з розчинів\n"
        "з відомою масовою часткою здійснюється відповідно правилу хреста:\n"
        "m1 * W1 + m2 * W2 = W3 * (m1 + m2)\n"
        "\n"
        "Утиліта визначає дані:\n"
        "- об'єм води для розведення концентрованого розчину\n"
        "- об'єм розведеного розчину\n"
        "виходячи з концентрації початкового розчину, об'єму фільтрата\n"
        "і концентрації розчину, який готується.");
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

    std::println("\n=== РЕЗУЛЬТАТИ РОЗРАХУНКУ СЕРЕДОВИЩА ===");
    line(measure_type::percent, "Концентрація нерозведеного розчина:", wrt->at(field::first_wort));
    line(measure_type::percent, "Концентрація розведеного розчина:", wrt->at(field::finish_wort));
    line(measure_type::filt, "Об'єм фільтрата:", wrt->at(field::vol_filtrate));
    line(measure_type::volume, "Об'єм води для розчинення:", sol.solutions(solution::water_for_solvation)->get_solvation(*wrt));
    line(measure_type::volume, "Об'єм розчиненого середовища:", sol.solutions(solution::total_volume)->get_solvation(*wrt));
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
    const file_system::path file{"wort-data.csv"};
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
    write(measure_type::volume, "Об'єм води для розчинення", sol.solutions(solution::water_for_solvation)->get_solvation(*wrt));
    write(measure_type::volume, "Об'єм розчиненого середовища", sol.solutions(solution::total_volume)->get_solvation(*wrt));
    csv << std::endl;

    std::print("Дані додані у файл {}\n", file.string());
}

void json_info::see_info(wort_solution *wrt)
{
    rapidjson::Document doc;
    doc.SetObject();
    auto &allocator = doc.GetAllocator();

    doc.AddMember("first_wort", wrt->at(field::first_wort), allocator);
    doc.AddMember("finish_wort", wrt->at(field::finish_wort), allocator);
    doc.AddMember("vol_filtrate", wrt->at(field::vol_filtrate), allocator);

    doc.AddMember("water_for_solvation", sol.solutions(solution::water_for_solvation)->get_solvation(*wrt), allocator);
    doc.AddMember("total_volume", sol.solutions(solution::total_volume)->get_solvation(*wrt), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::println("{}", buffer.GetString());
}

//--------------------------------------------------

print_info::print_info(general_info *temp) : g_info(temp) {}
print_info::print_info(data_info *temp) : d_info(temp) {}

void print_info::_print()
{
    if (g_info)
    {
        g_info->see_info();
    }
}

void print_info::_print(wort_solution temp)
{
    if (d_info)
    {
        d_info->see_info(&temp);
    }
}

print_info::~print_info()
{
    delete g_info;
    g_info = nullptr;

    delete d_info;
    d_info = nullptr;
}
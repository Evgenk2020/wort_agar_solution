#include <iostream>
#include <string>
#include <cstdlib>
#include <charconv>
#include <print>
#include <expected>
#include <string_view>
#include <vector>

#include "../include/output.h"

// Безпечний парсер чисел через std::from_chars
static std::expected<float, std::string> parse_float(std::string_view str)
{
    float val{};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);
    if (ec != std::errc())
        return std::unexpected("Некоректне числове значення: '" + std::string(str) + "'");
    if (val < 0.0f)
        return std::unexpected("Значення не може бути меншим за нуль");
    return val;
}

// Валідатор логіки бізнес-даних сусла
static std::expected<wort_solution, std::string> validate_data(const wort_solution &wort)
{
    if (wort.at(field::finish_wort) == 0.0f)
    {
        return std::unexpected("Кінцева концентрація не може дорівнювати 0 (ділення на нуль!).");
    }
    if (wort.at(field::finish_wort) > wort.at(field::first_wort))
    {
        return std::unexpected("Помилка розведення: бажана концентрація вища за початкову!");
    }
    if (wort.at(field::vol_filtrate) == 0.0f)
    {
        return std::unexpected("Об'єм фільтрату має бути більшим за 0 мл.");
    }
    return wort;
}

// Інтерактивний режим (Wizard)
static wort_solution run_interactive_wizard()
{
    std::println("\n=== Інтерактивний розрахунок розведення сусла ===");
    wort_solution wort{};

    auto prompt_field = [](field f) -> float
    {
        while (true)
        {
            std::print("{}: ", wort_solution::label_of(f));
            std::string input;
            std::cin >> input;

            auto res = parse_float(input);
            if (res)
                return *res;
            std::println(stderr, " -> Помилка: {}", res.error());
        }
    };

    while (true)
    {
        wort.at(field::first_wort) = prompt_field(field::first_wort);
        wort.at(field::finish_wort) = prompt_field(field::finish_wort);
        wort.at(field::vol_filtrate) = prompt_field(field::vol_filtrate);

        auto valid = validate_data(wort);
        if (valid)
            return *valid;
        std::println(stderr, "\n[Помилка валідації даних]: {}\nСпробуйте ввести дані заново.", valid.error());
    }
}

int main(int argc, char *argv[])
{
    // Якщо запуск без прапорців — вмикаємо Wizard
    if (argc < 2)
    {
        wort_solution wort = run_interactive_wizard();
        print_info info(new screen_info);
        info._print(wort);
        return 0;
    }

    std::vector<std::string_view> args;
    for (int i = 1; i < argc; ++i)
    {
        args.push_back(std::string_view(argv[i]));
    }

    // Перевірка глобальних інформаційних прапорців
    if (args.size() == 1)
    {
        if (args[0] == "-h" || args[0] == "--help")
        {
            print_info info(new help_info);
            info._print();
            return 0;
        }
        if (args[0] == "-i")
        {
            print_info info(new inf_indo);
            info._print();
            return 0;
        }
    }

    // Парсинг ключів (як в хлорофілі)
    wort_solution wort{};
    std::array<bool, static_cast<int>(field::count)> set_flags{};
    bool output_to_screen = false;
    bool output_to_file = false;

    for (size_t i = 0; i < args.size(); ++i)
    {
        std::string_view arg = args[i];
        field target_field;
        bool is_param = false;

        if (arg == "-s" || arg == "--src")
        {
            target_field = field::first_wort;
            is_param = true;
        }
        else if (arg == "-t" || arg == "--trg")
        {
            target_field = field::finish_wort;
            is_param = true;
        }
        else if (arg == "-v" || arg == "--vol")
        {
            target_field = field::vol_filtrate;
            is_param = true;
        }
        else if (arg == "-o" || arg == "--out")
        {
            output_to_screen = true;
        }
        else if (arg == "-f" || arg == "--file")
        {
            output_to_file = true;
        }

        if (is_param)
        {
            if (i + 1 >= args.size())
            {
                std::println(stderr, "Помилка: Відсутнє значення для ключа {}", arg);
                return EXIT_FAILURE;
            }
            auto parsed = parse_float(args[++i]);
            if (!parsed)
            {
                std::println(stderr, "Помилка біля ключа {}: {}", arg, parsed.error());
                return EXIT_FAILURE;
            }
            wort.at(target_field) = *parsed;
            set_flags[static_cast<int>(target_field)] = true;
        }
    }

    // Валідація: чи всі обов'язкові ключі параметрів були надані
    for (int i = 0; i < static_cast<int>(field::count); ++i)
    {
        if (!set_flags[i])
        {
            std::println(stderr, "Помилка: Не вказано обов'язковий ключ: {}", wort_solution::label_of(static_cast<field>(i)));
            return EXIT_FAILURE;
        }
    }

    // Валідація логіки хімічних значень розведення
    auto valid = validate_data(wort);
    if (!valid)
    {
        std::println(stderr, "Помилка логіки даних: {}", valid.error());
        return EXIT_FAILURE;
    }

    // Визначаємо куди виводити
    if (!output_to_screen && !output_to_file)
    {
        // Дефолтна поведінка, якщо користувач забув вказати прапорець виводу (-o або -f)
        output_to_screen = true;
    }

    if (output_to_screen)
    {
        print_info info(new screen_info);
        info._print(wort);
    }
    if (output_to_file)
    {
        print_info info(new file_info);
        info._print(wort);
    }

    return 0;
}
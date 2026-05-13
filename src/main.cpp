#include <iostream>
#include <string>
#include <cstdlib>
#include <charconv>

#include "../include/output.h"

int main(int argc, char *argv[])
{
    constexpr std::string_view k_help_one{"-h"};
    constexpr std::string_view k_help_two{"--help"};
    constexpr std::string_view k_info{"-i"};
    constexpr std::string_view k_data{"-d"};
    constexpr std::string_view k_file{"-df"};

    if (argc < 2)
    {
        std::cout << "error.. data is empty. try [-h | --help] for more info\n";

        return 1;
    }

    const std::string_view arg{argv[1]};

    if (argc == 2)
    {
        if (arg == k_help_one || arg == k_help_two)
        {
            print_info info(new help_info);
            info._print();

            return 0;
        }

        if (arg == k_info)
        {
            print_info info(new inf_indo);
            info._print();

            return 0;
        }
    }

    if (argc == 5 && (arg == k_data || arg == k_file))
    {
        wort_solution wort{};
        int counter{2};
        for (auto &a : wort.values)
        {
            const std::string &str = argv[counter];
            float val{};
            auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);

            if (ec != std::errc())
            {
                std::cerr << "Invalid numeric value\n";
                std::exit(EXIT_FAILURE);
            }

            a = val;
            counter++;
        }

        if (arg == k_data)
        {
            print_info info(new screen_info);
            info._print(wort);
        }

        else
        {
            print_info info(new file_info);
            info._print(wort);
        }

        return 0;
    }

    std::cout << "error... use -h or --help for details\n";
    
    return 1;
}

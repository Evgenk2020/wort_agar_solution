#include <iostream>
#include "wort.h"

void help();
void info();
void data_run(float first_solution, float finish_solution, float vol_filtrate);

int main(int argc, char *argv[])
{
    const std::string k_help_one = "-h";
    const std::string k_help_two = "--help";
    const std::string k_info = "-i";
    const std::string k_data = "-d";
    std::string similar;

    if (argc >= 2)
    {
        similar = (std::string)argv[1];
    }

    if (argc == 2)
    {
        if (similar == k_help_one || similar == k_help_two)
        {
            help();
        }

        if (similar == k_info)
        {
            info();
        }
    }

    else if (argc == 5 && similar == k_data)
    {
        float data[3];

        for (int i = 0; i < 3; i++)
        {
            data[i] = atof(argv[i + 2]);
        }

        data_run(data[0], data[1], data[2]);
    }

    else
    {
        std::cout << "error... use -h or --help for details" << std::endl;
    }

    return 0;
}

void help()
{
    std::cout << "*** Определение объема компонентов сусло-агара ***" << std::endl
              << std::endl
              << "Использование: " << std::endl
              << "wort -d [начальная концентация] [необходимая концентрация] [объем фильтара]" << std::endl
              << "wort [-h|--help] для вызова справки" << std::endl
              << "wort -i для просмотра дополнительной информации" << std::endl;

    exit(0);
}

void info()
{
    std::cout << "В лабораторных условиях приготовление растворов с заданной" << std::endl
              << "массовой долей растворенного вещества из растворов" << std::endl
              << "с исходной массовой долей осуществоляется в соответствии с \"правилом креста\":" << std::endl
              << "m1 * W1 + m2 * W2 = W3 * (m1 + m2)" << std::endl
              << std::endl
              << "Утилита определяет данные:" << std::endl
              << "- объем воды для разбавления концентрированного раствора" << std::endl
              << "- объем разбавленного раствора" << std::endl
              << "исходя из концентрации начального раствора, объема фильтрата" << std::endl
              << "и концентрации приготавливаемого раствора" << std::endl;

    exit(0);
}

void data_run(float first_solution, float finish_solution, float vol_filtrate)
{
    std::cout << "Концентрация неразбавленного раствора: " << first_solution << "%" << std::endl;
    std::cout << "Концентрация разбавленного раствора: " << finish_solution << "%" << std::endl;
    std::cout << "Объем фильтрата: " << vol_filtrate << " мл" << std::endl;

    solution sol;
    std::cout << "Объем воды для разбавления: " << sol.solutions(sol.water_first)->get_solvation(first_solution, finish_solution, vol_filtrate) << " мл" << std::endl;
    std::cout << "Объем разбавленной среды: " << sol.solutions(sol.worts_second)->get_solvation(sol.solutions(sol.water_first)->get_solvation(first_solution, finish_solution, vol_filtrate), vol_filtrate, 0) << " мл" << std::endl;
}
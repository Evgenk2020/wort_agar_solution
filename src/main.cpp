#include <iostream>
#include "wort.h"

void help();
void info();
void data_run(wort_solution wrt);

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
        wort_solution wort;
        wort.first_wort = atof(argv[2]);
        wort.finish_wort = atof(argv[3]);
        wort.vol_filtrate = atof(argv[4]);
        data_run(wort);
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
}

void data_run(wort_solution wrt /*float first_solution, float finish_solution, float vol_filtrate*/)
{
    std::cout << "Концентрация неразбавленного раствора: " << wrt.first_wort << "%" << std::endl;
    std::cout << "Концентрация разбавленного раствора: " << wrt.finish_wort << "%" << std::endl;
    std::cout << "Объем фильтрата: " << wrt.vol_filtrate << " мл" << std::endl;

    solution sol;
    std::cout << "Объем воды для разбавления: " << sol.solutions(sol.water_for_solvation)->get_solvation(wrt) << " мл" << std::endl;
    std::cout << "Объем разбавленной среды: " << sol.solutions(sol.total_volume)->get_solvation(wrt) << " мл" << std::endl;
}

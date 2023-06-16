#include <iostream>
#include <fstream>
#include <locale>
#include "output.h"

general_info::~general_info() {}

void help_info::see_info()
{
    std::cout << "*** Определение объема компонентов сусло-агара ***" << std::endl
              << std::endl
              << "Для вывода в терминал" << std::endl
              << "wort -d [начальная концентация] [необходимая концентрация] [объем фильтара]" << std::endl
              << "Для вывода в файл" << std::endl
              << "wort -df [начальная концентация] [необходимая концентрация] [объем фильтара]" << std::endl
              << "Для вывода справки" << std::endl
              << "wort [-h|--help]" << std::endl
              << "Для просмотра дополнительной информации" << std::endl
              << "wort -i" << std::endl;
}

void inf_indo::see_info()
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

//--------------------------------------------------

data_info::~data_info() {}

void screen_info::see_info(wort_solution *wrt)
{
    std::cout << "Концентрация неразбавленного раствора: " << wrt->first_wort << " %" << std::endl;
    std::cout << "Концентрация разбавленного раствора: " << wrt->finish_wort << " %" << std::endl;
    std::cout << "Объем фильтрата: " << wrt->vol_filtrate << " мл" << std::endl;

    solution sol;
    std::cout << "Объем воды для разбавления: " << sol.solutions(sol.water_for_solvation)->get_solvation(*wrt) << " мл" << std::endl;
    std::cout << "Объем разбавленной среды: " << sol.solutions(sol.total_volume)->get_solvation(*wrt) << " мл" << std::endl;
}

void file_info::see_info(wort_solution *wrt)
{
    std::ofstream writer("wort-dada.csv", std::ios::app);

    const char coma = ',';
    const char quo = '\"';

    std::locale m_loc("uk_UA.utf8");
    writer.imbue(m_loc);

    writer << "Концентрация разбавленного раствора:" << coma << quo << wrt->finish_wort << quo << coma << "%" << std::endl;
    writer << "Объем фильтрата:" << coma << quo << wrt->vol_filtrate << quo << coma << "мл" << std::endl;

    solution sol;

    writer << "Объем воды для разбавления:" << coma << quo << sol.solutions(sol.water_for_solvation)->get_solvation(*wrt) << quo << coma << "мл" << std::endl;
    writer << "Объем разбавленной среды:" << coma << quo << sol.solutions(sol.total_volume)->get_solvation(*wrt) << quo << coma << "мл" << std::endl;
    writer << "" << std::endl;

    std::cout << "Данные добавлены в файл wort-dada.csv" << std::endl;
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

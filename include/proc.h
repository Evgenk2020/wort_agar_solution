#ifndef PROC_H
#define PROC_H

#include <string>
#include <string_view>
#include <expected>

#include "wort.h"

std::expected<float, std::string> parse_float(std::string_view str);
std::expected<wort_solution, std::string> validate_data(const wort_solution &wort);
wort_solution run_interactive_wizard();
int run_cli(int argc, char *argv[]);

#endif // PROC_H

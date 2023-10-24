//rootConfig.h.in, used for configuration defintions in project scope

#ifndef ROOT_CONFIG_H
#define ROOT_CONFIG_H

#include <type_traits>
constexpr bool is_little_endian = std::endian::native == std::endian::little;

#if defined(_LINUX_TARGET) || defined(_MAC_TARGET)
#define GREEN_TERMINAL std::cout << GREEN;
#define RED_TERMINAL std::cout << RED;
#define YELLOW_TERMINAL std::cout << YELLOW;
#define BLUE_TERMINAL std::cout << BLUE;
#define RESET_TERMINAL std::cout << RESET;
#define DIMB_TEXT std::cout << DIMB;
#define NORM_TEXT std::cout << NORM_TXT;
#include <cstdlib>
#define CLEAR_TERMINAL std::system("clear");
#else
#define GREEN_TERMINAL
#define RED_TERMINAL
#define YELLOW_TERMINAL
#define BLUE_TERMINAL
#define RESET_TERMINAL
#endif

#if defined(_WIN_TARGET)
#include <windows.h>
#define CLEAR_TERMINAL std::system("cls");
#endif

#endif //!ROOT_CONFIG_H

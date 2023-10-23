//rootConfig.h.in, used for configuration defintions in project scope

#ifndef ROOT_CONFIG_H
#define ROOT_CONFIG_H

#include <type_traits>
constexpr bool is_little_endian = std::endian::native == std::endian::little;

#endif //!ROOT_CONFIG_H

#ifndef MACROS_HPP
#define MACROS_HPP

/* io libraries */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <print>

#include <cstdint>
#include <algorithm>
#include <numeric>
#include <utility>
#include <variant>
#include <optional>

/* containers */
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <deque>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define LOG(x) std::cout << x << std::endl;

#endif // MACROS_HPP
#ifndef TREX_MACROS
#define TREX_MACROS

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <print>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

namespace TREX {

/* colors */
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

#define LOG(x) std::cout << x << std::endl;

} // namespace TREX

#endif // TREX_MACROS
#ifndef UTIL_H
#define UTIL_H

#include <limits>
#include <cstdint>

typedef uint64_t ull;

const ull inf = std::numeric_limits<ull>::max();
const double eps = 1E-10;

struct point {
    ull x;
    double y;
};

#endif

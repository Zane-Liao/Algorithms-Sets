#include "mult.h"
#include <utility> // for std::pair
#include <algorithm> // for std::max
#include <cmath> // for std::pow

namespace algorithms {

    std::size_t digits(uint64_t num) {
        std::size_t count = 0;
        while (num > 0) {
            ++count;
            num /= 10;
        }
        return count;
    }

    std::pair<uint64_t, uint64_t> split_at(uint64_t a, std::size_t b) {
        uint64_t power_of_10 = static_cast<uint64_t>(std::pow(10, b));
        uint64_t low = a % power_of_10;
        uint64_t high = a / power_of_10;
        return {high, low};
    }

    uint64_t karatsuba(uint64_t a, uint64_t b) {
        if (a < 10 || b < 10) {
            return a * b;
        }

        std::size_t m = std::max(digits(a), digits(b));
        std::size_t m2 = m / 2;

        auto [high1, low1] = split_at(a, m2);
        auto [high2, low2] = split_at(b, m2);

        uint64_t z0 = karatsuba(low1, low2);
        uint64_t z1 = karatsuba(low1 + high1, low2 + high2);
        uint64_t z2 = karatsuba(high1, high2);

        return (z2 * static_cast<uint64_t>(std::pow(10, m2 * 2))) +
               ((z1 - z2 - z0) * static_cast<uint64_t>(std::pow(10, m2))) +
               z0;
    }

}

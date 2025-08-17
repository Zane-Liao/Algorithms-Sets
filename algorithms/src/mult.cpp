#include "algorithms.hpp"
#include <utility> // for std::pair
#include <algorithm> // for std::max
#include <cmath> // for std::pow
#include <cstddef>   // for std::size_t
#include <cstdint>   // for uint64_t
#include <gmpxx.h>

namespace algorithms {

    static mpz_class pow10(std::size_t n) {
        mpz_class res = 1;
        for (std::size_t i = 0; i < n; ++i) res *= 10;
        return res;
    }

    std::size_t digits(const mpz_class& num) {
        if (num == 0) return 1;
        return mpz_sizeinbase(num.get_mpz_t(), 10);
    }

    std::pair<mpz_class, mpz_class> split_at(const mpz_class& a, std::size_t b) {
        mpz_class p = pow10(b);
        mpz_class low = a % p;
        mpz_class high = a / p;
        return {high, low};
    }

    mpz_class karatsuba(const mpz_class& a, const mpz_class& b) {
        if (a < 10 && a > -10) {
            if (b < 10 && b > -10) return a * b;
        }

        std::size_t m = std::max(digits(a >= 0 ? a : -a), digits(b >= 0 ? b : -b));
        std::size_t m2 = m / 2;

        auto [high1, low1] = split_at(a >= 0 ? a : -a, m2);
        if (a < 0) high1 = -high1;
        auto [high2, low2] = split_at(b >= 0 ? b : -b, m2);
        if (b < 0) high2 = -high2;

        mpz_class z0 = karatsuba(low1, low2);
        mpz_class z1 = karatsuba(low1 + high1, low2 + high2);
        mpz_class z2 = karatsuba(high1, high2);

        mpz_class p10_m2   = pow10(m2);
        mpz_class p10_2m2  = p10_m2 * p10_m2;

        return z2 * p10_2m2 + (z1 - z2 - z0) * p10_m2 + z0;
    }

} // namespace algorithms

#pragma once
#include <cstdint>

namespace algorithms {

    std::size_t digits(uint64_t num);
    std::pair<uint64_t, uint64_t> split_at(uint64_t a, std::size_t b);
    uint64_t karatsuba(uint64_t a, uint64_t b);

}

#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <inttypes.h>

namespace algorithms {

    int64_t knapsack_1d(const std::vector<std::pair<int64_t, int64_t>>& pairs, int64_t capacity) {
        std::vector<int64_t> dp(capacity + 1, 0);

        for (auto [v, w] : pairs) {
            for (int64_t c = capacity; c >= w; --c) {
                dp[c] = std::max(dp[c], dp[c - w] + v);
            }
        }

        return dp[capacity];
    }

} // namespace algorithms
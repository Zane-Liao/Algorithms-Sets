#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <inttypes.h>

namespace algorithms {

    std::vector<int64_t> mwis(const std::vector<int64_t>& numbers) {
        std::vector<int64_t> w;
        // dummy1
        w.push_back(0);
        w.insert(w.end(), numbers.begin(), numbers.end());

        int64_t n = static_cast<int64_t>(w.size()) - 1;
        std::vector<int64_t> dp(n + 1, 0);
        if (n >= 1) dp[1] = w[1];

        for (int64_t i = 2; i <= n; ++i) {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + w[i]);
        }
        return dp;
    }

    std::unordered_set<int64_t> reconstruct_mwis(const std::vector<int64_t>& dp, const std::vector<int64_t>& numbers) {
        std::vector<int64_t> w;
        // dummy2
        w.push_back(0);
        w.insert(w.end(), numbers.begin(), numbers.end());

        int64_t n = static_cast<int64_t>(w.size()) - 1;
        std::unordered_set<int64_t> S;

        int64_t i = n; 
        while (i >= 0) {
            if (dp[i - 1] >= dp[i - 2] + w[i]) {
                --i;
            } else {
                S.insert(i);
                i -= 2;
            }

            if (i == 1) {
                S.insert(1);
            }
        }
        return S;
    }

} // namespace algorithms
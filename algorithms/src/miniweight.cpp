#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <inttypes.h>

namespace algorithms {

    int64_t mini_weight_sum_diff(std::vector<std::pair<double, double>> nums) {
        auto nums_copy = nums;

        std::sort(nums_copy.begin(), nums_copy.end(), [](auto& a, auto& b) {
            auto da = a.first - a.second;
            auto db = b.first - b.second;
            // if two jobs have equal difference (weight - length)
            // you should schedule the job with higher weight first.
            if (da == db) return a.first > b.first;
            return da > db;
        });

        int64_t time = 0, result = 0;
        for (auto &[w, l] : nums_copy) {
            time += l;
            result += w * time;
        }

        return result;
    }

    int64_t mini_weight_sum_scale(std::vector<std::pair<double, double>> nums) {
        auto nums_copy = nums;

        std::sort(nums_copy.begin(), nums_copy.end(), [](auto& a, auto& b) {
            return ( a.first / a.second ) < ( b.first / b.second );
        });

        int64_t time = 0, result = 0;
        for (auto& num : nums_copy) {
            time += num.first;
            // If you pair<int, int>, need add 1LL * time * num.second;
            result += time * num.second;
        }

        return result;
    }

} // namespace algorithms
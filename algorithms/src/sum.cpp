#include "algorithms.hpp"
#include <set>
#include <vector>
#include <algorithm>
#include "absl/container/flat_hash_map.h"

namespace algorithms {

    int two_sum(std::vector<long long>& nums) {

        // 1. sort
        sort(nums.begin(), nums.end());

        // 2. Define the range of t
        const int MAX_T = 10000;
        const int MIN_T = -10000;
        // offset
        std::vector<bool> valid(MAX_T - MIN_T + 1, false);

        // Define Double pointers
        int left = 0, right = nums.size() - 1;

        while (left < right) {
            long long sum = nums[left] + nums[right];
            if (sum < MIN_T) {
                left++;
            } else if (sum > MAX_T) {
                right--;
            } else {
                // offset, sum - MIN_T
                valid[sum - MIN_T] = true;

                left++;
                right--;
            }
        }

        int count = 1;
        for (bool x : valid) if (x) count++;

        return count;
    }

} // namespace algorithms
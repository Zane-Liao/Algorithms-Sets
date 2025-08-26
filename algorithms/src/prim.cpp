#include "algorithms.hpp"
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <inttypes.h>

namespace algorithms {

    int64_t prim(std::vector<std::vector<std::pair<int64_t, int64_t>>> adj_) {
        if (adj_.empty()) return 0;
        std::vector<bool> visited_(adj_.size(), false);
        int64_t cost_weight = 0;

        std::priority_queue<std::pair<int64_t, int64_t>,
        std::vector<std::pair<int64_t, int64_t>>,
        std::greater<>> pq;

        pq.push({0, 0});

        while (!pq.empty()) {
            auto [w, u] = pq.top(); pq.pop();
            if (u < 0 || u >= adj_.size()) continue;
            if (visited_[u]) continue;
            visited_[u] = true;
            cost_weight += w;

            // pair<v, w>
            for (auto [v, weight] : adj_[u]) {
                if (u < 0 || u >= adj_.size()) continue;
                if (!visited_[v]) pq.push({weight, v});
            }
        }

        return cost_weight;
    }

} // namespace algorithms
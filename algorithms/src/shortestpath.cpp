#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <queue>
#include <inttypes.h>

namespace algorithms {

    std::vector<int64_t> bellman_ford(const std::vector<std::vector<std::pair<int, int>>>& g) {
        int n = g.size();
        const int64_t INF = LLONG_MAX / 4;
        std::vector<int64_t> h(n, 0);

        for (int iter = 0; iter < n - 1; iter++) {
            bool updated = false;
            for (int u = 0; u < n; u++) {
                if (h[u] >= INF) continue;
                for (auto [v, w] : g[u]) {
                    if (h[v] > h[u] + w) {
                        h[v] = h[u] + w;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }

        for (int u = 0; u < n; u++) {
            for (auto [v, w] : g[u]) {
                if (h[v] > h[u] + w) {
                    // ERROR
                    throw std::runtime_error("Negative cycle detected");
                }
            }
        }

        return h;
    }

    int64_t johnson_algorithm(const std::vector<std::vector<std::pair<int, int>>>& g) {
        int n = g.size();
        // If RUN ERROR, replace LLONG_MAX / 4;
        const int64_t INF = std::numeric_limits<int64_t>::max();

        // Step 1: Bellman-Ford
        std::vector<int64_t> h = bellman_ford(g);

        // Step 2: Recalibrate edge weights
        std::vector<std::vector<std::pair<int, int>>> new_g(n);
        for (int u = 0; u < n; u++) {
            for (auto [v, w] : g[u]) {
                int64_t new_w = (int64_t)w + h[u] - h[v];
                // ERROR
                if (new_w > INT_MAX) throw std::overflow_error("Edge weight overflow");
                new_g[u].push_back({v, (int)new_w});
            }
        }

        // Step 3: Dijkstra from every node
        int64_t ans = INF;
        for (int s = 0; s < n; s++) {
            auto dist = algorithms::dijkstra(n, s, new_g);
            for (int t = 0; t < n; t++) {
                if (s == t || dist[t] >= INF) continue;
                int64_t real_dist = dist[t] - h[s] + h[t];
                ans = std::min(ans, real_dist);
            }
        }

        // If RUN ERROR, replace LLONG_MAX
        return (ans == INF ? std::numeric_limits<int64_t>::max() : ans);
    }

} // namespace algorithms
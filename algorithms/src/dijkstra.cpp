#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>

namespace algorithms {

    std::vector<int> dijkstra(int n, int start, std::vector<std::vector<std::pair<int, int>>> adj) {
        // We need use std::greater<> => Max-Heap -> Min-Heap
        // std::greater<>, c++ 11, 14 => std::greater<std::pair<int, int>>
        // In c++ 17 => std::greater<>
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> Q;

        const int INF = std::numeric_limits<int>::max();
        std::vector<int> dist(n, INF);
        dist[start] = 0;

        Q.push({0, start});
        while (!Q.empty()) {
            // access priority(max) elements
            auto [d, u] = Q.top();
            // remove elements
            Q.pop();
            if (d > dist[u]) continue;

            for (auto x : adj[u]) {
                int v = x.first;
                int w = x.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    Q.push({dist[v], v});
                }
            }
        }

        return dist;
    }

} // namespace algorithms
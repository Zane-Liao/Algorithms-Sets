#include "algorithms.hpp"
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>
#include <ctime>

namespace algorithms {

    std::pair<int, int> randomEdge(Graph &g) {
        int u;
        do {
            u = rand() % g.V;
        } while (g.adj[u].empty());

        int v_index = rand() % g.adj[u].size();
        int v = g.adj[u][v_index];

        return {u, v};
    }

    void contract(Graph &g, int v1, int v2) {
        for (int neighbor : g.adj[v2]) {
            if (neighbor != v2) {
                g.adj[v1].push_back(neighbor);

                std::replace(
                    g.adj[neighbor].begin(),
                    g.adj[neighbor].end(),
                    v2,
                    v1
                );
            }
        }

        g.adj[v2].clear();
    }

    int karger_min_cut(Graph g) {
        int vertices = g.V;

        while (vertices > 2) {
            auto [u, v] = randomEdge(g);
            contract(g, u, v);
            vertices--;
        }

        int cutEdge = 0;
        for (int i = 0; i < g.V; i++) {
            cutEdge += g.adj[i].size();
        }

        return cutEdge / 2;
    }

} // namespace algorithms
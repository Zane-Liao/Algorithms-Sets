#include "algorithms.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <queue>

namespace algorithms {

    Kosaraju::Kosaraju(int n, std::vector<std::vector<int>>& edges) {
        // private member n
        this->n = n;
        adj.assign(n + 1, {});
        rev.assign(n + 1, {});
        vis.assign(n + 1, 0);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            rev[e[1]].push_back(e[0]);
        }
    }

    void Kosaraju::dfs1(int u) {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (!vis[v]) dfs1(v);
        }
        order.push_back(u);
    }

    void Kosaraju::dfs2(int u, std::vector<int>& comp) {
        vis[u] = 1;
        comp.push_back(u);
        for (int v : rev[u]) {
            if (!vis[v]) dfs2(v, comp);
        }
    }

    std::vector<std::vector<int>> Kosaraju::find_acc() {
        order.clear();
        std::fill(vis.begin(), vis.end(), 0);

        for (int i = 1; i < n; i++) {
            if (!vis[i]) dfs1(i);
        }

        std::fill(vis.begin(), vis.end(), 0);
        std::vector<std::vector<int>> sccs;
        reverse(order.begin(), order.end());
        for (int u : order) {
            if (!vis[u]) {
                std::vector<int> comp;
                dfs2(u, comp);
                sccs.push_back(comp);
            }
        }
        return sccs;
    }

} // namespace algorithms
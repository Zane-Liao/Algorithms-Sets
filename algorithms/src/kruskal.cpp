#include "algorithms.hpp"
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <concepts>
#include <numeric> // std::iora

namespace algorithms {

    WUnionFindDSPath::WUnionFindDSPath (int n)
        : _parent (n), _rank (n, 0) {
        std::iota( _parent.begin(), _parent.end(), 0 );
    }

    int WUnionFindDSPath::__find__( int x ) {
        if ( _parent[x] != x ) {
            _parent[x] = __find__( _parent[x] ); // Path Compression
        }
        return _parent[x];
    }

    void WUnionFindDSPath::__union__( int x, int y ) {
        int root_x = __find__( x );
        int root_y = __find__( y );

        if ( root_x != root_y ) {
            if ( _rank[root_x] > _rank[root_y] ) _parent[root_y] = root_x;
            else if ( _rank[root_x] < _rank[root_y] ) _parent[root_x] = root_y;
            else _parent[root_x] = root_y, _rank[root_y]++;
        }
    }

    int kruskal_clustering(std::vector<std::vector<int>> container) {
        int k = 4;
        int count = 0;
        int sum_cost = 0;
        int max_node = 0;
        std::unordered_set<int> nodes;
        for (auto &e : container) {
            max_node = std::max({max_node, e[0], e[1]});
            nodes.insert(e[0]);
            nodes.insert(e[1]);
        }

        WUnionFindDSPath dsu(max_node + 1);

        // lambda => makeset(v)
        // auto => std::std::vector<int>
        std::sort(container.begin(), container.end(), [](const auto& a, const auto& b) {
            return a[2] < b[2];
        });

        int num_clusters = nodes.size();

        for (auto &c : container) {
            int u = c[0], v = c[1], w = c[2];
            if (dsu.__find__(u) != dsu.__find__(v)) {
                if (num_clusters == k) return w;
                dsu.__union__(u, v);
                num_clusters--;
            }
        }
        return -1;
    }

    int hamming_clustering(std::vector<std::array<int, 24>> container) {
        
    }

} // namespace algorithms
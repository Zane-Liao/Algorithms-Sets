#include "algorithms.hpp"
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <concepts>
#include <numeric> // std::iora
#include <unordered_map>

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

    unsigned int bits_to_int ( const std::array<int, 24>& bits ) {
        unsigned int num = 0;
        for ( int i = 0; i < 24; ++i ) {
            // 2 => 10, 0101 => 5
            if ( bits[i] == 1 ) num |= ( 1 << i );
        }
        return num;
    }

    int hamming_clustering ( std::vector<std::array<int, 24>> container ) {
        int num_nodes = container.size();
        WUnionFindDSPath dsu( num_nodes );
        int num_clusters = num_nodes;

        std::unordered_map<unsigned int, int> mask_to_node_id;
        for ( int i = 0; i < num_nodes; ++i ) {
            unsigned int mask = bits_to_int( container[i] );
            if ( mask_to_node_id.count( mask ) ) {
                int existing_node_id = mask_to_node_id [mask];
                if ( dsu.__find__( i ) != dsu.__find__( existing_node_id ) ) {
                    dsu.__union__( i, existing_node_id );
                    num_clusters--;
                }
            } else {
                mask_to_node_id[mask] = i;
            }
        }

        for ( const auto& [mask, node_id] : mask_to_node_id ) {
            // Find 1
            for ( int i = 0; i < 24; ++i ) {
                // mask = 1010, i=2
                // mask^(1<<2) ==> 1110
                unsigned int neighbor_mask_1 = mask ^ ( 1 << i );
                if ( mask_to_node_id.count( neighbor_mask_1 ) ) {
                    int neighbor_node_id = mask_to_node_id[neighbor_mask_1];
                    if ( dsu.__find__( node_id ) != dsu.__find__( neighbor_node_id ) ) {
                        dsu.__union__( node_id, neighbor_node_id );
                        num_clusters--;
                    }
                }
            }

            // Find 2
            for ( int i = 0; i < 24; ++i ) {
                for ( int j = i + 1; j < 24; ++j ) {
                    // mask = 101010, i=2, j=4
                    // mask^(1<<2)^(1<<4) ==> 111110
                    unsigned int neighbor_mask_2 = mask ^ ( 1 << i ) ^ ( 1 << j );
                    if ( mask_to_node_id.count( neighbor_mask_2 ) ) {
                        int neighbor_node_id = mask_to_node_id[neighbor_mask_2];
                        if ( dsu.__find__( node_id ) != dsu.__find__( neighbor_node_id ) ) {
                            dsu.__union__( node_id, neighbor_node_id );
                            num_clusters--;
                        }
                    }
                }
            }
        }

        return num_clusters;
    }

} // namespace algorithms
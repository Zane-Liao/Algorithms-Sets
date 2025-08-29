#include "algorithms.hpp"
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <queue>

namespace algorithms {

    Kosaraju::Kosaraju ( int n, std::vector<std::vector<int>>& edges ) {
        // private member n
        this->_n = n;
        _adj.assign( n + 1, { } );
        _rev.assign( n + 1, { } );
        _vis.assign( n + 1, false );

        for ( const auto& e : edges ) {
            if ( e[0] <= n && e[1] <= n ) {
                _adj[e[0]].push_back( e[1] );
                _rev[e[1]].push_back( e[0] );
            }
        }
    }

    void Kosaraju::dfs1 ( int u ) {
        _vis[u] = 1;
        for ( int v : _adj[u] ) {
            if ( !_vis[v] ) dfs1( v );
        }
        _order.push_back( u );
    }

    void Kosaraju::dfs2 ( int u, std::vector<int>& comp ) {
        _vis[u] = 1;
        comp.push_back( u );
        for ( int v : _rev[u] ) {
            if ( !_vis[v] ) dfs2( v, comp );
        }
    }

    std::vector<std::vector<int>> Kosaraju::find_scc () {
        _order.clear();
        std::fill( _vis.begin(), _vis.end(), 0 );

        for ( int i = 1; i <= _n; i++ ) {
            if ( !_vis[i] ) dfs1( i );
        }

        std::fill( _vis.begin(), _vis.end(), 0 );
        std::vector<std::vector<int>> sccs;

        std::reverse( _order.begin(), _order.end() );

        for ( int u : _order ) {
            if ( !_vis[u] ) {
                std::vector<int> comp;
                dfs2( u, comp );
                sccs.push_back( comp );
            }
        }
        return sccs;
    }

} // namespace algorithms
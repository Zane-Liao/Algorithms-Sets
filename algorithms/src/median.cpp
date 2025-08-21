#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

namespace algorithms {

    void MedianHeap::insert(long long x) {

        if ( _left_heap.empty() || x <= _left_heap.top() ) {
            _left_heap.push( x );
        } else {
            _right_heap.push( x );
        }

        if ( _right_heap.size() + 1 < _left_heap.size() ) {
            _right_heap.push( _left_heap.top() );
            _left_heap.pop();
        } else if ( _right_heap.size() > _left_heap.size() ) {
            _left_heap.push( _right_heap.top() );
            _right_heap.pop();
        }

    }

    long long MedianHeap::get_median() const {
        return _left_heap.top();
    }

    // #if BST
    void MedianBST::insert(long long x) {

        if ( data.empty() ) {
            data.insert( x );
            mid = data.begin();
            return;
        }

        if ( x < *mid ) {
            data.insert( x );
            if ( data.size() % 2 == 0 ) {
                --mid;
            }
        } else {
            data.insert( x );
            if ( data.size() % 2 == 1 ) {
                ++mid;
            }
        }

    }
    // #endif

    // #if BST
    long long MedianBST::get_median() const {
        return *mid;
    }
    // #endif

} // namespace algorithms
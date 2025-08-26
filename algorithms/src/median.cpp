#include "algorithms.hpp"
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <inttypes.h>

namespace algorithms {

    void MedianHeap::insert ( int64_t x ) {

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

    int64_t MedianHeap::get_median () const {
        return _left_heap.top();
    }

    // #if BST
    void MedianBST::insert ( int64_t x ) {

        if ( _data.empty() ) {
            _data.insert( x );
            mid_ = _data.begin();
            return;
        }

        if ( x < *mid_ ) {
            _data.insert( x );
            if ( _data.size() % 2 == 0 ) {
                --mid_;
            }
        } else {
            _data.insert( x );
            if ( _data.size() % 2 == 1 ) {
                ++mid_;
            }
        }

    }
    // #endif

    // #if BST
    int64_t MedianBST::get_median () const {
        return *mid_;
    }
    // #endif


    template<class Median>
    void benchmark_median(const std::vector<int64_t> nums, const std::string& name) {
        Median median;
        int64_t sum = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (int64_t x : nums) {
            median.insert(x);
            sum += median.get_median();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << name <<  " result = " << (sum % 10000) << ", time = " << duration.count() << " ms\n";
    }

    template void
    benchmark_median<MedianHeap>(const std::vector<int64_t>, const std::string&);

    template void
    benchmark_median<MedianBST>(const std::vector<int64_t>, const std::string&);

} // namespace algorithms
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


    template<class Median>
    void benchmark_median(const std::vector<long long> nums, const std::string& name) {
        Median median;
        long long sum = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (long long x : nums) {
            median.insert(x);
            sum += median.get_median();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << name <<  " result = " << (sum % 10000) << ", time = " << duration.count() << " ms\n";
    }

    template void
    benchmark_median<MedianHeap>(const std::vector<long long>, const std::string&);

    template void
    benchmark_median<MedianBST>(const std::vector<long long>, const std::string&);

} // namespace algorithms
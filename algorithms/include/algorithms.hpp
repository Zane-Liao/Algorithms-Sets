#pragma once

#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ranges> // std::range::range => STL
#include <concepts>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <utility>
#include <cstddef>
#include <gmpxx.h>
#include <time.h>
#include "absl/container/flat_hash_map.h"

namespace algorithms {

    // karatsuba algorithm define
    std::size_t digits(const mpz_class& num);

    std::pair<mpz_class, mpz_class> split_at(const mpz_class& a, std::size_t b);

    mpz_class karatsuba(const mpz_class& a, const mpz_class& b);


    // Read adj file
    std::vector<std::vector<int>> read_adj_list_from_file(const std::string& filename);

    // karger(min-cut) algorithms define
    struct Graph {
        int V;
        std::vector<std::vector<int>> adj;
    };

    // Select Random one edge
    std::pair<int, int> randomEdge(Graph &g);

    // Merge V1, V2
    void contract(Graph &g, int v1, int v2);

    int karger_min_cut(Graph g);


    // scc algorithm define
    std::vector<std::vector<int>> read_edge_mmap(const std::string& filename);

    class Kosaraju {
        public:
            Kosaraju ( int n, std::vector<std::vector<int>>& edges );

            void dfs1 ( int u );
            void dfs2 ( int u, std::vector<int>& comp );

            std::vector<std::vector<int>> find_acc ();

        private:
            std::vector<std::vector<int>> _adj, _rev;
            std::vector<int> _vis, _order;
            int _n;
    };


    // Define Djikstra's algorithm
    std::vector<std::vector<std::pair<int, int>>> read_adj_weight(const std::string& filename);

    // To Only use non-negative weights
    std::vector<int> dijkstra(int n, int start, std::vector<std::vector<std::pair<int, int>>> adj);


    // Define Median maintenance algorithm
    template<std::ranges::range Container>
    Container read_numbers(const std::string& filename);

    class MedianHeap {
        public:
            void insert ( long long x );
            
            long long get_median () const;

        private:
            std::priority_queue<long long> _left_heap;
            std::priority_queue<long long, std::vector<long long>, std::greater<>> _right_heap;
    };

    class MedianBST {
        public:
            void insert ( long long x );

            long long get_median () const;
        private:
            std::multiset<long long> _data;
            std::multiset<long long>::iterator mid_;
    };

    template<class Median>
    void benchmark_median(const std::vector<long long> nums, const std::string& name);


    // Define 2-sum Algorithm
    int two_sum(std::vector<long long>& nums);


    // Read weight and ungraph
    template<std::ranges::range Container>
    Container read_weight_ungraph(const std::string& filename);

    // Define Greedy Algorithms
    // looking for minimizing the weighted sum of completion times
    long long mini_weight_sum_diff(std::vector<std::pair<double, double>> nums);

    // Optimal version algorithm
    long long mini_weight_sum_scale(std::vector<std::pair<double, double>> nums);


    // Define Prim's minimum spanning tree algorithm
    long long prim(std::vector<std::vector<std::pair<long long, long long>>> adj_);


    // Define kruskal clustering algorithm
    template <std::ranges::range Container>
    Container read_file_kclustering(const std::string& filename);

    class WUnionFindDSPath {
        public:
            explicit WUnionFindDSPath (int n);

            int __find__ ( int x );

            void __union__ ( int x, int y );

        private:
            std::vector<int> _parent;
            std::vector<int> _rank;
    };

    int kruskal_clustering(std::vector<std::vector<int>> container);

    int hamming_clustering ( std::vector<std::array<int, 24>> container );


    // Define the all-pairs shortest-path problem
    template <std::ranges::range Container>
    Container read_graph(const std::string& filename);


    // Define tsp Problem
    template <std::ranges::range Container>
    Container read_tsp(const std::string& filename);


    // Define 2SAT problem
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
    read_two_sat(const std::string& filename);

} // namespace algorithms
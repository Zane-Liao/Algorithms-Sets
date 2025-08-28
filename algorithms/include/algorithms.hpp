#pragma once

#include <set>
#include <span>
#include <queue>
#include <cmath>
#include <vector>
#include <memory>
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
#include <inttypes.h>
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

        protected:
            std::vector<std::vector<int>> _adj, _rev;
            std::vector<int> _vis, _order;
            int _n;
    };


    /* Online Algorithm */
    // Define Median maintenance algorithm
    template<std::ranges::range Container>
    Container read_numbers(const std::string& filename);

    class MedianHeap {
        public:
            void insert ( int64_t x );
            
            int64_t get_median () const;

        protected:
            std::priority_queue<int64_t> _left_heap;
            std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> _right_heap;
    };

    class MedianBST {
        public:
            void insert ( int64_t x );

            int64_t get_median () const;
        protected:
            std::multiset<int64_t> _data;
            std::multiset<int64_t>::iterator mid_;
    };

    template<class Median>
    void benchmark_median(const std::vector<int64_t> nums, const std::string& name);


    // Define 2-sum Algorithm
    int two_sum(std::vector<int64_t>& nums);


    // Read weight and ungraph
    template<std::ranges::range Container>
    Container read_weight_ungraph(const std::string& filename);

    /* Greedy Algorithms */
    // Define Djikstra's algorithm
    std::vector<std::vector<std::pair<int, int>>> read_adj_weight(const std::string& filename);

    // To Only use non-negative weights
    std::vector<int> dijkstra(int n, int start, std::vector<std::vector<std::pair<int, int>>> adj);


    // looking for minimizing the weighted sum of completion times
    int64_t mini_weight_sum_diff(std::vector<std::pair<double, double>> nums);

    // Optimal version algorithm
    int64_t mini_weight_sum_scale(std::vector<std::pair<double, double>> nums);


    // Define Prim's minimum spanning tree algorithm
    int64_t prim(std::vector<std::vector<std::pair<int64_t, int64_t>>> adj_);


    // Define kruskal clustering algorithm
    template <std::ranges::range Container>
    Container read_file_kclustering(const std::string& filename);

    class WUnionFindDSPath {
        public:
            explicit WUnionFindDSPath ( int n );

            int __find__ ( int x );

            void __union__ ( int x, int y );

        protected:
            std::vector<int> _parent;
            std::vector<int> _rank;
    };

    int kruskal_clustering(std::vector<std::vector<int>> container);

    int hamming_clustering ( std::vector<std::array<int, 24>> container );


    // Define huffman code algorithm
    class HuffmanNode {
        public:
            int64_t weight;
            std::unique_ptr<HuffmanNode> left;
            std::unique_ptr<HuffmanNode> right;

            HuffmanNode ( int64_t w );

            HuffmanNode (
                int64_t w,
                std::unique_ptr<HuffmanNode> l,
                std::unique_ptr<HuffmanNode> r
            );
    };

    std::unique_ptr<HuffmanNode> huffman_code(std::vector<int64_t>& weights);

    std::pair<int64_t, int64_t> bfs_huffman(const std::unique_ptr<HuffmanNode>& root);


    /* Define Dynamic Programming Algorithms */
    // cs161-Lecture13_notes ==> Algorithm 5: MaxWeightIndependentSet(G)
    std::vector<int64_t> mwis(const std::vector<int64_t>& numbers);

    std::unordered_set<int64_t> reconstruct_mwis(const std::vector<int64_t>& dp, const std::vector<int64_t>& numbers);


    // Solve Knapsack Problem
    // cs161-Lecture13_notes ==> Algorithm 3: UnboundedKnapsack(W, n, w , v )
    // Space: O(W) Time: O(n*W)
    int64_t knapsack_1d(const std::vector<std::pair<int64_t, int64_t>>& pairs, int64_t capacity);


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
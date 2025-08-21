#ifndef ALGORITHMS_SETS
#define ALGORITHMS_SETS

// #pragma once

#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
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
            Kosaraju(int n, std::vector<std::vector<int>>& edges);

            void dfs1(int u);
            void dfs2(int u, std::vector<int>& comp);

            std::vector<std::vector<int>> find_acc();

        private:
            std::vector<std::vector<int>> adj, rev;
            std::vector<int> vis, order;
            int n;
    };

    // Define Djikstra's algorithm
    std::vector<std::vector<std::pair<int, int>>> read_adj_weight(const std::string& filename);

    // To Only use non-negative weights
    std::vector<int> dijkstra(int n, int start, std::vector<std::vector<std::pair<int, int>>> adj);


    // Define Median maintenance algorithm
    template<typename Container>
    Container read_numbers(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }

        Container c;
        std::string outline;

        while (std::getline(infile, outline)) {
            std::istringstream iss(outline);
            long long x;
            while (iss >> x) {
                if constexpr (std::is_same_v<Container, std::multiset<long long>>) {
                    c.insert(x);
                } else if constexpr (std::is_same_v<Container, std::vector<long long>>) {
                    c.push_back(x);
                } else if constexpr (std::is_same_v<Container, absl::flat_hash_map<int, int>>) {
                    c[x]++;
                }
            }
        }

        return c;
    }

    class MedianHeap {
        public:
            void insert(long long x);
            
            long long get_median() const;

        private:
            std::priority_queue<long long> _left_heap;
            std::priority_queue<long long, std::vector<long long>, std::greater<>> _right_heap;
    };

    class MedianBST {
        public:
            void insert(long long x);

            long long get_median() const;
        private:
            std::multiset<long long> data;
            std::multiset<long long>::iterator mid;
    };

    template<typename Median>
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

    // Define 2-sum Algorithm
    int two_sum(std::vector<long long>& nums);

} // namespace algorithms

#endif // ALGORITHMS_SETS
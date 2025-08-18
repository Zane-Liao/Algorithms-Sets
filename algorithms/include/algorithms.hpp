#ifndef ALGORITHMS_SETS
#define ALGORITHMS_SETS

// #pragma once

#include <cstdint>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>
#include <gmpxx.h>
#include <time.h>

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
    void dfs();

    void dfs2();

    std::vector<std::vector<int>> kosaraju_scc();

} // namespace algorithms

#endif // ALGORITHMS_SETS
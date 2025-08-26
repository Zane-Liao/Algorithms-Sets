// Note: Tests failures are normal
// Run all tests with one click. Some algorithms are random,
// so please test them several times. => ./algorithms
// Running a Single Test => 
// ./algorithms --gtest_filter=MultUnitTest.Scc

#include "algorithms.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmpxx.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <inttypes.h>
// #include <bits/stdc++.h>

// This algorithm is random and the test is prone to errors.
// If you don't want it to affect you, please change the value.
// The default is 2 compilation, or check CmakeLists.txt to change
// add_compile_definitions(RUN_TEST_MINCUT=nums)
#define RUN_TEST_MINCUT 1

TEST(MultUnitTest, Karatsuba1) {
    EXPECT_EQ(algorithms::karatsuba(20, 20), 400);
    EXPECT_EQ(algorithms::karatsuba(15, 20), 300);
    EXPECT_EQ(algorithms::karatsuba(400, 500), 200000);
    EXPECT_EQ(algorithms::karatsuba(400, 500), 200000);
}

TEST(MultUnitTest, Karatsuba2) {
    mpz_class a("3141592653589793238462643383279502884197169399375105820974944592");
    mpz_class b("2718281828459045235360287471352662497757247093699959574966967627");
    mpz_class r("8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");

    EXPECT_EQ(algorithms::karatsuba(a, b), r);
}

TEST(MultUnitTest, Dijkstra) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/dijkstraData.txt").string();
    std::vector<std::vector<std::pair<int, int>>> adj;

    adj = algorithms::read_adj_weight(outline);

    // for (auto& neighbors : adj) {
    //     for (auto& edge : neighbors) {
    //         int v = edge.first;
    //         int w = edge.second;
    //         std::cout << "ne: " << v << "wieght: " << w << std::endl;
    //     }
    // }

    auto dist = algorithms::dijkstra(200, 1, adj);
    std::vector<int> select_dist = {
        dist[7], dist[37], dist[59], dist[82], dist[99],
        dist[115], dist[133], dist[165], dist[188], dist[197]
    };

    std::vector<int> answer1 = {2599, 2610, 2947, 2052, 2367, 2399, 2029, 2442, 2505, 3068};
    EXPECT_EQ(select_dist, answer1);
}

TEST(MultUnitTest, 2Sum) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/algo1-programming_prob-2sum.txt").string();

    auto nums = algorithms::read_numbers<std::vector<int64_t>>(outline);

    std::cout << nums.size() << std::endl;

    int count = algorithms::two_sum(nums);

    EXPECT_EQ(count, 427);
}

TEST(MultUnitTest, Median) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/Median.txt").string();

    auto num_heap = algorithms::read_numbers<std::vector<int64_t>>(outline);
    int64_t _sum_heap = 0;

    algorithms::MedianHeap heap;
    for (int64_t num : num_heap) {
        heap.insert( num );
        _sum_heap += heap.get_median();
    }
    // std::cout << "heap result = " << ( _sum_heap % 10000 ) << std::endl;

    EXPECT_EQ((_sum_heap % 10000), 1213);

    auto num_bst = algorithms::read_numbers<std::vector<int64_t>>(outline);
    int64_t _sum_bst = 0;

    algorithms::MedianBST bst;
    for (int64_t num : num_bst) {
        bst.insert( num );
        _sum_bst += bst.get_median();
    }
    // std::cout << "bst result = " << ( _sum_bst % 10000 ) << std::endl;

    EXPECT_EQ((_sum_bst % 10000), 1213);

    algorithms::benchmark_median<algorithms::MedianHeap>(num_heap, "heap");
    algorithms::benchmark_median<algorithms::MedianBST>(num_bst, "bst");
}

#if RUN_TEST_MINCUT == 2
TEST(MultUnitTest, Karger) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/kargerMinCut.txt").string();
    std::vector<std::vector<int>> adj;

    adj = algorithms::read_adj_list_from_file(outline);

    // seed
    srand(time(NULL));

    algorithms::Graph g;

    g.V = adj.size();
    g.adj = adj;
    int min_cut = karger_min_cut(g);
    std::cout << min_cut << std::endl;

    // Note: Tests failures are normal
    // Please test a few more times => ./algorithms
    EXPECT_EQ(min_cut, 17);
}
#endif

TEST(MultUnitTest, Scc) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/scc.txt").string();
    std::vector<std::vector<int>> adj;
    
    adj = algorithms::read_edge_mmap(outline);

    algorithms::Kosaraju solver((int)adj.size(), adj);
    auto ans = solver.find_acc();
    std::vector<int> result;
    for (auto& comp : ans) {
        for (int v : comp) {
            result.push_back(v);
        }
    }

    std::vector<int> answer2 = {434821, 968, 459, 313, 211};
    EXPECT_EQ(result, answer2);
}

// ---------------------------------------------------------------------------------------------------------------------------------------

TEST(MultUnitTest, MiniWeightSum) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/jobs.txt").string();

    auto num_weight = algorithms::read_weight_ungraph<std::vector<std::pair<double, double>>>(outline);

    int64_t sum_diff = algorithms::mini_weight_sum_diff(num_weight);
    EXPECT_EQ(sum_diff, 69119377652);

    int64_t sum_scale = algorithms::mini_weight_sum_scale(num_weight);
    EXPECT_EQ(sum_scale, 67311454237);
}

TEST(MultUnitTest, Prim) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/edges.txt").string();

    auto num_ungraph = algorithms::read_weight_ungraph<std::vector<std::vector<std::pair<int64_t, int64_t>>>>(outline);

    int64_t sum_cost = algorithms::prim(num_ungraph);

    std::cout << "sum cost: " << sum_cost << std::endl;

    EXPECT_EQ(sum_cost, -3612829);
}

TEST(MultUnitTest, Kruskal) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/clustering1.txt").string();

    std::string big_outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/clustering_big.txt").string();

    auto num_k = algorithms::read_file_kclustering<std::vector<std::vector<int>>>(outline);
    std::cout << "num_k: " << num_k.size() << std::endl;
    auto sum_k = algorithms::kruskal_clustering(num_k);
    EXPECT_EQ(sum_k, 106);

    auto big_num_k = algorithms::read_file_kclustering<std::vector<std::array<int, 24>>>(big_outline);
    std::cout << "big_num_k: " << big_num_k.size() << std::endl;
    auto big_sum_k = algorithms::hamming_clustering(big_num_k);
    EXPECT_EQ(big_sum_k, 6118);
}

TEST(MultUnitTest, Huffman) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/huffman.txt").string();

    auto huffman_weight = algorithms::read_numbers<std::vector<int64_t>>(outline);
    ASSERT_FALSE(huffman_weight.empty()) << "huffman.txt is empty!";
    std::cout << "huffman weight: " << huffman_weight.size() << std::endl;

    auto code = algorithms::huffman_code(huffman_weight);

    std::cout << "weights count: " << huffman_weight.size() << std::endl;
    for (int i = 0; i < std::min((size_t)10, huffman_weight.size()); i++) {
        std::cout << huffman_weight[i] << " ";
    }
    std::cout << std::endl;

    auto [min_len, max_len] = algorithms::bfs_huffman(code);

    EXPECT_EQ(min_len, 9);
    EXPECT_EQ(max_len, 19);
}

TEST(MultUnitTest, Mwis) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/mwis.txt").string();

    auto mwis = algorithms::read_numbers<std::vector<int64_t>>(outline);

    std::cout << "mwis: " << mwis.size() << std::endl;
}

TEST(MultUnitTest, Knapsack) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/knapsack1.txt").string();
    auto knapsack = algorithms::read_weight_ungraph<std::vector<std::pair<double, double>>>(outline);
    std::cout << "knapsack: " << knapsack.size() << std::endl;

    std::string big_outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/knapsack_big.txt").string();
    auto big_knapsack = algorithms::read_weight_ungraph<std::vector<std::pair<double, double>>>(big_outline);
    std::cout << "big knapsack: " << big_knapsack.size() << std::endl;
}

TEST(MultUnitTest, Graph) {
    std::string outline_g1 = (std::filesystem::path(SOURCE_DIR) / "problemFile/g1.txt").string();
    auto g1 = algorithms::read_graph<std::vector<std::vector<std::pair<int, int>>>>(outline_g1);
    std::cout << "g1: " << g1.size() << std::endl;

    std::string outline_g2 = (std::filesystem::path(SOURCE_DIR) / "problemFile/g2.txt").string();
    auto g2 = algorithms::read_graph<std::vector<std::vector<std::pair<int, int>>>>(outline_g2);
    std::cout << "g2: " << g2.size() << std::endl;

    std::string outline_g3 = (std::filesystem::path(SOURCE_DIR) / "problemFile/g3.txt").string();
    auto g3 = algorithms::read_graph<std::vector<std::vector<std::pair<int, int>>>>(outline_g3);
    std::cout << "g3: " << g3.size() << std::endl;

    std::string outline_large = (std::filesystem::path(SOURCE_DIR) / "problemFile/large.txt").string();
    auto large = algorithms::read_graph<std::vector<std::vector<std::pair<int, int>>>>(outline_large);
    std::cout << "large: " << large.size() << std::endl;
}

TEST(MultUnitTest, Tsp1) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/tsp.txt").string();
    auto tsp_num = algorithms::read_tsp<std::vector<std::pair<double, double>>>(outline);
    std::cout << "Tsp1: " << tsp_num.size() << std::endl;
}

TEST(MultUnitTest, Tsp2) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/nn.txt").string();
    auto tsp_num = algorithms::read_tsp<std::vector<std::tuple<int, double, double>>>(outline);
    std::cout << "Tsp2: " << tsp_num.size() << std::endl;
}

TEST(MultUnitTest, Twosat) {
    std::string outline1 = (std::filesystem::path(SOURCE_DIR) / "problemFile/2sat1.txt").string();
    std::string outline2 = (std::filesystem::path(SOURCE_DIR) / "problemFile/2sat2.txt").string();
    std::string outline3 = (std::filesystem::path(SOURCE_DIR) / "problemFile/2sat3.txt").string();
    std::string outline4 = (std::filesystem::path(SOURCE_DIR) / "problemFile/2sat4.txt").string();
    std::string outline5 = (std::filesystem::path(SOURCE_DIR) / "problemFile/2sat5.txt").string();
    std::string outline6 = (std::filesystem::path(SOURCE_DIR) / "problemFile/2sat6.txt").string();
    auto two_sat_1 = algorithms::read_two_sat(outline1);
    auto two_sat_2 = algorithms::read_two_sat(outline2);
    auto two_sat_3 = algorithms::read_two_sat(outline3);
    auto two_sat_4 = algorithms::read_two_sat(outline4);
    auto two_sat_5 = algorithms::read_two_sat(outline5);
    auto two_sat_6 = algorithms::read_two_sat(outline6);
}
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
#include <vector>
#include <filesystem>
#include <chrono>

// This algorithm is random and the test is prone to errors.
// If you don't want it to affect you, please change the value.
// The default is 2 compilation, or check CmakeLists.txt to change
// add_compile_definitions(RUN_TEST_MINCUT=nums)
#define RUN_TEST_MINCUT 1

TEST(MultUnitTest1, Karatsuba1) {
    EXPECT_EQ(algorithms::karatsuba(20, 20), 400);
    EXPECT_EQ(algorithms::karatsuba(15, 20), 300);
    EXPECT_EQ(algorithms::karatsuba(400, 500), 200000);
    EXPECT_EQ(algorithms::karatsuba(400, 500), 200000);
}

TEST(MultUnitTest1, Karatsuba2) {
    mpz_class a("3141592653589793238462643383279502884197169399375105820974944592");
    mpz_class b("2718281828459045235360287471352662497757247093699959574966967627");
    mpz_class r("8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");

    EXPECT_EQ(algorithms::karatsuba(a, b), r);
}

TEST(MultUnitTest1, Dijkstra) {
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

TEST(MultUnitTest1, 2Sum) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/algo1-programming_prob-2sum.txt").string();

    auto nums = algorithms::read_numbers<std::vector<long long>>(outline);

    std::cout << nums.size() << std::endl;

    int count = algorithms::two_sum(nums);

    EXPECT_EQ(count, 427);
}

TEST(MultUnitTest1, Median) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/Median.txt").string();

    auto num_heap = algorithms::read_numbers<std::vector<long long>>(outline);
    long long _sum_heap = 0;

    algorithms::MedianHeap heap;
    for (long long num : num_heap) {
        heap.insert( num );
        _sum_heap += heap.get_median();
    }
    // std::cout << "heap result = " << ( _sum_heap % 10000 ) << std::endl;

    EXPECT_EQ((_sum_heap % 10000), 1213);

    auto num_bst = algorithms::read_numbers<std::vector<long long>>(outline);
    long long _sum_bst = 0;

    algorithms::MedianBST bst;
    for (long long num : num_bst) {
        bst.insert( num );
        _sum_bst += bst.get_median();
    }
    // std::cout << "bst result = " << ( _sum_bst % 10000 ) << std::endl;

    EXPECT_EQ((_sum_bst % 10000), 1213);

    algorithms::benchmark_median<algorithms::MedianHeap>(num_heap, "heap");
    algorithms::benchmark_median<algorithms::MedianBST>(num_bst, "bst");
}

#if RUN_TEST_MINCUT == 2
TEST(MultUnitTest1, Karger) {
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

TEST(MultUnitTest1, Scc) {
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

TEST(MultUnitTest1, MiniWeightSum) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/jobs.txt").string();

    auto num_weight = algorithms::read_weight_ungraph<std::vector<std::pair<double, double>>>(outline);

    long long sum_diff = algorithms::mini_weight_sum_diff(num_weight);
    EXPECT_EQ(sum_diff, 69119377652);

    long long sum_scale = algorithms::mini_weight_sum_scale(num_weight);
    EXPECT_EQ(sum_scale, 67311454237);
}

TEST(MultUnitTest2, Prim) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/edges.txt").string();

    auto num_ungraph = algorithms::read_weight_ungraph<std::vector<std::vector<std::pair<long long, long long>>>>(outline);

    long long sum_cost = algorithms::prim(num_ungraph);

    EXPECT_EQ(sum_cost, -3612829);
}
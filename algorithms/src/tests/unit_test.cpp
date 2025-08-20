#include "algorithms.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmpxx.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>

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

TEST(MultUnitTest, Median) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/Median.txt").string();

    auto num_heap = algorithms::read_numbers<std::vector<int>>(outline);

    auto num_tree = algorithms::read_numbers<std::multiset<int>>(outline);
    
}

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
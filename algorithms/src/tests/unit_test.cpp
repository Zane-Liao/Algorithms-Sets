#include "algorithms.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "gmpxx.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

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

TEST(MultUnitTest, Karger) {
    std::string outline = (std::filesystem::path(SOURCE_DIR) / "problemFile/kargerMinCut.txt").string();
    std::vector<std::vector<int>> adj;

    try {
        adj = algorithms::read_adj_list_from_file(outline);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return;
    }

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
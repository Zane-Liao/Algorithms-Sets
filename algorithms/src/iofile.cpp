#include "algorithms.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace algorithms {

    std::vector<std::vector<int>> read_adj_list_from_file(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("Error!!! Can not open file" + filename);
        }
    
        std::vector<std::vector<int>> adj;
        std::string outline;
    
        while (std::getline(infile, outline)) {
            std::istringstream iss(outline);
            int vertex;
            iss >> vertex;
            std::vector<int> neighbors;
            int neighbor;
            while (iss >> neighbor) {
                neighbors.push_back(neighbor);
            }
            adj.push_back(neighbors);
        }
    
        return adj;
    }

} // namespace algorithms
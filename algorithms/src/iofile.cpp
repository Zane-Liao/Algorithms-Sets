#include "algorithms.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace algorithms {

    std::vector<std::vector<int>> read_adj_list_from_file(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
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

    std::vector<std::vector<int>> read_edge_mmap(const std::string& filename) {
        // some c style
        int fd = open(filename.c_str(), O_RDONLY);
        if (fd == -1) {
            throw std::runtime_error("ERROR!!! can not open file: " + filename);
        }
        struct stat sb;
        fstat(fd, &sb);
        size_t sz = sb.st_size;
        // mmap syscall
        char* data = static_cast<char*>mmap(nullptr, sz, PROT_READ, MAP_PRIVATE, fd, 0);
        if (data == MAP_FAILED) {
            close(fd);
            throw std::runtime_error("ERROR!!! Falied to mmap file");
        }
        close(fd);

        std::vector<std::vector<int>> adj;
        const char* p = data;
        const char* end = data + sz;
        int u, v;

        // lambda
        auto readInt = [&](int &x) -> bool {
            // Is p a number? true => ++p false => 
            while (p < end && !isdigit(*p)) ++p;
            if (p >= end) return false;
            int val = 0;
            while (p < end && isdigit(*p)) {
                // *'3' - '0' = 51 - 48 = 3
                // val = 0 * 10 + (1) = 1 => val = 1 * 10 + (2) = 12
                val = val * 10 + (*p - '0');
                ++p;
            }
            x = val;
            return true;
        }

        while (readInt(u) && readInt(v)) {
            --u, --v;
            int n = max(u+1, v+1);
            if ((int)adj.size() < n) adj.resize(n);
            adj[u].push_back(v);
        }

        if (munmap(data, sz) == -1) {
            throw std::runtime_error(
                "ERROR!!! munmap falied: " + std::string(strerror(errno))
            );
        }
        std::cerr << "[mmap-simple] nodes = " << adj.size() <<std::endl;
        
        return adj;
    }

} // namespace algorithms
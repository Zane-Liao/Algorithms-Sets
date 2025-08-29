#include "algorithms.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

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
        int fd = open(filename.c_str(), O_RDONLY);
        if (fd == -1) {
            throw std::runtime_error("ERROR!!! can not open file: " + filename);
        }
        struct stat sb;
        fstat(fd, &sb);
        size_t sz = sb.st_size;
        char* data = static_cast<char*>(mmap(nullptr, sz, PROT_READ, MAP_PRIVATE, fd, 0));
        if (data == MAP_FAILED) {
            close(fd);
            throw std::runtime_error("ERROR!!! Falied to mmap file");
        }
        close(fd);
    
        std::vector<std::vector<int>> edge_list;
        const char* p = data;
        const char* end = data + sz;
        int u, v;
        int max_node = 0;
    
        auto readInt = [&](int &x) -> bool {
            while (p < end && !isdigit(*p)) ++p;
            if (p >= end) return false;
            int val = 0;
            while (p < end && isdigit(*p)) {
                val = val * 10 + (*p - '0');
                ++p;
            }
            x = val;
            return true;
        };
    
        while (readInt(u) && readInt(v)) {
            edge_list.push_back({u, v});
        }
    
        if (munmap(data, sz) == -1) {
            throw std::runtime_error(
                "ERROR!!! munmap falied: " + std::string(strerror(errno))
            );
        }
        
        // std::cerr << "[mmap-simple] nodes = " << adj.size() <<std::endl;
        
        return edge_list;
    }

    std::vector<std::vector<std::pair<int, int>>> read_adj_weight(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }
    
        std::vector<std::vector<std::pair<int, int>>> adj(201);
    
        std::string outline;
        while (std::getline(infile, outline)) {
            std::istringstream iss(outline);
            int vertex;
            iss >> vertex;
            int neighbor, weight;
    
            std::string token;
            while (iss >> token) {
                // find substr, size_t ',' index
                auto pos = token.find(',');
                // if '.' does not exist => continue
                if (pos == std::string::npos) continue;
                // std::string translat int
                // substr() => token = 80,982, find() = 2
                // neighbor= 80, weight = 982
                neighbor = std::stoi(token.substr(0, pos));
                weight = std::stoi(token.substr(pos + 1));
                // Construct elements directly within collections(fast)
                adj[vertex].emplace_back(neighbor, weight);
            }
        }
        return adj;
    }

    template<std::ranges::range Container>
    Container read_numbers(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }

        Container c;
        std::string outline;

        while (std::getline(infile, outline)) {
            std::istringstream iss(outline);
            int64_t x;
            while (iss >> x) {
                if constexpr (std::is_same_v<Container, std::multiset<int64_t>>) {
                    c.insert(x);
                } else if constexpr (std::is_same_v<Container, std::vector<int64_t>>) {
                    c.push_back(x);
                } else if constexpr (std::is_same_v<Container, absl::flat_hash_map<int, int>>) {
                    c[x]++;
                }
            }
        }

        return c;
    }

    template<std::ranges::range Container>
    Container read_weight_ungraph(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }

        Container c;

        std::string outline;
        int max_node = 0;

        std::vector<std::tuple<int64_t, int64_t, int64_t>> edges;
        while (std::getline(infile, outline)) {
            std::istringstream iss(outline);

            if constexpr (std::is_same_v<Container, std::vector<std::pair<double, double>>>) {
                int n, w;
                while (iss >> n >> w) {
                    c.push_back({n, w});
                }
            } else if constexpr (std::is_same_v<Container, std::vector<std::vector<std::pair<int64_t, int64_t>>>>) {
                int u, v, w;
                while (iss >> u >> v >> w) {
                    u--; v--;
                    edges.push_back({u, v, w});
                    max_node = std::max({max_node, u, v});
                }
            } else if constexpr (std::is_same_v<Container, std::vector<std::pair<int64_t, int64_t>>>) {
                int n, w;
                while (iss >> n >> w) {
                    c.push_back({n, w});
                }
            }

            if constexpr (std::is_same_v<Container, std::vector<std::vector<std::pair<int64_t, int64_t>>>>) {
                c.resize(max_node + 1);
                for (auto [u, v, w] : edges) {
                    // pair<v, w>
                    c[u].push_back({v, w});
                    c[v].push_back({u, w});
                }
            }
        }

        return c;
    }

    template <std::ranges::range Container>
    Container read_file_kclustering(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }

        Container c;
        std::string outline;

        while (std::getline(infile, outline)) {
            std::istringstream iss(outline);

            if constexpr (std::is_same_v<Container, std::vector<std::vector<int>>>) {
                int u, v, w;
                if (!(iss >> u >> v >> w)) continue;

                c.push_back({u, v, w});

            } else if constexpr (std::is_same_v<Container, std::vector<std::array<int, 24>>>) {
                std::array<int, 24> row{};
                for (int i = 0; i < 24; ++i) {
                    iss >> row[i];
                }
                c.push_back(row);
            }
        }

        return c;
    }

    template <std::ranges::range Container>
    Container read_graph(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }
    
        int n, m;
        infile >> n >> m;
    
        if constexpr (std::is_same_v<Container, std::vector<std::vector<std::pair<int, int>>>>) {
            Container adj(n + 1);  // 1-based index
            int u, v, w;
            for (int i = 0; i < m; i++) {
                infile >> u >> v >> w;
                adj[u].push_back({v, w});
            }
            return adj;

        } else if constexpr (std::is_same_v<Container, std::vector<std::tuple<int, int, int>>>) {
            Container edges;
            edges.reserve(m);
            int u, v, w;
            for (int i = 0; i < m; i++) {
                infile >> u >> v >> w;
                edges.emplace_back(u, v, w);
            }
            return edges;
    
        }
    }

    template <std::ranges::range Container>
    Container read_tsp(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) throw std::runtime_error("ERROR!!! Can not open file: " + filename);
    
        int n;
        infile >> n;
    
        Container c;
        c.reserve(n);
    
        for (int i = 0; i < n; i++) {
            if constexpr (std::is_same_v<Container, std::vector<std::pair<double, double>>>) {
                std::string line;
                std::getline(infile, line);
                if (line.empty()) { i--; continue; }
                std::istringstream iss(line);
    
                double x, y;
                if (iss.peek() >= '0' && iss.peek() <= '9') {
                    int id;
                    iss >> id >> x >> y;
                    c.emplace_back(x, y);
                } else {
                    iss >> x >> y;
                    c.emplace_back(x, y);
                }
    
            } else if constexpr (std::is_same_v<Container, std::vector<std::tuple<int, double, double>>>) {
                int id; double x, y;
                infile >> id >> x >> y;
                c.emplace_back(id, x, y);
            }
        }
    
        return c;
    }

    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> read_two_sat(const std::string& filename) {
        std::ifstream infile(filename);
        if (!infile) {
            throw std::runtime_error("ERROR!!! Can not open file: " + filename);
        }

        int n; 
        infile >> n;

        std::vector<std::vector<int>> g(2 * n + 1);
        std::vector<std::vector<int>> g_rev(2 * n + 1);

        auto var_index = [n](int x) {
            if (x > 0) return x;
            else return n + (-x);
        };

        auto neg = [n](int x) {
            if (x > n) return x - n;
            else return x + n;
        };

        int a, b;
        while (infile >> a >> b) {
            int u = var_index(a);
            int v = var_index(b);

            int not_u = neg(u);
            int not_v = neg(v);

            g[not_u].push_back(v);
            g[not_v].push_back(u);

            g_rev[v].push_back(not_u);
            g_rev[u].push_back(not_v);
        }

        return {g, g_rev};
    }


    template std::multiset<int64_t>
    read_numbers<std::multiset<int64_t>>(const std::string & );

    template std::vector<int64_t>
    read_numbers<std::vector<int64_t>>(const std::string & );

    template absl::flat_hash_map<int, int>
    read_numbers<absl::flat_hash_map<int, int>>(const std::string & );

    template std::vector<std::pair<double, double>>
    read_weight_ungraph<std::vector<std::pair<double, double>>>(const std::string & );

    template std::vector<std::pair<int64_t, int64_t>>
    read_weight_ungraph<std::vector<std::pair<int64_t, int64_t>>>(const std::string & );

    template std::vector<std::vector<std::pair<int64_t, int64_t>>>
    read_weight_ungraph<std::vector<std::vector<std::pair<int64_t, int64_t>>>>(const std::string & );

    template std::vector<std::vector<int>>
    read_file_kclustering<std::vector<std::vector<int>>>(const std::string & );

    template std::vector<std::array<int, 24>>
    read_file_kclustering<std::vector<std::array<int, 24>>>(const std::string & );

    template std::vector<std::vector<std::pair<int, int>>>
    read_graph<std::vector<std::vector<std::pair<int, int>>>>(const std::string & );

    template std::vector<std::tuple<int, int, int>>
    read_graph<std::vector<std::tuple<int, int, int>>>(const std::string & );

    template std::vector<std::pair<double, double>>
    read_tsp<std::vector<std::pair<double, double>>>(const std::string & );

    template std::vector<std::tuple<int, double, double>>
    read_tsp<std::vector<std::tuple<int, double, double>>>(const std::string & );

} // namespace algorithms
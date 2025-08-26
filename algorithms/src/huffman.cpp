#include "algorithms.hpp"
#include <queue>
#include <vector>
#include <memory>
#include <algorithm>
#include <ranges>

namespace algorithms {

    HuffmanNode::HuffmanNode ( int64_t w )
        : weight (w), left (nullptr), right (nullptr) {}

    HuffmanNode::HuffmanNode ( int64_t w, std::unique_ptr<HuffmanNode> l, std::unique_ptr<HuffmanNode> r ) 
        : weight (w), left (std::move(l)), right (std::move(r)) {}

    std::unique_ptr<HuffmanNode> huffman_code(std::vector<int64_t>& weights) {
        std::sort(weights.begin(), weights.end());
        
        std::vector<std::unique_ptr<HuffmanNode>> nodes;
        for (auto w : weights) {
                nodes.push_back(std::make_unique<HuffmanNode>(w));
        }

        std::queue<std::unique_ptr<HuffmanNode>> merges;
        size_t i = 0;

        auto get_min = [&]() -> std::unique_ptr<HuffmanNode> {
            if (i < nodes.size() && (merges.empty() || nodes[i]->weight <= merges.front()->weight)) {
                return std::move(nodes[i++]);
            } else {
                auto node = std::move(merges.front());
                merges.pop();
                return node;
            }
        };

        while ((nodes.size() - i) + merges.size() > 1) {
            auto left  = get_min();
            auto right = get_min();
            auto parent = std::make_unique<HuffmanNode>(
                left->weight + right->weight,
                std::move(left),
                std::move(right)
            );
            merges.push(std::move(parent));
        }

        if (!merges.empty()) {
            return std::move(merges.front());
        } else if (i < nodes.size()) {
            return std::move(nodes[i]);
        } else {
            return nullptr;
        }
    }

    std::pair<int64_t, int64_t> bfs_huffman(const std::unique_ptr<HuffmanNode>& root) {
        if (!root) return {0, 0};
        int min_depth = INT_MAX;
        int max_depth = 0;

        std::queue<std::pair<HuffmanNode*, int>> Q;
        Q.emplace(root.get(), 0);

        while (!Q.empty()) {
            auto [node, depth] = Q.front();
            Q.pop();

            if (!node->left && !node->right) {
                min_depth = std::min(min_depth, depth);
                max_depth = std::max(max_depth, depth);
            }

            if (node->left)  Q.emplace(node->left.get(), depth + 1);
            if (node->right) Q.emplace(node->right.get(), depth + 1);
        }

        return {min_depth, max_depth};
    }

} // namespace algorithms
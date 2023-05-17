/*

Реализуйте бинарное дерево поиска для целых чисел. Программа получает на вход последовательность различных натуральных
чисел и строит из них дерево. Элементы в деревья добавляются в соответствии с результатом поиска их места. Балансировка
дерева не производится.

Дерево называется сбалансированным, если для любой его вершины высота левого и правого поддерева для этой вершины
различаются не более чем на 1. Определите, является ли дерево сбалансированным.

*/

#include <iostream>
#include <vector>
#include <boost/intrusive/bstree.hpp>
#include <boost/intrusive/sg_set.hpp>
#include <boost/algorithm/string.hpp>

class TreeNode : public boost::intrusive::bs_set_base_hook<> {
    int32_t x_;

public:
    TreeNode(int32_t i) : x_(i) {
    }

    friend bool operator<(const TreeNode &a, const TreeNode &b) {
        return a.x_ < b.x_;
    }

    friend bool operator>(const TreeNode &a, const TreeNode &b) {
        return a.x_ > b.x_;
    }

    friend bool operator==(const TreeNode &a, const TreeNode &b) {
        return a.x_ == b.x_;
    }
};

typedef boost::intrusive::bstree<TreeNode, boost::intrusive::compare<std::greater<TreeNode>>> BSTree;

int32_t Depth(boost::intrusive::tree_node<boost::intrusive::hook_defaults::void_pointer> *node) {
    if (node == nullptr) {
        return 0;
    }
    return std::max(Depth(node->left_), Depth(node->right_)) + 1;
}

int32_t TaskI(const std::vector<std::string> &temp) {

    std::vector<TreeNode> values;
    for (auto &string : temp) {
        values.emplace_back(std::stoi(string));
    }
    BSTree bstree;
    for (auto &node : values) {
        bstree.insert_unique(node);
    }

    for (auto &node : bstree) {
        if (std::abs(Depth(node.right_) - Depth(node.left_)) > 1) {
            return false;
        }
    }

    return true;
}

int main() {
    std::string line;
    getline(std::cin, line);
    std::vector<std::string> temp;
    boost::split(temp, line, boost::is_any_of(" "));
    auto balanced = TaskI(temp);
    if (balanced) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
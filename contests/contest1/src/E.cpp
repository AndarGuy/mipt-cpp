/*

Задан ориентированый граф в виде списка рёбер. Каждому ребру приписан вес - натуральное число. Необходимо определить
количество исходящих рёбер из каждой вершины и их суммарный вес. Рёбра перечислены в случайном порядке.

*/

#include <iostream>
#include <vector>
#include "boost/graph/adjacency_list.hpp"

#define N constant_n

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
                              boost::property<boost::edge_weight_t, uint32_t>>
    graph_t;

std::vector<std::tuple<int32_t, int32_t, int32_t>> TaskE(const graph_t &graph) {
    std::vector<std::tuple<int32_t, int32_t, int32_t>> answer;
    for (auto vertice : boost::make_iterator_range(vertices(graph))) {
        int32_t to = 0;
        int32_t weight = 0;
        for (auto edge : boost::make_iterator_range(out_edges(vertice, graph))) {
            weight += get(boost::edge_weight_t(), graph, edge);
            to++;
        }
        answer.emplace_back(vertice, to, weight);
    }
    return answer;
}

int main() {
    uint32_t N = 0;
    std::cin >> N;

    graph_t graph;
    for (size_t i = 0; i < N; i++) {
        int32_t from = 0;
        int32_t to = 0;
        int32_t weight = 0;
        std::cin >> from >> to >> weight;
        boost::add_edge(from, to, weight, graph);
    }

    for (auto [vertice, to, weight] : TaskE(graph)) {
        std::cout << vertice << " " << to << " " << weight << '\n';
    }

    return 0;
}
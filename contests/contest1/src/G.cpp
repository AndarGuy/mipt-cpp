/*

Дан взвешенный связный граф. Вершины пронумерованы от 0. Трeбуется с помощью алгоритма Дейкстры восстановить кратчайший
путь от вершины s до f.

*/

#include <iostream>
#include <vector>
#include <map>
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/connected_components.hpp>
#include <boost/graph/detail/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#define N constant_n
#define M constant_m
#define S constant_s
#define F constant_F

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
                              boost::property<boost::edge_weight_t, uint32_t>>
    graph_t;

std::vector<int32_t> TaskG([[maybe_unused]] const int32_t N, [[maybe_unused]] const int32_t M,
                           [[maybe_unused]] const int32_t S, [[maybe_unused]] const int32_t F,
                           const std::vector<std::tuple<int32_t, int32_t, int32_t>> &bridges) {

    graph_t graph(N);
    for (auto [from, to, weight] : bridges) {
        boost::add_edge(from, to, weight, graph);
    }

    std::vector<int32_t> predecessors(N);
    std::vector<int32_t> distances(N);
    boost::dijkstra_shortest_paths(graph, vertex(S, graph),
                                   boost::predecessor_map(predecessors.data()).distance_map(distances.data()));
    std::vector<int32_t> path;
    for (int32_t current = F; current != S; current = predecessors[current]) {
        path.push_back(current);
    }
    path.push_back(S);

    return std::vector<int32_t>(path.rbegin(), path.rend());
}

int main() {
    int32_t N = 0;
    std::cin >> N;
    int32_t M = 0;
    std::cin >> M;
    int32_t S = 0;
    std::cin >> S;
    int32_t F = 0;
    std::cin >> F;

    std::vector<std::tuple<int32_t, int32_t, int32_t>> bridges(M);
    for (auto &[from, to, weight] : bridges) {
        std::cin >> from >> to >> weight;
    }

    auto answer = TaskG(N, M, S, F, bridges);
    for (auto vertex : answer) {
        std::cout << vertex << " ";
    }

    return 0;
}
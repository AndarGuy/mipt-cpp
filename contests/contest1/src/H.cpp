/*

Дан невзвешенный неориентированный связный граф. Вершины пронумерованы от 0. Трeбуется с помощью обхода в ширину найти
расстояния от 0-й до всех остальных вершин.

*/

#include <iostream>
#include <vector>
#include <map>
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/connected_components.hpp>
#include <boost/graph/detail/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/breadth_first_search.hpp>

#define N constant_n
#define M constant_m

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::no_property>
    graph_t;

std::vector<int32_t> TaskH([[maybe_unused]] const int32_t N, [[maybe_unused]] const int32_t M,
                           const std::vector<std::tuple<int32_t, int32_t>> &bridges) {

    graph_t graph(N);
    for (auto [from, to] : bridges) {
        boost::add_edge(from, to, graph);
    }

    std::vector<int32_t> distances(N);
    boost::breadth_first_search(
        graph, 0,
        boost::visitor(boost::make_bfs_visitor(boost::record_distances(distances.data(), boost::on_tree_edge()))));

    return distances;
}

int main() {
    int32_t N = 0;
    std::cin >> N;
    int32_t M = 0;
    std::cin >> M;

    std::vector<std::tuple<int32_t, int32_t>> bridges(M);
    for (auto &[from, to] : bridges) {
        std::cin >> from >> to;
    }

    auto answer = TaskH(N, M, bridges);
    for (auto distance : answer) {
        std::cout << distance << std::endl;
    }

    return 0;
}
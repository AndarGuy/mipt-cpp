/*

Проверить планарен ли граф.

*/

#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

#define V constant_v
#define E constant_e

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph_t;

int32_t TaskJ([[maybe_unused]] const int32_t V, [[maybe_unused]] const int32_t E,
              const std::vector<std::pair<int32_t, int32_t>> &bridges) {
    graph_t graph(V);
    for (auto [from, to] : bridges) {
        boost::add_edge(from, to, graph);
    }

    return boost::boyer_myrvold_planarity_test(graph);
}

int main() {
    uint32_t V = 0;
    uint32_t E = 0;
    std::cin >> V >> E;

    std::vector<std::pair<int32_t, int32_t>> bridges(E);
    for (auto &[from, to] : bridges) {
        std::cin >> from >> to;
    }

    if (TaskJ(V, E, bridges)) {
        std::cout << "YES";
        return 0;
    }
    std::cout << "NO";
}
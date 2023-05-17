/*

Одно разбросанное на островах Океании государство решило создать сеть автомобильных дорог (вернее, мостов). По каждому
мосту можно перемещаться в обе стороны. Был разработан план очередности строительства мостов и известно, что после
постройки всех мостов можно будет проехать по ним с каждого острова на каждый (возможно, через некоторые промежуточные
острова). Переменные и функции с именем link запрещены.

Однако, этот момент может наступить до того, как будут построены все мосты. Ваша задача состоит в нахождении такого
минимального количества мостов, после постройки которых ( в порядке строительства по плану ) можно будет попасть с
любого острова на любой другой.

*/

#include <iostream>
#include <vector>
#include <map>
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/connected_components.hpp>

#define N constant_n
#define M constant_m

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
                              boost::property<boost::edge_weight_t, uint32_t>>
    graph_t;

int32_t TaskF([[maybe_unused]] const uint32_t N, [[maybe_unused]] const uint32_t M,
              const std::vector<std::pair<int32_t, int32_t>> &bridges) {
    graph_t graph(N);
    int32_t answer = 0;
    for (size_t bridge = 0; bridge < M; bridge++) {
        auto [from, to] = bridges[bridge];
        boost::add_edge(from, to, graph);
        std::map<graph_t::vertex_descriptor, int32_t> property_map;
        int32_t components = boost::connected_components(graph, boost::make_assoc_property_map(property_map));
        if (components == 1) {
            answer = bridge;
            break;
        }
    }

    return answer + 1;
}

int main() {
    uint32_t N = 0;
    std::cin >> N;

    uint32_t M = 0;
    std::cin >> M;

    std::vector<std::pair<int32_t, int32_t>> bridges(M);
    for (auto &[from, to] : bridges) {
        std::cin >> from >> to;
    }

    auto answer = TaskF(N, M, bridges);
    std::cout << answer << std::endl;

    return 0;
}
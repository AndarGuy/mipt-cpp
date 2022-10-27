#include "./modules/graphs/arc_graph/arc_graph.hpp"

int main() {
    std::unique_ptr<IGraph> graph = std::make_unique<ArcGraph>(8);
}
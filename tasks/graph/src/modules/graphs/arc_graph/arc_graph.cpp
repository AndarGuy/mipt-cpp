#include "arc_graph.hpp"

ArcGraph::ArcGraph(size_t vertices_amount) noexcept {
    this->vertices_amount = vertices_amount;
}

ArcGraph::ArcGraph(const IGraph *graph) noexcept : ArcGraph::ArcGraph(graph->vertices_count()) {
    std::vector<size_t> vertices;
    for (size_t from = 0; from < graph->vertices_count(); from++, vertices.clear()) {
        graph->get_next_vertices(from, vertices);
        for (size_t to : vertices) this->add_edge(from, to);
    }
}

void ArcGraph::add_edge(size_t from, size_t to) {
    this->edges.push_back({from, to});
}

size_t ArcGraph::vertices_count() const noexcept {
    return this->vertices_amount;
}

void ArcGraph::get_next_vertices(size_t vertex, std::vector<size_t> &vertices) const noexcept {
    for (std::pair<size_t, size_t> edge : this->edges) {
        if (edge.first == vertex) vertices.push_back(edge.second);
    }
}

void ArcGraph::get_previous_vetices(size_t vertex, std::vector<size_t> &vertices) const noexcept {
    for (std::pair<size_t, size_t> edge : this->edges) {
        if (edge.second == vertex) vertices.push_back(edge.first);
    }
}
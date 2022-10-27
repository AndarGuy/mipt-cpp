#include "set_graph.hpp"

SetGraph::SetGraph(size_t vertices_amount) noexcept : vertices_amount(vertices_amount) {
    this->contiguity_list = std::vector<std::unordered_set<size_t>>(vertices_amount);
    this->reversed_contiguity_list = std::vector<std::unordered_set<size_t>>(vertices_amount);
}

SetGraph::SetGraph(const IGraph *graph) noexcept : SetGraph::SetGraph(graph->vertices_count()) {
    std::vector<size_t> vertices;
    for (size_t from = 0; from < graph->vertices_count(); from++, vertices.clear()) {
        graph->get_next_vertices(from, vertices);
        for (size_t to : vertices) this->add_edge(from, to);
    }
}

void SetGraph::add_edge(size_t from, size_t to) {
    this->contiguity_list[from].insert(to);
    this->reversed_contiguity_list[to].insert(from);
}

size_t SetGraph::vertices_count() const noexcept {
    return this->vertices_amount;
}

void SetGraph::get_next_vertices(size_t vertex, std::vector<size_t> &vertices) const noexcept {
    for (size_t v : this->contiguity_list[vertex]) vertices.push_back(v);
}

void SetGraph::get_previous_vetices(size_t vertex, std::vector<size_t> &vertices) const noexcept {
    for (size_t v : this->reversed_contiguity_list[vertex]) vertices.push_back(v);
}
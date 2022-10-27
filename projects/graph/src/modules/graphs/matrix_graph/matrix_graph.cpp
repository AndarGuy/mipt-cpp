#include "matrix_graph.hpp"

MatrixGraph::MatrixGraph(size_t vertices_amount) noexcept : vertices_amount(vertices_amount) {
    this->contiguity_matrix = std::vector<std::vector<bool>>(vertices_amount, std::vector<bool>(vertices_amount, 0));
}

MatrixGraph::MatrixGraph(const IGraph *graph) noexcept : MatrixGraph::MatrixGraph(graph->vertices_count()) {
    std::vector<size_t> vertices;
    for (size_t from = 0; from < graph->vertices_count(); from++, vertices.clear()) {
        graph->get_next_vertices(from, vertices);
        for (size_t to : vertices) this->add_edge(from, to);
    }
}

void MatrixGraph::add_edge(size_t from, size_t to) {
    this->contiguity_matrix[from][to] = true;
}

void MatrixGraph::get_next_vertices(size_t vertex, std::vector<size_t> &vertices) const noexcept {
    for (size_t i = 0; i < this->vertices_amount; i++) {
        if (this->contiguity_matrix[vertex][i]) vertices.push_back(i);
    }
}

size_t MatrixGraph::vertices_count() const noexcept {
    return this->vertices_amount;
}

void MatrixGraph::get_previous_vetices(size_t vertex, std::vector<size_t> &vertices) const noexcept {
    for (size_t i = 0; i < this->vertices_amount; i++) {
        if (this->contiguity_matrix[i][vertex]) vertices.push_back(i);
    }
}
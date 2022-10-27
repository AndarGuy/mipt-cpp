#include <vector>

#include "../igraph.hpp"

class ArcGraph : IGraph {
   private:
    std::vector<std::pair<size_t, size_t>> edges;
    size_t vertices_amount;

   public:
    // Конструктор от числа вершин.
    ArcGraph(size_t vertices_amount) noexcept;

    // Конструктор от указателя на базовый класс.
    ArcGraph(IGraph *graph);

    // Конструктор копирования и копирующее присваивание должны быть явно запрещены.
    ArcGraph(IGraph &graph) = delete;

    // Конструктор копирования и копирующее присваивание должны быть явно запрещены.
    IGraph operator=(IGraph &graph) = delete;

    void add_edge(size_t from, size_t to) override;

    size_t vertices_count() const noexcept override;

    // Метод `get_next_vertices`, возвращающий список вершин, в которые можно попасть из данной.
    void get_next_vertices(size_t vertex, std::vector<size_t> &vertices) const noexcept override;

    // Метод `get_previous_vetices`, возвращающий список вершин, из которых можно попасть в данную.
    void get_previous_vetices(size_t vertex, std::vector<size_t> &vertices) const noexcept override;
};
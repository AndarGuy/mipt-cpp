#include <vector>

#include "igraph.hpp"

class MatrixGraph : public IGraph {
 private:
  std::vector<std::vector<bool>> contiguity_matrix;
  size_t vertices_amount;

 public:
  // Конструктор от числа вершин.
  MatrixGraph(size_t vertices_amount) noexcept;

  // Конструктор от указателя на базовый класс.
  MatrixGraph(const IGraph* graph) noexcept;

  // Конструктор копирования и копирующее присваивание должны быть явно запрещены.
  MatrixGraph(IGraph& graph) = delete;

  // Конструктор копирования и копирующее присваивание должны быть явно запрещены.
  IGraph operator=(IGraph& graph) = delete;

  void add_edge(size_t from, size_t to) override;

  size_t vertices_count() const noexcept override;

  // Метод `get_next_vertices`, возвращающий список вершин, в которые можно попасть из данной.
  void get_next_vertices(size_t vertex, std::vector<size_t>& vertices) const noexcept override;

  // Метод `get_previous_vetices`, возвращающий список вершин, из которых можно попасть в данную.
  void get_previous_vetices(size_t vertex, std::vector<size_t>& vertices) const noexcept override;
};
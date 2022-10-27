#include <stdexcept>
#include <vector>

struct IGraph {
   public:
    virtual ~IGraph() = default;

    virtual void add_edge(size_t from, size_t to) = 0;
    virtual size_t vertices_count() const noexcept = 0;
    virtual void get_next_vertices(size_t vertex, std::vector<size_t>& vertices) const noexcept = 0;
    virtual void get_previous_vetices(size_t vertex, std::vector<size_t>& vertices) const noexcept = 0;
};

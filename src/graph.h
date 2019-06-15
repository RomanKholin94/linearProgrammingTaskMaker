#include "component.h"

class Graph {
private:
    std::vector<Component> _components;
public:
    Graph()
        : _components(std::vector<Component>(0))
    {
    }

    Graph(const Graph& copy) 
        : _components(copy._components)
    {
    }

    Graph& operator=(const Graph& copy) 
    {
        _components = copy._components;
        return *this;
    }

    Graph(Graph&& move) 
        : _components(std::move(move._components))
    {
    }

    Graph& operator=(Graph&& move) 
    {
        _components = std::move(move._components);
        return *this;
    }

    Graph(std::istream& in) {
        size_t size;
        in >> size;
        for (size_t i = 0; i < size; ++i) {
            _components.push_back(Component(in));
        }
    }

    Component& operator[](const size_t i) {
        return _components[i];
    }

    const Component& operator[](const size_t i) const {
        return _components[i];
    }

    void dumpGraph(std::ostream& out) {
        out << _components.size() << std::endl;
        for (size_t i = 0; i < _components.size(); ++i) {
            _components[i].dumpComponent(out);
        }
    }

    size_t size() const {
        return _components.size();
    }
};

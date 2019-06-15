#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

enum Type{
    UNKNOWN,
    CYCLE,
    CHAIN
};

class Component {
private:
    const char CYCLE = 'c';
    const char CHAIN = 'h';

    Type _type;
    std::vector<std::pair<int32_t, size_t> > _edges;
public:
    Component()
        : _type(Type::UNKNOWN)
        , _edges(std::vector<std::pair<int32_t, size_t> >(0))
    {
    }

    Component(const Component& copy)
        : _type(copy._type)
        , _edges(copy._edges)
    {
    }

    Component& operator=(const Component& copy) 
    {
        _type = copy._type;
        _edges = copy._edges;
        return *this;
    }

    Component(Component&& move) 
        : _type(move._type)
        , _edges(std::move(move._edges))
    {
    }

    Component& operator=(Component&& move) 
    {
        _type = move._type;
        _edges = std::move(move._edges);
        return *this;
    }

    Component(std::istream& in) {
        char type;
        in >> type;
        if (type == CYCLE) {
            _type = Type::CYCLE;
        } else if (type == CHAIN) {
            _type = Type::CHAIN;
        } else {
            throw std::exception();
        }
        size_t size;
        in >> size;
        for (size_t i = 0; i < size; ++i) {
            std::pair<int32_t, int32_t> edge;
            char point;
            in >> edge.first >> point >> edge.second;
            _edges.push_back(edge);
        }
    }

    std::pair<int32_t, size_t>& operator[](const size_t i) {
        return _edges[i];
    }

    const std::pair<int32_t, size_t>& operator[](const size_t i) const {
        return _edges[i];
    }

    void dumpComponent(std::ostream& out) {
        if (_type == Type::CYCLE) {
            out << CYCLE;
        } else if (_type == Type::CHAIN) {
            out << CHAIN;
        } else {
            throw std::exception();
        }
        out << " " <<  _edges.size();
        for (size_t i = 0; i < _edges.size(); ++i) {
            out << " " <<  _edges[i].first << "." << _edges[i].second;
        }
        out << std::endl;
    }

    size_t size() const {
        return _edges.size();
    }

    Type type() {
        return _type;
    }
};

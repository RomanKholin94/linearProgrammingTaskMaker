#include <functional>
#include "graph.h"

class Solver {
private:
    std::ostream& _out;

    static std::string writeMultiplication(std::string c, size_t time) {
        std::string answer = c;
        for (size_t i = 0; i + 1 < time; ++i) {
            answer += " + " + c;
        }
        return answer;
    }

    static void writeNumberOfexpression(std::ostream& _out) {
        static size_t numberOfexpression = 0;
        ++numberOfexpression;
        _out << "expression" << numberOfexpression << ": ";
    }

    static void writeSum(const size_t x, const size_t y, const std::pair<int32_t, size_t>& a, const std::pair<size_t, size_t>& b, std::ostream& _out) {
        _out << "u" << x << " - " << "u" << y << " + "
                  << writeMultiplication("z_" + std::to_string(std::abs(a.first)) + "_" + std::to_string(a.second)
                  + "_" + std::to_string(b.second), x) << " <= " << x << std::endl; 
    }

    static void writeMaximaze(const Component& a, const Component& b, std::vector<std::string>& /*zVariables*/, std::ostream& _out) {
        _out << "Maximize" << std::endl;
        writeNumberOfexpression(_out);
        for (size_t i = 1; i < a.size() + b.size(); ++i) {
            _out << "p" << i << " + ";
        }
        _out << "p" << a.size() + b.size() << std::endl;
    }

    static void writeSubjectTo(const Component& a, const Component& b, std::vector<std::string>& zVariables, std::ostream& _out) {
        _out << "Subject To" << std::endl;
        for (size_t i = 1; i <= a.size() + b.size(); ++i) {
            writeNumberOfexpression(_out);
            _out << writeMultiplication("p" + std::to_string(i), i) << " - u" << i << " <= 0" << std::endl;
        }
        for (size_t i = 0; i < a.size(); ++i) {
            bool first = true;
            for (size_t j = 0; j < b.size(); ++j) {
                if (std::abs(a[i].first) == std::abs(b[j].first)) {
                    if (!first) {
                        _out << " + ";
                    } else {
                        writeNumberOfexpression(_out);
                        first = false;
                    }
                    _out << "z_" << std::abs(a[i].first) << "_" << a[i].second << "_" << b[j].second; 
                }
            }
            _out << " = 1" << std::endl;
        }
        for (size_t j = 0; j < b.size(); ++j) {
            bool first = true;
            for (size_t i = 0; i < a.size(); ++i) {
                if (std::abs(a[i].first) == std::abs(b[j].first)) {
                    if (!first) {
                        _out << " + ";
                    } else {
                        writeNumberOfexpression(_out);
                        first = false;
                    }
                    _out << "z_" << std::abs(a[i].first) << "_" << a[i].second << "_" << b[j].second; 
                }
            }
            _out << " = 1" << std::endl;
        }
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < b.size(); ++j) {
                if (std::abs(a[i].first) == std::abs(b[j].first)) {
                    zVariables.push_back(
                        "z_" + std::to_string(std::abs(a[i].first)) + '_' + std::to_string(a[i].second) + '_' + std::to_string(b[j].second)
                    );
                }
            }
        }
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < b.size(); ++j) {
                if (std::abs(a[i].first) == std::abs(b[j].first)) {
                    size_t beginA = i + 1,
                           endA = (i + 1) % a.size() + 1,
                           beginB = a.size() + j + 1,
                           endB = a.size() + (j + 1) % b.size() + 1;
                    if (a[i].first == b[j].first) {
                        writeNumberOfexpression(_out);
                        writeSum(beginA, beginB, a[i], a[j], _out);
                        writeNumberOfexpression(_out);
                        writeSum(beginB, beginA, a[i], a[j], _out);
                        writeNumberOfexpression(_out);
                        writeSum(endA, endB, a[i], a[j], _out);
                        writeNumberOfexpression(_out);
                        writeSum(endB, endA, a[i], a[j], _out);
                   } else {
                        writeNumberOfexpression(_out);
                        writeSum(endA, beginB, a[i], a[j], _out);
                        writeNumberOfexpression(_out);
                        writeSum(beginB, endA, a[i], a[j], _out);
                        writeNumberOfexpression(_out);
                        writeSum(beginA, endB, a[i], a[j], _out);
                        writeNumberOfexpression(_out);
                        writeSum(endB, beginA, a[i], a[j], _out);
                    }
                }
            }
        }
    }

    static void writeBounds(const Component& a, const Component& b, std::vector<std::string>& /*zVariables*/, std::ostream& _out) {
        _out << "Bounds" << std::endl;
        for (size_t i = 1; i <= a.size() + b.size(); ++i) {
            _out << "0 <= p" << i << " <= 1" << std::endl;
        }
        for (size_t i = 1; i <= a.size() + b.size(); ++i) {
            _out << "0 <= u" << i << " <= " << i << std::endl;
        }
    }

    void writeBoundsForZVariables(std::vector<std::string>& zVariables) {
        for (size_t i = 0; i < zVariables.size(); ++i) {
            _out << "0 <= " << zVariables[i] << " <= 1" << std::endl;
        }
    }

    static void writeGeneral(const Component& a, const Component& b, std::vector<std::string>& /*zVariables*/, std::ostream& _out) {
        _out << "General" << std::endl;
        for (size_t i = 1; i <= a.size() + b.size(); ++i) {
            _out << "p" << i << std::endl;
        }
        for (size_t i = 1; i <= a.size() + b.size(); ++i) {
            _out << "u" << i << std::endl;
        }
    }

    void writeGeneralForZVariables(std::vector<std::string>& zVariables) {
        for (size_t i = 0; i < zVariables.size(); ++i) {
            _out << zVariables[i] << std::endl;
        }
    }

    void writeEnd() {
        _out << "End" << std::endl;
    }

    void forAllComponents(
        const Graph& graphA,
        const Graph& graphB,
	std::vector<std::string>& zVariables,
        void (*func)(const Component&, const Component&, std::vector<std::string>&, std::ostream&)
    ) {
        for (size_t i = 0; i < graphA.size(); ++i) {
            for (size_t j = 0; j < graphB.size(); ++j) {
                func(graphA[i], graphB[j], zVariables, _out);
            }
        }
    }
public:
    Solver(std::ostream& out) : _out(out) {}

    void solve(const Graph& graphA, const Graph& graphB) {
        std::vector<std::string> zVariables;
        forAllComponents(graphA, graphB, zVariables, writeMaximaze);
        forAllComponents(graphA, graphB, zVariables, writeSubjectTo);
        forAllComponents(graphA, graphB, zVariables, writeBounds);
        writeBoundsForZVariables(zVariables);
        forAllComponents(graphA, graphB, zVariables, writeGeneral);
        writeGeneralForZVariables(zVariables);
	writeEnd();
    }
};

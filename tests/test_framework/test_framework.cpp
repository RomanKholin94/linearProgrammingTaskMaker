#include <gtest/gtest.h>
#include <fstream>
#include "../../src/solver.h"

class TestFramework : public ::testing::Test {
public:
    TestFramework() {}
    ~TestFramework() {}
    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestFramework, DateJson) {
    std::fstream fin, fout, f1, f2;
    fin.open("../tests/test_framework/test_framework_input.txt", std::fstream::in);
    fout.open("../tests/test_framework/test_framework_output.txt", std::fstream::out);
    
    Graph a(fin);
    Graph b(fin);
    Solver solver(fout);
    solver.solve(a, b);
    fout.close();

    std::string first, second;
    f1.open("../tests/test_framework/test_framework_output.txt", std::fstream::in);
    f2.open("../tests/test_framework/test_framework_output_canonical.txt", std::fstream::in);
    getline(f1, first, '\0');
    getline(f2, second, '\0');

    ASSERT_EQ(first, second);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

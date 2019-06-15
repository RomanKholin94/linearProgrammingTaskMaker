#include <gtest/gtest.h>
#include "../../src/graph.h"

class TestGraph : public ::testing::Test {
public:
    TestGraph() {}
    ~TestGraph() {}
    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestGraph, DateJson) {
    freopen("../tests/test_graph/test_graph_input.txt", "r", stdin);
    Graph a(std::cin);
    ASSERT_EQ(a.size(), 1);
    ASSERT_EQ(a[0].size(), 3);
    ASSERT_EQ(a[0][0].first, -1);
    ASSERT_EQ(a[0][0].second, 1u);
    ASSERT_EQ(a[0][1].first, -2);
    ASSERT_EQ(a[0][1].second, 1u);
    ASSERT_EQ(a[0][2].first, -1);
    ASSERT_EQ(a[0][2].second, 2u);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

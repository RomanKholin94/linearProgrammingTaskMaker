#include <gtest/gtest.h>
#include "../../src/component.h"

class TestComponent : public ::testing::Test {
public:
    TestComponent() {}
    ~TestComponent() {}
    void SetUp() {}
    void TearDown() {}
};

TEST_F(TestComponent, DateJson) {
    freopen("../tests/test_component/test_component_input.txt", "r", stdin);
    Component a(std::cin);
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(a[0].first, -1);
    ASSERT_EQ(a[0].second, 1u);
    ASSERT_EQ(a[1].first, -2);
    ASSERT_EQ(a[1].second, 1u);
    ASSERT_EQ(a[2].first, -1);
    ASSERT_EQ(a[2].second, 2u);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

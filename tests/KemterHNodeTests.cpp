#include <gtest/gtest.h>
#include "kemter_hnode.h"
#include "kemter_hmap.h"

TEST(ExampleTest, DemonstratedQTestMacros) {

    const std::string key = "test";
    const int value = 6;
    kemter::kemter_hnode<std::string, int> h(key, value);

    ASSERT_EQ(h.getKey(), key);
    ASSERT_EQ(h.getValue(), value);

    kemter::kemter_hnode<std::string, size_t> q("test", 6234);
    ASSERT_EQ(q.getKey(), "test");
    ASSERT_EQ(q.getValue(), 6234);

    // kemter::kemter_hmap<int, int> map;
    // map.add(1, 1);
    kemter::kemter_hmap<std::string, int> test;
    test.add("furkan", 123);
}
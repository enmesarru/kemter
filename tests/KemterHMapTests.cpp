#include <gtest/gtest.h>
#include "kemter_hmap.h"
#include "kemterdb.h"

TEST(KemterMapTests, MapTest)
{
    kemter::kemter_hmap<std::string, int> test;
    test.add("test1", 123);
    test.add("tester", 444);
    ASSERT_EQ(test.size(), 2);
    test.remove("tester");
    ASSERT_EQ(test.size(), 1);
    test.put("test1", 555);

    test.remove("qweqw");

    kemter::kemter_hmap<float, int> c;
    c.add(1.f, 123);
    ASSERT_EQ(c.size(), 1);
    c.remove(1.f);
    ASSERT_EQ(c.size(), 0);
}
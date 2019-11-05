#include <gtest/gtest.h>
#include "kemter_hmap.h"
#include "kemterdb.h"
#include "kemter_types.h"

TEST(KemterMapTests, MapAddTest) {
    kemter::kemter_hmap<std::string, int> test;
    test.add("test1", 123);
    test.add("test2", 4321);

    ASSERT_EQ(test.size(), 2);
}

TEST(KemterMapTests, MapRemoveTest) {
    kemter::kemter_hmap<std::string, int> test;

    test.add("test1", 123);
    test.add("test2", 4321);
    test.remove("test1");

    ASSERT_EQ(test.size(), 1);
}

TEST(KemterMapTests, MapPutTest) {
    kemter::kemter_hmap<std::string, kemter::type::TypeWrapper> test;
    test.add("test1", 123);

    test.put("test1", 555);

    kemter::type::TypeWrapper wrapper = test.get("test1");

    std::visit(
    kemter::type::base_visitor(
        [&](kemter::type::Type<int> s) { 
            ASSERT_EQ(s.value(), 555) ;
        },
        [&](auto &&) {  }
    ), wrapper);
}
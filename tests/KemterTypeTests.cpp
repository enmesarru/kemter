#include <memory>
#include <variant>
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "kemter_types.h"
#include "kemter_hmap.h"

TEST(KemterTypeTest, TypeTest) {
    kemter::kemter_hmap<std::string, kemter::type::TypeWrapper> map;;
    
    map.add("key1", kemter::type::Type<int>(123));
    map.add("key2", kemter::type::Type<std::string>("furkan"));

    ASSERT_EQ(map.size(), 2);
    
    // auto test2 = std::get<0>(map.get("key1")).value(); // get value, directly
    // auto test2 = std::get<1>(map.get("key2"));
    
    std::vector<kemter::type::TypeWrapper> container;

    auto testInt = map.get("key1");
    auto testString = map.get("key2");
    auto testNone =  map.get("key10");

    container.push_back(testInt);
    container.push_back(testString);
    container.push_back(testNone);
    
    for(auto& data: container) {
        std::visit(
            kemter::type::base_visitor(
                [](kemter::type::Type<int> j) { ASSERT_EQ(j.value(), 123); },
                [](kemter::type::Type<std::string> s) { ASSERT_EQ(s.value(), "furkan"); },
                [](auto &&) { std::cout << "unknown type";}
            )
        , data);
    }

    map.put("key1", kemter::type::Type<int>(99));
    auto newValue = map.get("key1");
    ASSERT_EQ(std::get<0>(newValue).value(), 99);

    map.remove("key1");
    ASSERT_EQ(map.size(), 1);
}
#include <memory>
#include <any>
#include <iostream>
#include <gtest/gtest.h>
#include "kemter_types.h"
#include "kemter_hmap.h"

template<typename T>
using TypeWrapper = kemter::type::gdata_type<T>;
TEST(KemterTypeTest, TypeTest) {
    kemter::kemter_hmap<std::string, std::any> map;

    auto value1 = std::make_shared<TypeWrapper<std::string>>("value1");
    auto value2 = std::make_shared<TypeWrapper<int>>(1123);
    auto value3 = std::make_shared<TypeWrapper<float>>(2.f);
    
    map.add("key1", value1);
    map.add("key2", value2);
    map.add("key3", value3);

    ASSERT_EQ(map.size(), 3);
    
    const auto& test = map.get("key1");
    const auto& test2 = map.get("key2");
    const auto& testNone = map.get("key6");
    const auto& test3 = map.get("key3");

    ASSERT_EQ(std::any_cast<std::string>(test), "value1");
    ASSERT_EQ(std::any_cast<int>(test2), 1123);
    ASSERT_EQ(std::any_cast<float>(test3), 2.f);

    map.put("key1", std::make_shared<TypeWrapper<int>>(1));
    const auto& newValue = map.get("key1");
    ASSERT_EQ(std::any_cast<int>(newValue), 1);

    map.remove("key1");
    ASSERT_EQ(map.size(), 2);
    
    const auto& deletedValue = map.get("key1");
    ASSERT_FALSE(deletedValue.has_value());
}
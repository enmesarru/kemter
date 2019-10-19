#include <gtest/gtest.h>
#include "kemter_types.h"
#include "kemter_hmap.h"
#include <memory>

using T = kemter::types::data_type;
using KeyT = std::shared_ptr<T>;

TEST(KemterTypeTest, TypeTest) {
    kemter::kemter_hmap<std::string, KeyT> h;
    auto c = std::make_shared<T>(kemter::types::gdata_type<std::string>("furkan"));
    auto d = std::make_shared<T>(kemter::types::gdata_type<int>(1));

    h.add("f", c);
    h.add("a", d);

    ASSERT_EQ(h.size(), 2);
    

}
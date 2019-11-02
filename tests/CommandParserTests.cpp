#include <gtest/gtest.h>
#include "command_parser.h"

TEST(CommandParserTest, CommandParser) {
    std::string request = "/GET TestKey TestValue";

    command_parser p;

    auto parse_command = p.parse(request);

    command test = *(parse_command.get());

    ASSERT_EQ(test.method, command_type::GET);
    ASSERT_EQ(test.key, "TestKey");
    ASSERT_EQ(test.value, "TestValue");
}
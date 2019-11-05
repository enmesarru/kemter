#include <gtest/gtest.h>
#include "command_parser.h"

TEST(CommandParserTest, CommandParserWrongRequest) {
    command_parser p;

    std::string wrong_request = "GT TestKey TestValue";
    auto parse_wrong_command = p.parse(wrong_request);

    ASSERT_EQ(parse_wrong_command.get(), nullptr);
}

TEST(CommandParserTest, CommandParserUnknownCommand) {
    command_parser p;

    std::string unknown_command = "/RUN TestKey TestValue";
    auto parse_unknown_command = p.parse(unknown_command);
    command unknown_command_value = *(parse_unknown_command.get());

    ASSERT_EQ(unknown_command_value.method, command_type::UNKNOWN);
}

TEST(CommandParserTest, CommandParserSetCommand) {
    command_parser p;

    std::string set_command = "/SET TestKey TestValue";
    auto parse_set_command = p.parse(set_command);
    command set_command_value = *(parse_set_command.get());

    ASSERT_EQ(set_command_value.method, command_type::SET);
    ASSERT_EQ(set_command_value.key, "TestKey");
    ASSERT_EQ(set_command_value.value, "TestValue");
}

TEST(CommandParserTest, CommandParserTestDeleteCommand) {
    command_parser p;

    std::string delete_command = "/DEL TestKey";
    auto parse_delete_command = p.parse(delete_command);
    command delete_command_value = *(parse_delete_command.get());

    ASSERT_EQ(delete_command_value.method, command_type::DELETE);
    ASSERT_EQ(delete_command_value.key, "TestKey");
}


TEST(CommandParserTest, CommandParserGET) {
    std::string request = "/GET TestKey TestValue";

    command_parser p;

    auto parse_command = p.parse(request);
    command& test = *(parse_command.get());

    ASSERT_EQ(test.method, command_type::GET);
    ASSERT_EQ(test.key, "TestKey");
    ASSERT_EQ(test.value, "TestValue");

    std::string set_command = "/SET TestKey TestValue";
    auto parse_set_command = p.parse(set_command);
    command set_command_value = *(parse_set_command.get());

    ASSERT_EQ(set_command_value.method, command_type::SET);
    ASSERT_EQ(set_command_value.key, "TestKey");
    ASSERT_EQ(set_command_value.value, "TestValue");
}
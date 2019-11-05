#include "kemterdb.h"

kemterdb::kemterdb() {}

kemterdb::~kemterdb() { }

void kemterdb::add(const std::string& key, const kemter::type::TypeWrapper& value) {
    try
    {
        table.add(key, value);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
};

bool kemterdb::remove(const std::string& key) {
    try
    {
        table.remove(key);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
};

void kemterdb::put(const std::string& key, const kemter::type::TypeWrapper& value) {
    try
    {
        table.put(key, value);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
};

kemter::type::TypeWrapper kemterdb::get(const std::string& key) {
    const auto& value = table.get(key);
    return value;
};
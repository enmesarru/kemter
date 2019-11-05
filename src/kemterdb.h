#ifndef KEMTER_DB_H
#define KEMTER_DB_H
#include <memory>
#include "kemter_hmap.h"
#include "kemter_types.h"

class kemterdb
{
private:
    kemter::kemter_hmap<std::string, kemter::type::TypeWrapper> table;
public:
    kemterdb();
    ~kemterdb();
    void add(const std::string& key, const kemter::type::TypeWrapper& value);
    bool remove(const std::string& key);
    void put(const std::string& key, const kemter::type::TypeWrapper& value);
    kemter::type::TypeWrapper get(const std::string& key);
};

#endif // !KEMTER_DB_H
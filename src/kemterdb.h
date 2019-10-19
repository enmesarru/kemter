#ifndef KEMTER_DB_H
#define KEMTER_DB_H
#include <memory>
#include "kemter_hmap.h"
#include "kemter_types.h"
class kemterdb
{
    using Type = kemter::types::data_type;
    using TypeContainer = std::shared_ptr<Type>;
private:
    kemter::kemter_hmap<std::string, TypeContainer> table;
public:
    kemterdb(/* args */);
    ~kemterdb();
};

kemterdb::kemterdb(/* args */)
{
}

kemterdb::~kemterdb()
{
}


#endif // !KEMTER_DB_H
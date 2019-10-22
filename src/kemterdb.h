#ifndef KEMTER_DB_H
#define KEMTER_DB_H
#include <memory>
#include <any>
#include "kemter_hmap.h"
#include "kemter_types.h"

class kemterdb
{
private:
    kemter::kemter_hmap<std::string, std::any> table;
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
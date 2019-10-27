#ifndef KEMTER_DB_H
#define KEMTER_DB_H
#include <memory>
#include <any>
#include "kemter_hmap.h"
#include "kemter_types.h"

class kemterdb
{
private:
    kemter::kemter_hmap<std::string, kemter::type::TypeWrapper> table;
public:
    kemterdb();
    ~kemterdb();
};

#endif // !KEMTER_DB_H
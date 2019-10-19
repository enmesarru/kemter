#ifndef basetype_H
#define basetype_H
#include <string>
#include <memory>

namespace kemter::types
{
    class data_type {
    public:
        data_type() {};
        ~data_type() {};

        // virtual void parse() = 0;
    };

    template<typename T>
    class gdata_type: public data_type {
    public:
        gdata_type(const T& t_value) {
            this->m_value = std::make_shared<T>(t_value);
        };
        ~gdata_type() {};
        T value() {
            return m_value;
        };
    private:
        std::shared_ptr<T> m_value;
    };

    
};

#endif // !basetype_H
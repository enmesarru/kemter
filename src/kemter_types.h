#ifndef basetype_H
#define basetype_H
#include <string>
#include <memory>
#include <variant>

namespace kemter::type
{
    enum class Status {
        NodeNotExist,
    };

    template<typename T>
    class gdata_type {
    public:
        gdata_type(const T& t_value) {
            m_value = std::make_shared<T>(t_value);
        };
        ~gdata_type() {};
        T& value() const {
            return *(this->m_value.get());
        };
    private:
        std::shared_ptr<T> m_value;
    };

    template<typename T>
    using Type = gdata_type<T>;

    using TypeWrapper = std::variant< Type<int>, Type<std::string>, Status, std::monostate>;

    template <class ...Ts>
    struct base_visitor: Ts... {
        base_visitor(Ts const&&... fs) : Ts{fs}... { };
        using Ts::operator()...;
    };
    
};
#endif // !basetype_H
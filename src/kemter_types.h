#ifndef basetype_H
#define basetype_H
#include <string>
#include <memory>
#include <any>

namespace kemter::type
{
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

    template<typename T>
    using TypeWrapper = std::shared_ptr<Type<T>>;

    template<typename Value>
    Value TypeParser(const std::any& data)
    {
        const auto& type = std::any_cast<TypeWrapper<Value>>(data);
        const auto& value = std::any_cast<Type<Value>*>(type.get())->value();
        return value;
    }
};
#endif // !basetype_H
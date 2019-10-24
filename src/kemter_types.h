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

    template<typename Value>
    Value TypeCheck(const std::type_info& ti, const std::any& value) {
        
        if(!value.has_value()) {
            return Value();
        }

        if(ti == typeid(TypeWrapper<std::string>)) {
            return TypeParser<std::string>(value);
        } else if(ti == typeid(TypeWrapper<int>)) {
            return TypeParser<int>(value);
        } else if(ti == typeid(TypeWrapper<float>)) {
            return TypeParser<float>(value);
        } else {
            return Value();
        }
    }
};
#endif // !basetype_H
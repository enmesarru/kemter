#ifndef basetype_H
#define basetype_H
#include <string>
#include <memory>

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
};

namespace kemter::type::cast {
    template<typename T>
    using Type = kemter::type::gdata_type<T>;

    template<typename T>
    using TypeWrapper = std::shared_ptr<Type<T>>;
}
#endif // !basetype_H
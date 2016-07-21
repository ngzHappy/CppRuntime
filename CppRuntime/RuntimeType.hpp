#ifndef _RUNTIME_TYPE_PRAGMA__ONCE_0x00
#define _RUNTIME_TYPE_PRAGMA__ONCE_0x00 0x00

#include <memory>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <string>
#include <QtCore/qbytearray.h>

#ifndef RUNTIME_TYPE_IMPORT
#define RUNTIME_TYPE_IMPORT
#endif

namespace runtime {
namespace type {

template<typename _T_>
using logical_type=std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<_T_>/**/>/**/>;

class RuntimeType {
public:
    std::type_index type_id;
    std::shared_ptr<void> data;

    operator const std::type_index&() const { return type_id; }
    operator const std::shared_ptr<const void>()const { return data; }
    operator const void *() const { return data.get(); }

    operator void *() { return data.get(); }
    operator std::shared_ptr<void>&() { return data; }

    RuntimeType():type_id(typeid(void*)) {}
    RuntimeType(const std::type_index&argID,const std::shared_ptr<void>&argData):type_id(argID),data(argData) {}
    RuntimeType(const std::type_info&argID,const std::shared_ptr<void>&argData):type_id(argID),data(argData) {}
};

typedef RuntimeType(*TypeCastFunction)(const std::shared_ptr<const void>&);

template<typename _T_>
class __RuntimTypeBase {
public:
    using type=logical_type<_T_>;
    static QByteArray readable_class_name() { return ""; }
    static std::type_index logical_type_index() { return typeid(type); }
    static constexpr bool is_static_type() { return false==std::has_virtual_destructor<type>::value; }
private:
    static_assert(std::is_reference<type>::value==false,"it should not be a ref type");
};

template<typename _T_>
class RuntimType;

template<>
class RuntimType<std::int32_t> final :public __RuntimTypeBase<std::int32_t> {
public:
    static QByteArray readable_class_name() { return "std::int32_t"; }
};

template<>
class RuntimType<std::int64_t> final :public __RuntimTypeBase<std::int64_t> {
public:
    static QByteArray readable_class_name() { return "std::int64_t"; }
};

template<>
class RuntimType<std::int16_t> final :public __RuntimTypeBase<std::int16_t> {
public:
    static QByteArray readable_class_name() { return "std::int16_t"; }
};

template<>
class RuntimType<std::int8_t> final :public __RuntimTypeBase<std::int8_t> {
public:
    static QByteArray readable_class_name() { return "std::int8_t"; }
};

template<>
class RuntimType<std::uint32_t> final :public __RuntimTypeBase<std::uint32_t> {
public:
    static QByteArray readable_class_name() { return "std::uint32_t"; }
};

template<>
class RuntimType<std::uint64_t> final :public __RuntimTypeBase<std::uint64_t> {
public:
    static QByteArray readable_class_name() { return "std::uint64_t"; }
};

template<>
class RuntimType<std::uint16_t> final :public __RuntimTypeBase<std::uint16_t> {
public:
    static QByteArray readable_class_name() { return "std::uint16_t"; }
};

template<>
class RuntimType<std::uint8_t> final :public __RuntimTypeBase<std::uint8_t> {
public:
    static QByteArray readable_class_name() { return "std::int8_t"; }
};

template<>
class RuntimType<float> final :public __RuntimTypeBase<float> {
public:
    static QByteArray readable_class_name() { return "float"; }
};

template<>
class RuntimType<double> final :public __RuntimTypeBase<double> {
public:
    static QByteArray readable_class_name() { return "double"; }
};

template<>
class RuntimType<long double> final :public __RuntimTypeBase<long double> {
public:
    static QByteArray readable_class_name() { return "long double"; }
};

template<>
class RuntimType<char> final :public __RuntimTypeBase<char> {
public:
    static QByteArray readable_class_name() { return "char"; }
};

template<>
class RuntimType<char16_t> final :public __RuntimTypeBase<char16_t> {
public:
    static QByteArray readable_class_name() { return "char16_t"; }
};

template<>
class RuntimType<char32_t> final :public __RuntimTypeBase<char32_t> {
public:
    static QByteArray readable_class_name() { return "char32_t"; }
};

template<>
class RuntimType<bool> final :public __RuntimTypeBase<bool> {
public:
    static QByteArray readable_class_name() { return "bool"; }
};

template<>
class RuntimType<std::string> final :public __RuntimTypeBase<std::string> {
public:
    static QByteArray readable_class_name() { return "std::string"; }
};


RUNTIME_TYPE_IMPORT TypeCastFunction get_static_class_cast_function(const std::type_index&,const std::type_index&);
RUNTIME_TYPE_IMPORT void set_static_class_cast_function(const std::type_index&,const std::type_index&,TypeCastFunction);

}
}

#endif


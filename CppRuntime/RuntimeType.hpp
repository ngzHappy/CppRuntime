#ifndef _RUNTIME_TYPE_PRAGMA__ONCE_0x00
#define _RUNTIME_TYPE_PRAGMA__ONCE_0x00 0x00

#include <string>
#include <memory>
#include <bitset>
#include <utility>
#include <cstddef>
#include <cstdint>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <QtCore/qglobal.h>
#include <QtCore/qbytearray.h>

#if defined(LIBRARY_CPP_RUNTIME)
#  define RUNTIME_TYPE_IMPORT Q_DECL_EXPORT
#else
#  define RUNTIME_TYPE_IMPORT Q_DECL_IMPORT
#endif

namespace runtime {
namespace type {

template<typename _T_>
using logical_type=std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<_T_>/**/>/**/>;

class RUNTIME_TYPE_IMPORT SharedVoidType final {
    std::bitset<sizeof(void*)*8>flags;
    union Data {
    public:
        std::shared_ptr<void>shared_data;
        void * plain_data;
        Data() {}
        ~Data() {}
    }data_;
public:

    enum {
        IS_CONST,
        IS_PLAINDATA,
    };

    SharedVoidType();
    SharedVoidType(const SharedVoidType&arg);
    SharedVoidType(SharedVoidType&&arg);
    SharedVoidType(decltype(nullptr)):SharedVoidType() {}
    SharedVoidType(void *arg);
    SharedVoidType(const void * arg);
    SharedVoidType(std::shared_ptr<void>arg);
    SharedVoidType(std::shared_ptr<const void>arg);

    template<typename _T_>
    SharedVoidType(std::shared_ptr<_T_>arg) 
        :SharedVoidType(std::shared_ptr<void>(std::move(arg))){}

    template<typename _T_>
    SharedVoidType(std::shared_ptr<const _T_>arg) 
        :SharedVoidType(std::shared_ptr<const void>(std::move(arg))){}

    void * data();
    const void * data()const;

    const void *get()const { return data(); }
    void *get() { return data(); }

    bool is_const() const { return flags.test(IS_CONST); }
    bool is_plain_data() const { return flags.test(IS_PLAINDATA); }
    operator bool()const { if (is_plain_data()) { return data_.plain_data; }return bool(data_.shared_data); }

    SharedVoidType&operator=(const SharedVoidType&arg);
    SharedVoidType&operator=(SharedVoidType&&arg);

    ~SharedVoidType();
};

class RuntimeType {
public:
    std::type_index type_id;
    SharedVoidType data;

    operator const std::type_index&() const { return type_id; }
    operator const void *() const { return data.get(); }
    operator void *() { return data.get(); }
 
    RuntimeType():type_id(typeid(void*)) {}

    template<typename _T_>
    RuntimeType(const std::type_index&argID,_T_&&argData):type_id(argID),data(std::forward<_T_>(argData)) {}
    template<typename _T_>
    RuntimeType(const std::type_info&argID,_T_&&argData):type_id(argID),data(std::forward<_T_>(argData)) {}

};

typedef RuntimeType(*TypeCastFunction)(const SharedVoidType&);

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


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

using name_type=QByteArray;
inline name_type operator""_name(const char *arg,std::size_t argN) { return name_type{ arg,static_cast<int>(argN) }; }

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
        :SharedVoidType(std::shared_ptr<void>(std::move(arg))) {}

    template<typename _T_>
    SharedVoidType(std::shared_ptr<const _T_>arg)
        :SharedVoidType(std::shared_ptr<const void>(std::move(arg))) {}

    void * data();
    const void * data()const;

    template<typename _T_>
    _T_*value() { return reinterpret_cast<_T_*>(data()); }

    template<typename _T_>
    const _T_*value()const { return reinterpret_cast<const _T_*>(data()); }

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

    operator SharedVoidType&() { return data; }
    operator const SharedVoidType&()const { return data; }

    RuntimeType():type_id(typeid(void*)) {}

    template<typename _T_>
    RuntimeType(const std::type_index&argID,_T_&&argData):type_id(argID),data(std::forward<_T_>(argData)) {}
    template<typename _T_>
    RuntimeType(const std::type_info&argID,_T_&&argData):type_id(argID),data(std::forward<_T_>(argData)) {}

};

typedef RuntimeType(*TypeCastFunction)(const SharedVoidType&);

template<typename _T_>
class __RuntimeTypeConceptBase {
public:
    using type=logical_type<_T_>;
    static name_type readable_class_name() { return ""; }
    static std::type_index logical_type_index() { return typeid(type); }
    static constexpr bool is_static_type() { return false==std::has_virtual_destructor<type>::value; }
private:
    static_assert(std::is_reference<type>::value==false,"it should not be a ref type");
};

template<typename _T_>
class RuntimeTypeConcept;

template<>
class RuntimeTypeConcept<std::int32_t> final :public __RuntimeTypeConceptBase<std::int32_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::int32_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::int64_t> final :public __RuntimeTypeConceptBase<std::int64_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::int64_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::int16_t> final :public __RuntimeTypeConceptBase<std::int16_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::int16_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::int8_t> final :public __RuntimeTypeConceptBase<std::int8_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::int8_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::uint32_t> final :public __RuntimeTypeConceptBase<std::uint32_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::uint32_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::uint64_t> final :public __RuntimeTypeConceptBase<std::uint64_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::uint64_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::uint16_t> final :public __RuntimeTypeConceptBase<std::uint16_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::uint16_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::uint8_t> final :public __RuntimeTypeConceptBase<std::uint8_t> {
public:
    static name_type readable_class_name() { const static auto ans="std::int8_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<float> final :public __RuntimeTypeConceptBase<float> {
public:
    static name_type readable_class_name() { const static auto ans="float"_name; return ans; }
};

template<>
class RuntimeTypeConcept<double> final :public __RuntimeTypeConceptBase<double> {
public:
    static name_type readable_class_name() { const static auto ans="double"_name; return ans; }
};

template<>
class RuntimeTypeConcept<long double> final :public __RuntimeTypeConceptBase<long double> {
public:
    static name_type readable_class_name() { const static auto ans="long double"_name; return ans; }
};

template<>
class RuntimeTypeConcept<char> final :public __RuntimeTypeConceptBase<char> {
public:
    static name_type readable_class_name() { const static auto ans="char"_name; return ans; }
};

template<>
class RuntimeTypeConcept<char16_t> final :public __RuntimeTypeConceptBase<char16_t> {
public:
    static name_type readable_class_name() { const static auto ans="char16_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<char32_t> final :public __RuntimeTypeConceptBase<char32_t> {
public:
    static name_type readable_class_name() { const static auto ans="char32_t"_name; return ans; }
};

template<>
class RuntimeTypeConcept<bool> final :public __RuntimeTypeConceptBase<bool> {
public:
    static name_type readable_class_name() { const static auto ans="bool"_name; return ans; }
};

template<>
class RuntimeTypeConcept<std::string> final :public __RuntimeTypeConceptBase<std::string> {
public:
    static name_type readable_class_name() { const static auto ans="std::string"_name; return ans; }
};

RUNTIME_TYPE_IMPORT TypeCastFunction get_static_class_cast_function(const std::type_index&,const std::type_index&);
RUNTIME_TYPE_IMPORT void set_static_class_cast_function(const std::type_index&,const std::type_index&,TypeCastFunction);

class RuntimeClasInfo {
public:
    virtual ~RuntimeClasInfo()=default;
    virtual name_type readable_class_name() const=0;
    virtual std::type_index logical_type_index()const=0;
    virtual bool is_static_type() const=0;
    virtual TypeCastFunction get_class_cast_function(const std::type_index&argFrom,const std::type_index&argTo) {
        return runtime::type::get_static_class_cast_function(argFrom,argTo);
    }
};

RUNTIME_TYPE_IMPORT void set_runtime_class_info(const std::type_index&,const RuntimeClasInfo*);
RUNTIME_TYPE_IMPORT const RuntimeClasInfo * get_runtime_class_info(const std::type_index&);

}
}

#endif


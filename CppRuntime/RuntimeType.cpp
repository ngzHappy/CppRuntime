#include <cassert>

#include <map>
#include <exception>
#include <stdexcept>
#include <shared_mutex>
#include <unordered_map>
#include <QtCore/qdebug.h>
#include "RuntimeType.hpp"

namespace runtime {
namespace type {

namespace __private {
namespace {

template<typename From_,typename To_>
inline std::pair<std::type_index,std::type_index> make_pair_from_to() {
    return{
        std::type_index(typeid(typename RuntimeTypeConcept<logical_type<From_>/**/>::type)),
        std::type_index(typeid(typename RuntimeTypeConcept<logical_type<To_>/**/>::type))
    };
}

template<typename _T_>
void do_not_delete(_T_*) {}

class StaticCastMap;
void add_std_string_cast(StaticCastMap*);

class StaticCastMap {
    friend void add_std_string_cast(StaticCastMap*);
    std::shared_ptr<std::shared_timed_mutex> mutex_read_write_{
        new std::shared_timed_mutex,[](auto *arg) {
        /*do not delete because it just use for static*/
        do_not_delete(arg);
    } };
    std::map<
        std::pair<std::type_index,std::type_index>,
        runtime::type::TypeCastFunction
    >cast_functions_;
public:
    void add(
        const std::type_index&from_,
        const std::type_index&to_,
        runtime::type::TypeCastFunction function_) {
        const auto & _lock_data_=mutex_read_write_;
        std::unique_lock<std::shared_timed_mutex> lock_(*_lock_data_);
        cast_functions_[std::make_pair(from_,to_)]=std::move(function_);
    }

    void remove(
        const std::type_index&from_,
        const std::type_index&to_) {
        const auto & _lock_data_=mutex_read_write_;
        std::unique_lock<std::shared_timed_mutex> lock_(*_lock_data_);
        cast_functions_.erase(std::make_pair(from_,to_));
    }

    runtime::type::TypeCastFunction find(
        const std::type_index&from_,
        const std::type_index&to_) const {
        const auto & _lock_data_=mutex_read_write_;
        std::shared_lock<std::shared_timed_mutex> lock_(*_lock_data_);
        auto varPos=cast_functions_.find(std::make_pair(from_,to_));
        if (varPos==cast_functions_.end()) { return nullptr; }
        return varPos->second;
    }

    StaticCastMap() {

        {/*init cast functions*/
         /* from:bool to:std::int32_t */
            cast_functions_[make_pair_from_to<bool,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:bool to:std::int64_t */
            cast_functions_[make_pair_from_to<bool,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:bool to:std::int16_t */
            cast_functions_[make_pair_from_to<bool,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:bool to:std::int8_t */
            cast_functions_[make_pair_from_to<bool,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:bool to:std::uint32_t */
            cast_functions_[make_pair_from_to<bool,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:bool to:std::uint64_t */
            cast_functions_[make_pair_from_to<bool,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:bool to:std::uint16_t */
            cast_functions_[make_pair_from_to<bool,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:bool to:std::uint8_t */
            cast_functions_[make_pair_from_to<bool,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:bool to:char */
            cast_functions_[make_pair_from_to<bool,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:bool to:char16_t */
            cast_functions_[make_pair_from_to<bool,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:bool to:char32_t */
            cast_functions_[make_pair_from_to<bool,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:bool to:float */
            cast_functions_[make_pair_from_to<bool,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:bool to:double */
            cast_functions_[make_pair_from_to<bool,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:bool to:long double */
            cast_functions_[make_pair_from_to<bool,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::int32_t to:bool */
            cast_functions_[make_pair_from_to<std::int32_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::int32_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::int32_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::int32_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::int32_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::int32_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::int32_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::int32_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::int32_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::int32_t to:char */
            cast_functions_[make_pair_from_to<std::int32_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::int32_t to:char16_t */
            cast_functions_[make_pair_from_to<std::int32_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::int32_t to:char32_t */
            cast_functions_[make_pair_from_to<std::int32_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::int32_t to:float */
            cast_functions_[make_pair_from_to<std::int32_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::int32_t to:double */
            cast_functions_[make_pair_from_to<std::int32_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::int32_t to:long double */
            cast_functions_[make_pair_from_to<std::int32_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::int64_t to:bool */
            cast_functions_[make_pair_from_to<std::int64_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::int64_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::int64_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::int64_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::int64_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::int64_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::int64_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::int64_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::int64_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::int64_t to:char */
            cast_functions_[make_pair_from_to<std::int64_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::int64_t to:char16_t */
            cast_functions_[make_pair_from_to<std::int64_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::int64_t to:char32_t */
            cast_functions_[make_pair_from_to<std::int64_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::int64_t to:float */
            cast_functions_[make_pair_from_to<std::int64_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::int64_t to:double */
            cast_functions_[make_pair_from_to<std::int64_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::int64_t to:long double */
            cast_functions_[make_pair_from_to<std::int64_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::int16_t to:bool */
            cast_functions_[make_pair_from_to<std::int16_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::int16_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::int16_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::int16_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::int16_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::int16_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::int16_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::int16_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::int16_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::int16_t to:char */
            cast_functions_[make_pair_from_to<std::int16_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::int16_t to:char16_t */
            cast_functions_[make_pair_from_to<std::int16_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::int16_t to:char32_t */
            cast_functions_[make_pair_from_to<std::int16_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::int16_t to:float */
            cast_functions_[make_pair_from_to<std::int16_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::int16_t to:double */
            cast_functions_[make_pair_from_to<std::int16_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::int16_t to:long double */
            cast_functions_[make_pair_from_to<std::int16_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::int8_t to:bool */
            cast_functions_[make_pair_from_to<std::int8_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::int8_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::int8_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::int8_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::int8_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::int8_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::int8_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::int8_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::int8_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::int8_t to:char */
            cast_functions_[make_pair_from_to<std::int8_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::int8_t to:char16_t */
            cast_functions_[make_pair_from_to<std::int8_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::int8_t to:char32_t */
            cast_functions_[make_pair_from_to<std::int8_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::int8_t to:float */
            cast_functions_[make_pair_from_to<std::int8_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::int8_t to:double */
            cast_functions_[make_pair_from_to<std::int8_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::int8_t to:long double */
            cast_functions_[make_pair_from_to<std::int8_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::uint32_t to:bool */
            cast_functions_[make_pair_from_to<std::uint32_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::uint32_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::uint32_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::uint32_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::uint32_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::uint32_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::uint32_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::uint32_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::uint32_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::uint32_t to:char */
            cast_functions_[make_pair_from_to<std::uint32_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::uint32_t to:char16_t */
            cast_functions_[make_pair_from_to<std::uint32_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::uint32_t to:char32_t */
            cast_functions_[make_pair_from_to<std::uint32_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::uint32_t to:float */
            cast_functions_[make_pair_from_to<std::uint32_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::uint32_t to:double */
            cast_functions_[make_pair_from_to<std::uint32_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::uint32_t to:long double */
            cast_functions_[make_pair_from_to<std::uint32_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::uint64_t to:bool */
            cast_functions_[make_pair_from_to<std::uint64_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::uint64_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::uint64_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::uint64_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::uint64_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::uint64_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::uint64_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::uint64_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::uint64_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::uint64_t to:char */
            cast_functions_[make_pair_from_to<std::uint64_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::uint64_t to:char16_t */
            cast_functions_[make_pair_from_to<std::uint64_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::uint64_t to:char32_t */
            cast_functions_[make_pair_from_to<std::uint64_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::uint64_t to:float */
            cast_functions_[make_pair_from_to<std::uint64_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::uint64_t to:double */
            cast_functions_[make_pair_from_to<std::uint64_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::uint64_t to:long double */
            cast_functions_[make_pair_from_to<std::uint64_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::uint16_t to:bool */
            cast_functions_[make_pair_from_to<std::uint16_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::uint16_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::uint16_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::uint16_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::uint16_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::uint16_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::uint16_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::uint16_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<std::uint16_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:std::uint16_t to:char */
            cast_functions_[make_pair_from_to<std::uint16_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::uint16_t to:char16_t */
            cast_functions_[make_pair_from_to<std::uint16_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::uint16_t to:char32_t */
            cast_functions_[make_pair_from_to<std::uint16_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::uint16_t to:float */
            cast_functions_[make_pair_from_to<std::uint16_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::uint16_t to:double */
            cast_functions_[make_pair_from_to<std::uint16_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::uint16_t to:long double */
            cast_functions_[make_pair_from_to<std::uint16_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:std::uint8_t to:bool */
            cast_functions_[make_pair_from_to<std::uint8_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:std::uint8_t to:std::int32_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:std::uint8_t to:std::int64_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:std::uint8_t to:std::int16_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:std::uint8_t to:std::int8_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:std::uint8_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:std::uint8_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:std::uint8_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<std::uint8_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:std::uint8_t to:char */
            cast_functions_[make_pair_from_to<std::uint8_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:std::uint8_t to:char16_t */
            cast_functions_[make_pair_from_to<std::uint8_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:std::uint8_t to:char32_t */
            cast_functions_[make_pair_from_to<std::uint8_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:std::uint8_t to:float */
            cast_functions_[make_pair_from_to<std::uint8_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:std::uint8_t to:double */
            cast_functions_[make_pair_from_to<std::uint8_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:std::uint8_t to:long double */
            cast_functions_[make_pair_from_to<std::uint8_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:char to:bool */
            cast_functions_[make_pair_from_to<char,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:char to:std::int32_t */
            cast_functions_[make_pair_from_to<char,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:char to:std::int64_t */
            cast_functions_[make_pair_from_to<char,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:char to:std::int16_t */
            cast_functions_[make_pair_from_to<char,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:char to:std::int8_t */
            cast_functions_[make_pair_from_to<char,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:char to:std::uint32_t */
            cast_functions_[make_pair_from_to<char,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:char to:std::uint64_t */
            cast_functions_[make_pair_from_to<char,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:char to:std::uint16_t */
            cast_functions_[make_pair_from_to<char,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:char to:std::uint8_t */
            cast_functions_[make_pair_from_to<char,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:char to:char16_t */
            cast_functions_[make_pair_from_to<char,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:char to:char32_t */
            cast_functions_[make_pair_from_to<char,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:char to:float */
            cast_functions_[make_pair_from_to<char,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:char to:double */
            cast_functions_[make_pair_from_to<char,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:char to:long double */
            cast_functions_[make_pair_from_to<char,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:char16_t to:bool */
            cast_functions_[make_pair_from_to<char16_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:char16_t to:std::int32_t */
            cast_functions_[make_pair_from_to<char16_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:char16_t to:std::int64_t */
            cast_functions_[make_pair_from_to<char16_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:char16_t to:std::int16_t */
            cast_functions_[make_pair_from_to<char16_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:char16_t to:std::int8_t */
            cast_functions_[make_pair_from_to<char16_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:char16_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<char16_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:char16_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<char16_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:char16_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<char16_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:char16_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<char16_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:char16_t to:char */
            cast_functions_[make_pair_from_to<char16_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:char16_t to:char32_t */
            cast_functions_[make_pair_from_to<char16_t,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:char16_t to:float */
            cast_functions_[make_pair_from_to<char16_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:char16_t to:double */
            cast_functions_[make_pair_from_to<char16_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:char16_t to:long double */
            cast_functions_[make_pair_from_to<char16_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:char32_t to:bool */
            cast_functions_[make_pair_from_to<char32_t,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:char32_t to:std::int32_t */
            cast_functions_[make_pair_from_to<char32_t,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:char32_t to:std::int64_t */
            cast_functions_[make_pair_from_to<char32_t,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:char32_t to:std::int16_t */
            cast_functions_[make_pair_from_to<char32_t,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:char32_t to:std::int8_t */
            cast_functions_[make_pair_from_to<char32_t,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:char32_t to:std::uint32_t */
            cast_functions_[make_pair_from_to<char32_t,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:char32_t to:std::uint64_t */
            cast_functions_[make_pair_from_to<char32_t,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:char32_t to:std::uint16_t */
            cast_functions_[make_pair_from_to<char32_t,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:char32_t to:std::uint8_t */
            cast_functions_[make_pair_from_to<char32_t,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:char32_t to:char */
            cast_functions_[make_pair_from_to<char32_t,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:char32_t to:char16_t */
            cast_functions_[make_pair_from_to<char32_t,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:char32_t to:float */
            cast_functions_[make_pair_from_to<char32_t,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:char32_t to:double */
            cast_functions_[make_pair_from_to<char32_t,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:char32_t to:long double */
            cast_functions_[make_pair_from_to<char32_t,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:float to:bool */
            cast_functions_[make_pair_from_to<float,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:float to:std::int32_t */
            cast_functions_[make_pair_from_to<float,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:float to:std::int64_t */
            cast_functions_[make_pair_from_to<float,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:float to:std::int16_t */
            cast_functions_[make_pair_from_to<float,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:float to:std::int8_t */
            cast_functions_[make_pair_from_to<float,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:float to:std::uint32_t */
            cast_functions_[make_pair_from_to<float,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:float to:std::uint64_t */
            cast_functions_[make_pair_from_to<float,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:float to:std::uint16_t */
            cast_functions_[make_pair_from_to<float,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:float to:std::uint8_t */
            cast_functions_[make_pair_from_to<float,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:float to:char */
            cast_functions_[make_pair_from_to<float,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:float to:char16_t */
            cast_functions_[make_pair_from_to<float,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:float to:char32_t */
            cast_functions_[make_pair_from_to<float,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:float to:double */
            cast_functions_[make_pair_from_to<float,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };

            /* from:float to:long double */
            cast_functions_[make_pair_from_to<float,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:double to:bool */
            cast_functions_[make_pair_from_to<double,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:double to:std::int32_t */
            cast_functions_[make_pair_from_to<double,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:double to:std::int64_t */
            cast_functions_[make_pair_from_to<double,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:double to:std::int16_t */
            cast_functions_[make_pair_from_to<double,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:double to:std::int8_t */
            cast_functions_[make_pair_from_to<double,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:double to:std::uint32_t */
            cast_functions_[make_pair_from_to<double,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:double to:std::uint64_t */
            cast_functions_[make_pair_from_to<double,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:double to:std::uint16_t */
            cast_functions_[make_pair_from_to<double,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:double to:std::uint8_t */
            cast_functions_[make_pair_from_to<double,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:double to:char */
            cast_functions_[make_pair_from_to<double,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:double to:char16_t */
            cast_functions_[make_pair_from_to<double,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:double to:char32_t */
            cast_functions_[make_pair_from_to<double,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:double to:float */
            cast_functions_[make_pair_from_to<double,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:double to:long double */
            cast_functions_[make_pair_from_to<double,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
                auto * varTo=new auto(static_cast<long double>(varFrom));
                return{typeid(long double),std::shared_ptr<long double>(varTo)};
            };

            /* from:long double to:bool */
            cast_functions_[make_pair_from_to<long double,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<bool>(varFrom));
                return{typeid(bool),std::shared_ptr<bool>(varTo)};
            };

            /* from:long double to:std::int32_t */
            cast_functions_[make_pair_from_to<long double,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
                return{typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo)};
            };

            /* from:long double to:std::int64_t */
            cast_functions_[make_pair_from_to<long double,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
                return{typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo)};
            };

            /* from:long double to:std::int16_t */
            cast_functions_[make_pair_from_to<long double,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
                return{typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo)};
            };

            /* from:long double to:std::int8_t */
            cast_functions_[make_pair_from_to<long double,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
                return{typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo)};
            };

            /* from:long double to:std::uint32_t */
            cast_functions_[make_pair_from_to<long double,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
                return{typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo)};
            };

            /* from:long double to:std::uint64_t */
            cast_functions_[make_pair_from_to<long double,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
                return{typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo)};
            };

            /* from:long double to:std::uint16_t */
            cast_functions_[make_pair_from_to<long double,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
                return{typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo)};
            };

            /* from:long double to:std::uint8_t */
            cast_functions_[make_pair_from_to<long double,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
                return{typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo)};
            };

            /* from:long double to:char */
            cast_functions_[make_pair_from_to<long double,char>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<char>(varFrom));
                return{typeid(char),std::shared_ptr<char>(varTo)};
            };

            /* from:long double to:char16_t */
            cast_functions_[make_pair_from_to<long double,char16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<char16_t>(varFrom));
                return{typeid(char16_t),std::shared_ptr<char16_t>(varTo)};
            };

            /* from:long double to:char32_t */
            cast_functions_[make_pair_from_to<long double,char32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<char32_t>(varFrom));
                return{typeid(char32_t),std::shared_ptr<char32_t>(varTo)};
            };

            /* from:long double to:float */
            cast_functions_[make_pair_from_to<long double,float>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<float>(varFrom));
                return{typeid(float),std::shared_ptr<float>(varTo)};
            };

            /* from:long double to:double */
            cast_functions_[make_pair_from_to<long double,double>()]=[](const SharedVoidType&arg)->RuntimeType {
                const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
                auto * varTo=new auto(static_cast<double>(varFrom));
                return{typeid(double),std::shared_ptr<double>(varTo)};
            };
        }
        add_std_string_cast(this);

    }

};

void add_std_string_cast(StaticCastMap *arg) {

    auto & cast_functions_=arg->cast_functions_;

    cast_functions_[make_pair_from_to<std::string,bool>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        bool varTo=false;
        do {
            if (varFrom.empty()) { break; }
            if (varFrom.size()>=4) {
                varTo=((varFrom[0]=='t')||(varFrom[0]=='T'))&&
                    ((varFrom[1]=='r')||(varFrom[1]=='R'))&&
                    ((varFrom[2]=='u')||(varFrom[2]=='U'))&&
                    ((varFrom[3]=='e')||(varFrom[3]=='E'));
            }
            if (varTo) { break; }
            varTo=true;
            if (varFrom.size()>=5) {
                varTo=!(((varFrom[0]=='f')||(varFrom[0]=='F'))&&
                    ((varFrom[1]=='a')||(varFrom[1]=='A'))&&
                    ((varFrom[2]=='l')||(varFrom[2]=='L'))&&
                    ((varFrom[3]=='s')||(varFrom[3]=='S'))&&
                    ((varFrom[4]=='e')||(varFrom[4]=='E')));
            }
        } while (false);
        return{ typeid(bool),std::shared_ptr<bool>(new bool(varTo)) };
    };

    cast_functions_[make_pair_from_to<bool,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
        if (varFrom) {
            return{ typeid(std::string), std::shared_ptr<std::string>(new std::string("true"))};
        }
        else {
            return{ typeid(std::string), std::shared_ptr<std::string>(new std::string("false"))};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::int8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            return{ typeid(std::int8_t), std::make_shared<std::int8_t>(std::stoi(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::uint8_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            return{ typeid(std::uint8_t), std::make_shared<std::uint8_t>(std::stoi(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::uint16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            static_assert(sizeof(int)>sizeof(std::uint16_t),"???");
            return{ typeid(std::uint16_t), std::make_shared<std::uint16_t>(std::stoi(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::int16_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            static_assert(sizeof(int)>sizeof(std::int16_t),"???");
            return{ typeid(std::int16_t), std::make_shared<std::int16_t>(std::stoi(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::int32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            static_assert(sizeof(long)>=sizeof(std::int32_t),"???");
            return{ typeid(std::int32_t), std::make_shared<std::int32_t>(std::stol(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::uint32_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            static_assert(sizeof(unsigned long)>=sizeof(std::uint32_t),"???");
            return{ typeid(std::uint32_t), std::make_shared<std::uint32_t>(std::stoul(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::int64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            static_assert(sizeof(long long)>=sizeof(std::int64_t),"???");
            return{ typeid(std::int64_t), std::make_shared<std::int64_t>(std::stoll(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,std::uint64_t>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            static_assert(sizeof(unsigned long long)>=sizeof(std::uint64_t),"???");
            return{ typeid(std::uint64_t), std::make_shared<std::uint64_t>(std::stoull(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,float>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            return{ typeid(float), std::make_shared<float>(std::stof(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,double>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            return{ typeid(double), std::make_shared<double>(std::stod(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::string,long double>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));
        try {
            return{ typeid(long double), std::make_shared<long double>(std::stold(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::int8_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::uint8_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::uint16_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::int16_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::int32_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::uint32_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::int64_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<std::uint64_t,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<float,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<double,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

    cast_functions_[make_pair_from_to<long double,std::string>()]=[](const SharedVoidType&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
        try {
            return{ typeid(std::string), std::make_shared<std::string>(std::to_string(varFrom))};
        }
        catch(std::exception&e){
            qDebug().noquote()<<e.what();
            return{};
        }
        catch (...) {
            return{};
        }
    };

}

StaticCastMap & get_static_cast_map() {
    /*the data do not need delete ,it is global static*/
    static std::unique_ptr<StaticCastMap,void(*)(StaticCastMap*)>
        static_cast_map_{ new StaticCastMap,&do_not_delete<StaticCastMap>};
    return *static_cast_map_;
}

}
}/*~__private*/

TypeCastFunction
get_static_class_cast_function(
    const std::type_index& argFrom,
    const std::type_index& argTo) {
    return __private::get_static_cast_map().find(argFrom,argTo);
}

void
set_static_class_cast_function(
    const std::type_index&argFrom,
    const std::type_index&argTo,
    TypeCastFunction argFunction) {
    return __private::get_static_cast_map().add(argFrom,argTo,std::move(argFunction));
}

}/*~type*/
}/*runtime*/


namespace runtime {
namespace type {

SharedVoidType::SharedVoidType() {
    flags.set(IS_PLAINDATA);
    data_.plain_data=nullptr;
}

SharedVoidType::SharedVoidType(const SharedVoidType&arg) {
    extern_data_=arg.extern_data_;
    if (arg.is_plain_data()) {
        flags=arg.flags;
        data_.plain_data=arg.data_.plain_data;
    }
    else {
        flags=arg.flags;
        new (&data_.shared_data)std::shared_ptr<void>(arg.data_.shared_data);
    }
}

SharedVoidType::SharedVoidType(SharedVoidType&&arg) {
    extern_data_=arg.extern_data_;
    if (arg.is_plain_data()) {
        flags=arg.flags;
        data_.plain_data=arg.data_.plain_data;
    }
    else {
        flags=arg.flags;
        new (&data_.shared_data)std::shared_ptr<void>(std::move(arg.data_.shared_data));
    }
}

SharedVoidType&SharedVoidType::operator=(const SharedVoidType&arg) {
    if (this==&arg) { return *this; }
    extern_data_=arg.extern_data_;
    if (arg.is_plain_data()) {
        if (is_plain_data()) {
            flags=arg.flags;
            data_.plain_data=arg.data_.plain_data;
        }
        else {
            flags=arg.flags;
            data_.shared_data.~shared_ptr();
            data_.plain_data=arg.data_.plain_data;
        }
    }
    else {
        if (is_plain_data()) {
            flags=arg.flags;
            new (&data_.shared_data)std::shared_ptr<void>(arg.data_.shared_data);
        }
        else {
            flags=arg.flags;
            data_.shared_data=arg.data_.shared_data;
        }
    }
    return *this;
}

SharedVoidType&SharedVoidType::operator=(SharedVoidType&&arg) {
    if (this==&arg) { return *this; }
    extern_data_=arg.extern_data_;
    if (arg.is_plain_data()) {
        if (is_plain_data()) {
            flags=arg.flags;
            data_.plain_data=arg.data_.plain_data;
        }
        else {
            flags=arg.flags;
            data_.shared_data.~shared_ptr();
            data_.plain_data=arg.data_.plain_data;
        }
    }
    else {
        if (is_plain_data()) {
            flags=arg.flags;
            new (&data_.shared_data)std::shared_ptr<void>(std::move(arg.data_.shared_data));
        }
        else {
            flags=arg.flags;
            data_.shared_data=std::move(arg.data_.shared_data);
        }
    }
    return *this;
}

SharedVoidType::SharedVoidType(void *arg) {
    flags.set(IS_PLAINDATA);
    data_.plain_data=arg;
}

SharedVoidType::SharedVoidType(const void * arg) {
    flags.set(IS_PLAINDATA);
    flags.set(IS_CONST);
    data_.plain_data=const_cast<void*>(arg);
}

QObject * SharedVoidType::qobject() const{ 
    if (flags.test(IS_EXTERNDATA_QOBJECT)) { 
        return reinterpret_cast<QObject*>(extern_data_); 
    }
    return nullptr;
}

void SharedVoidType::set_extern_data(const QObject *arg) { 
    extern_data_=const_cast<QObject *>(arg);
    flags.set(IS_EXTERNDATA_QOBJECT);
    /*clear other extern data flags*/
}

SharedVoidType::SharedVoidType(std::shared_ptr<void>arg) {
    new(&data_.shared_data) std::shared_ptr<void>(std::move(arg));
}
SharedVoidType::SharedVoidType(std::shared_ptr<const void>arg) {
    flags.set(IS_CONST);
    new(&data_.shared_data) std::shared_ptr<void>(std::move(std::const_pointer_cast<void>(arg)));
}

SharedVoidType::~SharedVoidType() {
    if (is_plain_data()) { return; }
    data_.shared_data.~shared_ptr();
}

void * SharedVoidType::data() {
    if (is_plain_data()) { return data_.plain_data; }
    return data_.shared_data.get();
}

const void * SharedVoidType::data()const {
    if (is_plain_data()) { return data_.plain_data; }
    return data_.shared_data.get();
}

}/*type*/
}/*runtime*/

namespace runtime {/*runtime*/
namespace type {/*type*/

namespace __private {
namespace {

using info_map_type_=std::unordered_map<std::type_index,const RuntimeClasInfo*>;

template<typename _T_>
inline void _add_info_static_t(info_map_type_ & arg) {

    class type_info_ final:public runtime::type::RuntimeClasInfo {
    public:
        virtual name_type readable_class_name() const override{
            return runtime::type::RuntimeTypeConcept<runtime::type::logical_type<_T_>>::readable_class_name();
        }
        virtual std::type_index logical_type_index()const override{
            return runtime::type::RuntimeTypeConcept<runtime::type::logical_type<_T_>>::logical_type_index();
        }
        virtual bool is_static_type() const override{
            return runtime::type::RuntimeTypeConcept<runtime::type::logical_type<_T_>>::is_static_type();
        }
    };

    arg[typeid(typename runtime::type::RuntimeTypeConcept<runtime::type::logical_type<_T_>>::type)]
        =new type_info_;

}

class StaticRuntimClassInfo {
    std::shared_ptr<std::shared_timed_mutex> read_write_lock_{
        new std::shared_timed_mutex,
        [](auto *arg) {do_not_delete(arg); }
    };

    info_map_type_ data_;
public:

    const RuntimeClasInfo* get_info(const std::type_index&arg) {
        auto & lock_data_=read_write_lock_;
        std::shared_lock<std::shared_timed_mutex> lock_{*lock_data_};
        auto pos_=data_.find(arg);
        if(pos_!=data_.end()){
            return pos_->second;
        }
        return nullptr;
    }

    void set_info(
        const std::type_index&arg,
        const RuntimeClasInfo*argInfo
    ) {
        if (argInfo==nullptr) { return; }
        auto & lock_data_=read_write_lock_;
        std::unique_lock<std::shared_timed_mutex> lock_{*lock_data_};
#if !defined(NDEBUG)/*if this is in debug*/
        {/*a class info just can be add once*/
            auto varPos=data_.find(arg);
            assert(varPos==data_.end());
        }
#endif
        data_[arg]=argInfo;
    }

    StaticRuntimClassInfo() {
        _add_info_static_t<bool>(data_);
        _add_info_static_t<char>(data_);
        _add_info_static_t<char16_t>(data_);
        _add_info_static_t<char32_t>(data_);
        _add_info_static_t<std::int8_t>(data_);
        _add_info_static_t<std::uint8_t>(data_);
        _add_info_static_t<std::int16_t>(data_);
        _add_info_static_t<std::uint16_t>(data_);
        _add_info_static_t<std::int32_t>(data_);
        _add_info_static_t<std::uint32_t>(data_);
        _add_info_static_t<std::int64_t>(data_);
        _add_info_static_t<std::uint64_t>(data_);
        _add_info_static_t<float>(data_);
        _add_info_static_t<double>(data_);
        _add_info_static_t<long double>(data_);
        _add_info_static_t<std::string>(data_);
    }

};

StaticRuntimClassInfo & get_runtime_class_infos() {
    /*do not need delete the class*/
    static std::unique_ptr<StaticRuntimClassInfo,void(*)(StaticRuntimClassInfo*)>
        ans{
        new StaticRuntimClassInfo,
        &do_not_delete<StaticRuntimClassInfo>
    };
    return *ans;
}

}
}

void set_runtime_class_info(
    const std::type_index&arg,
    const RuntimeClasInfo*argInfo) {
    return __private::get_runtime_class_infos().set_info(arg,argInfo);
}

const RuntimeClasInfo * get_runtime_class_info(const std::type_index&arg) {
    return __private::get_runtime_class_infos().get_info(arg);
}


}/*type*/
}/*runtime*/


namespace runtime {
namespace type {

namespace __private {
namespace {

class StaticToLogicalTypeIndex {
    using type_mutex=std::shared_timed_mutex;
    std::unordered_map<std::type_index,ToLogicalTypeIndex>data_;
    std::shared_ptr<type_mutex> lock_mutex_{
        new type_mutex,
        [](auto *arg) {do_not_delete(arg); }
    };
public:
    StaticToLogicalTypeIndex() {}

    void add(const std::type_index&argKey,ToLogicalTypeIndex argValue) {
        if (argValue) {
            auto &var=lock_mutex_;
            std::unique_lock<type_mutex> lock_{ *var };
            data_[argKey]=argValue;
        }
    }

    ToLogicalTypeIndex find_item(const std::type_index&argKey) {
        auto &var=lock_mutex_;
        std::shared_lock<type_mutex> lock_{ *var };
        auto varValue=data_.find(argKey);
        if (varValue==data_.end()) { return nullptr; }
        return varValue->second;
    }

};

StaticToLogicalTypeIndex & getData() {
    static std::unique_ptr<StaticToLogicalTypeIndex,void(*)(StaticToLogicalTypeIndex*)>
        ans{
        new StaticToLogicalTypeIndex,
        &do_not_delete<StaticToLogicalTypeIndex>
    };
    return *ans;
}

}/*namespace*/
}/*__private*/

ToLogicalTypeIndex get_to_logical_type_index(const std::type_index&arg) {
    return __private::getData().find_item(arg);
}

void set_to_logical_type_index(const std::type_index&argKey,ToLogicalTypeIndex argValue) {
    __private::getData().add(argKey,argValue);
}

}/*type*/
}/*runtime*/






﻿#include "RuntimeType.hpp"

#include <shared_mutex>
#include <map>


namespace runtime {
namespace type {

namespace __private {
namespace {

template<typename From_,typename To_>
inline std::pair<std::type_index,std::type_index> make_pair_from_to() {
    return{
        std::type_index(typeid(typename RuntimType<logical_type<From_>>::type)),
        std::type_index(typeid(typename RuntimType<logical_type<To_>>::type))
    };
}

class StaticCastMap;
void add_std_string_cast(StaticCastMap*);

class StaticCastMap {
    friend void add_std_string_cast(StaticCastMap*);
    std::shared_ptr<std::shared_timed_mutex> mutex_read_write_{
        new std::shared_timed_mutex,[](auto *) {
        /*do not delete because it just use for static*/} };
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
        /*init cast functions*/
        /* from:bool to:std::int32_t */
        cast_functions_[make_pair_from_to<bool,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:bool to:std::int64_t */
        cast_functions_[make_pair_from_to<bool,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:bool to:std::int16_t */
        cast_functions_[make_pair_from_to<bool,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:bool to:std::int8_t */
        cast_functions_[make_pair_from_to<bool,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:bool to:std::uint32_t */
        cast_functions_[make_pair_from_to<bool,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:bool to:std::uint64_t */
        cast_functions_[make_pair_from_to<bool,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:bool to:std::uint16_t */
        cast_functions_[make_pair_from_to<bool,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:bool to:std::uint8_t */
        cast_functions_[make_pair_from_to<bool,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:bool to:char */
        cast_functions_[make_pair_from_to<bool,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:bool to:char16_t */
        cast_functions_[make_pair_from_to<bool,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:bool to:char32_t */
        cast_functions_[make_pair_from_to<bool,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:bool to:float */
        cast_functions_[make_pair_from_to<bool,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:bool to:double */
        cast_functions_[make_pair_from_to<bool,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:bool to:long double */
        cast_functions_[make_pair_from_to<bool,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::int32_t to:bool */
        cast_functions_[make_pair_from_to<std::int32_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::int32_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::int32_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::int32_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::int32_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::int32_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::int32_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::int32_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::int32_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::int32_t to:char */
        cast_functions_[make_pair_from_to<std::int32_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::int32_t to:char16_t */
        cast_functions_[make_pair_from_to<std::int32_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::int32_t to:char32_t */
        cast_functions_[make_pair_from_to<std::int32_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::int32_t to:float */
        cast_functions_[make_pair_from_to<std::int32_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::int32_t to:double */
        cast_functions_[make_pair_from_to<std::int32_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::int32_t to:long double */
        cast_functions_[make_pair_from_to<std::int32_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::int64_t to:bool */
        cast_functions_[make_pair_from_to<std::int64_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::int64_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::int64_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::int64_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::int64_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::int64_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::int64_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::int64_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::int64_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::int64_t to:char */
        cast_functions_[make_pair_from_to<std::int64_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::int64_t to:char16_t */
        cast_functions_[make_pair_from_to<std::int64_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::int64_t to:char32_t */
        cast_functions_[make_pair_from_to<std::int64_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::int64_t to:float */
        cast_functions_[make_pair_from_to<std::int64_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::int64_t to:double */
        cast_functions_[make_pair_from_to<std::int64_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::int64_t to:long double */
        cast_functions_[make_pair_from_to<std::int64_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::int16_t to:bool */
        cast_functions_[make_pair_from_to<std::int16_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::int16_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::int16_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::int16_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::int16_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::int16_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::int16_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::int16_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::int16_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::int16_t to:char */
        cast_functions_[make_pair_from_to<std::int16_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::int16_t to:char16_t */
        cast_functions_[make_pair_from_to<std::int16_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::int16_t to:char32_t */
        cast_functions_[make_pair_from_to<std::int16_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::int16_t to:float */
        cast_functions_[make_pair_from_to<std::int16_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::int16_t to:double */
        cast_functions_[make_pair_from_to<std::int16_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::int16_t to:long double */
        cast_functions_[make_pair_from_to<std::int16_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::int8_t to:bool */
        cast_functions_[make_pair_from_to<std::int8_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::int8_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::int8_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::int8_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::int8_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::int8_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::int8_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::int8_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::int8_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::int8_t to:char */
        cast_functions_[make_pair_from_to<std::int8_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::int8_t to:char16_t */
        cast_functions_[make_pair_from_to<std::int8_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::int8_t to:char32_t */
        cast_functions_[make_pair_from_to<std::int8_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::int8_t to:float */
        cast_functions_[make_pair_from_to<std::int8_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::int8_t to:double */
        cast_functions_[make_pair_from_to<std::int8_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::int8_t to:long double */
        cast_functions_[make_pair_from_to<std::int8_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::int8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::uint32_t to:bool */
        cast_functions_[make_pair_from_to<std::uint32_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::uint32_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::uint32_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::uint32_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::uint32_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::uint32_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::uint32_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::uint32_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::uint32_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::uint32_t to:char */
        cast_functions_[make_pair_from_to<std::uint32_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::uint32_t to:char16_t */
        cast_functions_[make_pair_from_to<std::uint32_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::uint32_t to:char32_t */
        cast_functions_[make_pair_from_to<std::uint32_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::uint32_t to:float */
        cast_functions_[make_pair_from_to<std::uint32_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::uint32_t to:double */
        cast_functions_[make_pair_from_to<std::uint32_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::uint32_t to:long double */
        cast_functions_[make_pair_from_to<std::uint32_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::uint64_t to:bool */
        cast_functions_[make_pair_from_to<std::uint64_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::uint64_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::uint64_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::uint64_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::uint64_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::uint64_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::uint64_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::uint64_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::uint64_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::uint64_t to:char */
        cast_functions_[make_pair_from_to<std::uint64_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::uint64_t to:char16_t */
        cast_functions_[make_pair_from_to<std::uint64_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::uint64_t to:char32_t */
        cast_functions_[make_pair_from_to<std::uint64_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::uint64_t to:float */
        cast_functions_[make_pair_from_to<std::uint64_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::uint64_t to:double */
        cast_functions_[make_pair_from_to<std::uint64_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::uint64_t to:long double */
        cast_functions_[make_pair_from_to<std::uint64_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint64_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::uint16_t to:bool */
        cast_functions_[make_pair_from_to<std::uint16_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::uint16_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::uint16_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::uint16_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::uint16_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::uint16_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::uint16_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::uint16_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<std::uint16_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:std::uint16_t to:char */
        cast_functions_[make_pair_from_to<std::uint16_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::uint16_t to:char16_t */
        cast_functions_[make_pair_from_to<std::uint16_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::uint16_t to:char32_t */
        cast_functions_[make_pair_from_to<std::uint16_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::uint16_t to:float */
        cast_functions_[make_pair_from_to<std::uint16_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::uint16_t to:double */
        cast_functions_[make_pair_from_to<std::uint16_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::uint16_t to:long double */
        cast_functions_[make_pair_from_to<std::uint16_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:std::uint8_t to:bool */
        cast_functions_[make_pair_from_to<std::uint8_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:std::uint8_t to:std::int32_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:std::uint8_t to:std::int64_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:std::uint8_t to:std::int16_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:std::uint8_t to:std::int8_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:std::uint8_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:std::uint8_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:std::uint8_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<std::uint8_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:std::uint8_t to:char */
        cast_functions_[make_pair_from_to<std::uint8_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:std::uint8_t to:char16_t */
        cast_functions_[make_pair_from_to<std::uint8_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:std::uint8_t to:char32_t */
        cast_functions_[make_pair_from_to<std::uint8_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:std::uint8_t to:float */
        cast_functions_[make_pair_from_to<std::uint8_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:std::uint8_t to:double */
        cast_functions_[make_pair_from_to<std::uint8_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:std::uint8_t to:long double */
        cast_functions_[make_pair_from_to<std::uint8_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const std::uint8_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:char to:bool */
        cast_functions_[make_pair_from_to<char,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:char to:std::int32_t */
        cast_functions_[make_pair_from_to<char,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:char to:std::int64_t */
        cast_functions_[make_pair_from_to<char,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:char to:std::int16_t */
        cast_functions_[make_pair_from_to<char,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:char to:std::int8_t */
        cast_functions_[make_pair_from_to<char,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:char to:std::uint32_t */
        cast_functions_[make_pair_from_to<char,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:char to:std::uint64_t */
        cast_functions_[make_pair_from_to<char,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:char to:std::uint16_t */
        cast_functions_[make_pair_from_to<char,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:char to:std::uint8_t */
        cast_functions_[make_pair_from_to<char,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:char to:char16_t */
        cast_functions_[make_pair_from_to<char,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:char to:char32_t */
        cast_functions_[make_pair_from_to<char,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:char to:float */
        cast_functions_[make_pair_from_to<char,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:char to:double */
        cast_functions_[make_pair_from_to<char,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:char to:long double */
        cast_functions_[make_pair_from_to<char,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:char16_t to:bool */
        cast_functions_[make_pair_from_to<char16_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:char16_t to:std::int32_t */
        cast_functions_[make_pair_from_to<char16_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:char16_t to:std::int64_t */
        cast_functions_[make_pair_from_to<char16_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:char16_t to:std::int16_t */
        cast_functions_[make_pair_from_to<char16_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:char16_t to:std::int8_t */
        cast_functions_[make_pair_from_to<char16_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:char16_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<char16_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:char16_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<char16_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:char16_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<char16_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:char16_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<char16_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:char16_t to:char */
        cast_functions_[make_pair_from_to<char16_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:char16_t to:char32_t */
        cast_functions_[make_pair_from_to<char16_t,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:char16_t to:float */
        cast_functions_[make_pair_from_to<char16_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:char16_t to:double */
        cast_functions_[make_pair_from_to<char16_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:char16_t to:long double */
        cast_functions_[make_pair_from_to<char16_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char16_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:char32_t to:bool */
        cast_functions_[make_pair_from_to<char32_t,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:char32_t to:std::int32_t */
        cast_functions_[make_pair_from_to<char32_t,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:char32_t to:std::int64_t */
        cast_functions_[make_pair_from_to<char32_t,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:char32_t to:std::int16_t */
        cast_functions_[make_pair_from_to<char32_t,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:char32_t to:std::int8_t */
        cast_functions_[make_pair_from_to<char32_t,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:char32_t to:std::uint32_t */
        cast_functions_[make_pair_from_to<char32_t,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:char32_t to:std::uint64_t */
        cast_functions_[make_pair_from_to<char32_t,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:char32_t to:std::uint16_t */
        cast_functions_[make_pair_from_to<char32_t,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:char32_t to:std::uint8_t */
        cast_functions_[make_pair_from_to<char32_t,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:char32_t to:char */
        cast_functions_[make_pair_from_to<char32_t,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:char32_t to:char16_t */
        cast_functions_[make_pair_from_to<char32_t,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:char32_t to:float */
        cast_functions_[make_pair_from_to<char32_t,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:char32_t to:double */
        cast_functions_[make_pair_from_to<char32_t,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:char32_t to:long double */
        cast_functions_[make_pair_from_to<char32_t,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const char32_t*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:float to:bool */
        cast_functions_[make_pair_from_to<float,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:float to:std::int32_t */
        cast_functions_[make_pair_from_to<float,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:float to:std::int64_t */
        cast_functions_[make_pair_from_to<float,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:float to:std::int16_t */
        cast_functions_[make_pair_from_to<float,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:float to:std::int8_t */
        cast_functions_[make_pair_from_to<float,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:float to:std::uint32_t */
        cast_functions_[make_pair_from_to<float,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:float to:std::uint64_t */
        cast_functions_[make_pair_from_to<float,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:float to:std::uint16_t */
        cast_functions_[make_pair_from_to<float,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:float to:std::uint8_t */
        cast_functions_[make_pair_from_to<float,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:float to:char */
        cast_functions_[make_pair_from_to<float,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:float to:char16_t */
        cast_functions_[make_pair_from_to<float,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:float to:char32_t */
        cast_functions_[make_pair_from_to<float,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:float to:double */
        cast_functions_[make_pair_from_to<float,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        /* from:float to:long double */
        cast_functions_[make_pair_from_to<float,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const float*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:double to:bool */
        cast_functions_[make_pair_from_to<double,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:double to:std::int32_t */
        cast_functions_[make_pair_from_to<double,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:double to:std::int64_t */
        cast_functions_[make_pair_from_to<double,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:double to:std::int16_t */
        cast_functions_[make_pair_from_to<double,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:double to:std::int8_t */
        cast_functions_[make_pair_from_to<double,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:double to:std::uint32_t */
        cast_functions_[make_pair_from_to<double,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:double to:std::uint64_t */
        cast_functions_[make_pair_from_to<double,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:double to:std::uint16_t */
        cast_functions_[make_pair_from_to<double,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:double to:std::uint8_t */
        cast_functions_[make_pair_from_to<double,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:double to:char */
        cast_functions_[make_pair_from_to<double,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:double to:char16_t */
        cast_functions_[make_pair_from_to<double,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:double to:char32_t */
        cast_functions_[make_pair_from_to<double,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:double to:float */
        cast_functions_[make_pair_from_to<double,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:double to:long double */
        cast_functions_[make_pair_from_to<double,long double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const double*>(arg.get()));
            auto * varTo=new auto(static_cast<long double>(varFrom));
            return{ typeid(long double),std::shared_ptr<long double>(varTo) };
        };

        /* from:long double to:bool */
        cast_functions_[make_pair_from_to<long double,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<bool>(varFrom));
            return{ typeid(bool),std::shared_ptr<bool>(varTo) };
        };

        /* from:long double to:std::int32_t */
        cast_functions_[make_pair_from_to<long double,std::int32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int32_t>(varFrom));
            return{ typeid(std::int32_t),std::shared_ptr<std::int32_t>(varTo) };
        };

        /* from:long double to:std::int64_t */
        cast_functions_[make_pair_from_to<long double,std::int64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int64_t>(varFrom));
            return{ typeid(std::int64_t),std::shared_ptr<std::int64_t>(varTo) };
        };

        /* from:long double to:std::int16_t */
        cast_functions_[make_pair_from_to<long double,std::int16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int16_t>(varFrom));
            return{ typeid(std::int16_t),std::shared_ptr<std::int16_t>(varTo) };
        };

        /* from:long double to:std::int8_t */
        cast_functions_[make_pair_from_to<long double,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::int8_t>(varFrom));
            return{ typeid(std::int8_t),std::shared_ptr<std::int8_t>(varTo) };
        };

        /* from:long double to:std::uint32_t */
        cast_functions_[make_pair_from_to<long double,std::uint32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint32_t>(varFrom));
            return{ typeid(std::uint32_t),std::shared_ptr<std::uint32_t>(varTo) };
        };

        /* from:long double to:std::uint64_t */
        cast_functions_[make_pair_from_to<long double,std::uint64_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint64_t>(varFrom));
            return{ typeid(std::uint64_t),std::shared_ptr<std::uint64_t>(varTo) };
        };

        /* from:long double to:std::uint16_t */
        cast_functions_[make_pair_from_to<long double,std::uint16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint16_t>(varFrom));
            return{ typeid(std::uint16_t),std::shared_ptr<std::uint16_t>(varTo) };
        };

        /* from:long double to:std::uint8_t */
        cast_functions_[make_pair_from_to<long double,std::uint8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<std::uint8_t>(varFrom));
            return{ typeid(std::uint8_t),std::shared_ptr<std::uint8_t>(varTo) };
        };

        /* from:long double to:char */
        cast_functions_[make_pair_from_to<long double,char>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<char>(varFrom));
            return{ typeid(char),std::shared_ptr<char>(varTo) };
        };

        /* from:long double to:char16_t */
        cast_functions_[make_pair_from_to<long double,char16_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<char16_t>(varFrom));
            return{ typeid(char16_t),std::shared_ptr<char16_t>(varTo) };
        };

        /* from:long double to:char32_t */
        cast_functions_[make_pair_from_to<long double,char32_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<char32_t>(varFrom));
            return{ typeid(char32_t),std::shared_ptr<char32_t>(varTo) };
        };

        /* from:long double to:float */
        cast_functions_[make_pair_from_to<long double,float>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<float>(varFrom));
            return{ typeid(float),std::shared_ptr<float>(varTo) };
        };

        /* from:long double to:double */
        cast_functions_[make_pair_from_to<long double,double>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
            const auto & varFrom=*(reinterpret_cast<const long double*>(arg.get()));
            auto * varTo=new auto(static_cast<double>(varFrom));
            return{ typeid(double),std::shared_ptr<double>(varTo) };
        };

        add_std_string_cast(this);

    }

};

void add_std_string_cast(StaticCastMap *arg) {

    auto & cast_functions_=arg->cast_functions_;

    cast_functions_[make_pair_from_to<std::string,bool>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
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

    cast_functions_[make_pair_from_to<bool,std::string>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const bool*>(arg.get()));
        if (varFrom) {
            return{ typeid(std::string), std::shared_ptr<std::string>(new std::string("true"))};
        }
        else {
            return{ typeid(std::string), std::shared_ptr<std::string>(new std::string("false"))};
        }
    };

    //TODO:write later
    cast_functions_[make_pair_from_to<std::string,std::int8_t>()]=[](const std::shared_ptr<const void>&arg)->RuntimeType {
        const auto & varFrom=*(reinterpret_cast<const std::string*>(arg.get()));

    };

}

StaticCastMap & get_static_cast_map() {
    static StaticCastMap static_cast_map_;
    return static_cast_map_;
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




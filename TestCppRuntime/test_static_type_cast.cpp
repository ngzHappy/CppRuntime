#include <RuntimeType.hpp>
#include <cassert>

void test_static_type_cast() {

    {
        auto int_double_cast_function=runtime::type::get_static_class_cast_function(
            typeid(int),
            typeid(double)
        );

        enum {
            o=sizeof(runtime::type::SharedVoidType),
            y=sizeof(std::shared_ptr<void>),
            z=sizeof(runtime::type::RuntimeType),
            d=sizeof(double)
        };

        int test=12;
        runtime::type::SharedVoidType tvalue{ &test };
        auto ans=int_double_cast_function(tvalue);
        double ans_double=*ans.data.value<double>();

        assert(ans_double==12.0);
    }

    {
        auto cast_function=runtime::type::get_static_class_cast_function(
            typeid(bool),
            typeid(std::string)
        );

        bool test=true;
        runtime::type::SharedVoidType tvalue{ &test };
        auto ans=cast_function(tvalue);
        auto & var_ans=*ans.data.value<std::string>();
        assert(var_ans=="true");
    }

    {
        auto cast_function=runtime::type::get_static_class_cast_function(
            typeid(bool),
            typeid(std::string)
        );

        bool test=false;
        runtime::type::SharedVoidType tvalue{ &test };
        auto ans=cast_function(tvalue);
        auto & var_ans=*ans.data.value<std::string>();
        assert(var_ans=="false");
    }

    {
        auto cast_function=runtime::type::get_static_class_cast_function(
            typeid(std::string),
            typeid(bool)
        );

        std::string test="false";
        runtime::type::SharedVoidType tvalue{ &test };
        auto ans=cast_function(tvalue);
        auto & var_ans=*ans.data.value<bool>();
        assert(var_ans==false);
    }

}

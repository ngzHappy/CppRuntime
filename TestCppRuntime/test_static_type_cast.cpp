#include <RuntimeType.hpp>
#include <cassert>


void test_static_type_cast(){


    auto int_double_cast_function=runtime::type::get_static_class_cast_function(
        typeid(int),
        typeid(double)
    );

    enum {
    o=sizeof(runtime::type::SharedVoidType),
    y=sizeof(std::shared_ptr<void>),
    z=sizeof(runtime::type::RuntimeType)
    };

    int test=12;
    runtime::type::SharedVoidType tvalue{&test};
    //int_double_cast_function();



}

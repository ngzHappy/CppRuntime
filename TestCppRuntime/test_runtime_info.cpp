#include <RuntimeType.hpp>
#include <cassert>


void test_runtime_info(){

    {
        auto value=runtime::type::get_runtime_class_info(typeid(float));
        assert(value->readable_class_name()=="float");
        (void)value;
    }

}

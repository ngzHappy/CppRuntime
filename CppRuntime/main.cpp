#include "RuntimeType.hpp"
#include <cassert>

int main(int,char **) {
    
    auto int_double_cast_function=runtime::type::get_static_class_cast_function(
        typeid(int),
        typeid(double)
    );

    int value=12;

    auto test_ans=
    std::static_pointer_cast<double>(
    int_double_cast_function(std::shared_ptr<int>(&value,[](auto *) {})).data);

    assert(*test_ans==value);

}






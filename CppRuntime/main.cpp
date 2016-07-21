#include "RuntimeType.hpp"
#include <cassert>

/*just for static code check*/
int _main__(int,char **) {
    
    auto int_double_cast_function=runtime::type::get_static_class_cast_function(
        typeid(int),
        typeid(double)
    );

    enum {
    o=sizeof(runtime::type::SharedVoidType),
    y=sizeof(std::shared_ptr<void>)
    };

    return 0;
}






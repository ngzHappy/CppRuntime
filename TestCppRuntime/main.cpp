#include <RuntimeType.hpp>
#include <cassert>

extern void test_void_shared();
extern void test_static_type_cast();

int main(int , char **)
{
    test_void_shared();
    void test_static_type_cast();
}

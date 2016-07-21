#include <RuntimeType.hpp>
#include <cassert>

void test_void_shared() {

    using namespace runtime::type;

    {
        auto rname=runtime::type::RuntimeTypeConcept<std::string>::readable_class_name();
        assert(rname=="std::string");
    }

    {
        runtime::type::SharedVoidType t0;
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==false);
        assert(t0.data()==nullptr);
        assert(t0==false);
    }

    {
        runtime::type::SharedVoidType t0(nullptr);
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==false);
        assert(t0.data()==nullptr);
        assert(t0==false);
    }

    {
        void *test=nullptr;
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==false);
        assert(t0.data()==nullptr);
        assert(t0==false);
    }

    {
        std::shared_ptr<void> test;
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==false);
        assert(t0.is_const()==false);
        assert(t0.data()==nullptr);
        assert(t0==false);
    }

    {
        int *test=new int{12};
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==false);
        assert(t0.data()==test);
        assert(t0==true);
        delete test;
    }

    {
        std::shared_ptr<int> test{ new int{12} };
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==false);
        assert(t0.is_const()==false);
        assert(t0.data()==test.get());
        assert(t0==true);
    }

    {
        const void *test=nullptr;
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==true);
        assert(t0.data()==nullptr);
        assert(t0==false);
    }

    {
        std::shared_ptr<const void> test;
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==false);
        assert(t0.is_const()==true);
        assert(t0.data()==nullptr);
        assert(t0==false);
    }

    {
        const int *test=new int{12};
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==true);
        assert(t0.data()==test);
        assert(t0==true);
        delete test;
    }

    {
        const int *test=new int{12};
        runtime::type::SharedVoidType t1(test);
        runtime::type::SharedVoidType t0;
        t0=t1;
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==true);
        assert(t0.data()==test);
        assert(t0==true);
        delete test;
    }

    {
        const int *test=new int{12};
        runtime::type::SharedVoidType t1(test);
        runtime::type::SharedVoidType t0;
        t0=std::move(t1);
        assert(t0.is_plain_data()==true);
        assert(t0.is_const()==true);
        assert(t0.data()==test);
        assert(t0==true);
        delete test;
    }

    {
        std::shared_ptr<const int> test{ new int{12} };
        runtime::type::SharedVoidType t0(test);
        assert(t0.is_plain_data()==false);
        assert(t0.is_const()==true);
        assert(t0.data()==test.get());
        assert(t0==true);
    }

    {
        std::shared_ptr<const int> test{ new int{12} };
        runtime::type::SharedVoidType t1(test);
        runtime::type::SharedVoidType t0=t1;
        assert(t0.is_plain_data()==false);
        assert(t0.is_const()==true);
        assert(t0.data()==test.get());
        assert(t0==true);
    }

    {
        std::shared_ptr<const int> test{ new int{12} };
        runtime::type::SharedVoidType t1(test);
        runtime::type::SharedVoidType t0=std::move(t1);
        assert(t0.is_plain_data()==false);
        assert(t0.is_const()==true);
        assert(t0.data()==test.get());
        assert(t0==true);
    }

}

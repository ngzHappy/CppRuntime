TEMPLATE = subdirs

SUBDIRS += \
    CppRuntime \
    StaticCastMaker \
    TestCppRuntime

TestCppRuntime.depends+=CppRuntime


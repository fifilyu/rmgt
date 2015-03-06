ADD_EXECUTABLE(common_unittest 
    gtest_main.cc
    common_unittest.cxx
    ../src/common.cxx)

TARGET_LINK_LIBRARIES(common_unittest gtest gtest_main)

ADD_EXECUTABLE(HostCtx_unittest 
    gtest_main.cc
    HostCtx_unittest.cxx
    ../src/Host.cxx
    ../src/HostCtx.cxx
    ../src/common.cxx)

TARGET_LINK_LIBRARIES(HostCtx_unittest gtest gtest_main)

find_package(GTest REQUIRED)

set(TEST_SUFFIX "TestRunner")

set(TEST_PROJECT_NAME "Elink${TEST_SUFFIX}")

add_executable(${TEST_PROJECT_NAME}
        # iec60870 tests
        ## codec
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/codec/Test_OStream.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/codec/Test_IStream.cpp
        ## cpxxtime2a
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/cpxxtime2a/Test_CPxxTime2a.cpp
        ## io
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectAddress.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectTypeID.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_SinglePointInformation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_SinglePointWithCP24Time2a.cpp
)

target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main)

enable_testing()
add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})

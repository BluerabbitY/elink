
find_package(GTest REQUIRED)

set(TEST_SUFFIX "TestRunner")

set(TEST_PROJECT_NAME "Elink${TEST_SUFFIX}")

add_executable(${TEST_PROJECT_NAME}
        # common tests
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_OStreamCommon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_IStreamCommon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_RelocatedLog.cpp
        # iec60870 tests
        ## codec
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/codec/Test_OStream.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/codec/Test_IStream.cpp
        ## cpxxtime2a
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/cpxxtime2a/Test_CPxxTime2a.cpp
        ## formatter
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/formatter/Test_Formatter.cpp
        ## io
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectAddress.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectTypeID.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_SinglePointInformation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_SinglePointWithCP24Time2a.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_DoublePointInformation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_DoublePointWithCP24Time2a.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_StepPositionInformation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_StepPositionWithCP24Time2a.cpp
)

target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main)

enable_testing()
add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})

target_compile_options(${TEST_PROJECT_NAME} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/WX,-Werror>)

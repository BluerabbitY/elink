find_package(GTest REQUIRED)

set(TEST_SUFFIX "TestRunner")

set(TEST_PROJECT_NAME "Elink${TEST_SUFFIX}")

add_executable(${TEST_PROJECT_NAME}
        # common tests
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_OStreamCommon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_IStreamCommon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_RelocatedLog.cpp
        # iec60870 tests
        ## asdu
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/asdu/Test_ApplicationServiceDataUnit.cpp
        ## codec
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/codec/Test_OStream.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/codec/Test_IStream.cpp
        ## communication
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/communication/Test_FT12MessageTransceiver.cpp
        ## cpxxtime2a
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/cpxxtime2a/Test_CPxxTime2a.cpp
        ## formatter
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/formatter/Test_Formatter.cpp
        ## io - common
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectAddress.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectTypeID.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectSerializable.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_InformationObjectWithCPxxTime2a.cpp
        ## io - information objects
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_SinglePointInformationSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_DoublePointInformationSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_StepPositionInformationSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_BitString32Set.cpp
)

target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main)

enable_testing()
add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})

target_compile_options(${TEST_PROJECT_NAME} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/WX,-Werror>)

if(WIN32)
    target_link_libraries(${TEST_PROJECT_NAME} PRIVATE ws2_32)
endif()

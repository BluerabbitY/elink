###################################################################################
#
# Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
#
# SPDX-License-Identifier: MIT
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
###################################################################################

find_package(GTest REQUIRED)

set(TEST_SUFFIX "TestRunner")

set(TEST_PROJECT_NAME "Elink${TEST_SUFFIX}")

add_executable(${TEST_PROJECT_NAME}
        # common tests
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_OStreamCommon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_IStreamCommon.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/Test_RelocatedLog.cpp
        # iec60870 tests
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/Test_ApplicationServiceDataUnit.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/Test_BinaryCounterReading.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/Test_StatusAndStatusChangeDetection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/Test_SingleEvent.cpp
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
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_MeasuredValueNormalizedSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_MeasuredValueScaledSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_MeasuredValueShortSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_IntegratedTotalsSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_EventOfProtectionEquipmentSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_PackedStartEventsOfProtectionEquipmentSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_PackedOutputCircuitInfoSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_PackedSinglePointWithSCD.cpp
        ${CMAKE_CURRENT_LIST_DIR}/iec60870/io/Test_CommandSet.cpp
)

target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main)

enable_testing()
add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})

target_compile_options(${TEST_PROJECT_NAME} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/WX,-Werror>)

if(WIN32)
    target_link_libraries(${TEST_PROJECT_NAME} PRIVATE ws2_32)
endif()

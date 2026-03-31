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
cmake_minimum_required(VERSION 4.0)

project(Elink VERSION "0.0.1.0" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(ELINK_BUILD_TESTS "Build and run tests for ELink library" ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/asio)

################################################################################
# Always provide test from FetchContent to avoid system package dependency.
# FETCHCONTENT_SOURCE_DIR_GOOGLETEST overrides.
if (ELINK_BUILD_TESTS)
    message(STATUS "Build and run tests")
    include(FetchContent)

    enable_testing()

    set(TEST_SUFFIX "TestRunner")
    set(ELINK_GTEST_TAG "v1.17.0" CACHE STRING "Git tag/commit for googletest")

    message(STATUS "Test suite version: googletest[${ELINK_GTEST_TAG}]")

    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG ${ELINK_GTEST_TAG})

    FetchContent_MakeAvailable(googletest)

    add_subdirectory(test)
endif()

################################################################################
# Package configuration files
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(ELINK_CMAKE_PACKAGE_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(ELINK_CMAKE_CONFIG_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake")
set(ELINK_CONFIG_FILE "${ELINK_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(ELINK_CONFIG_VERSION_FILE "${ELINK_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")

add_library(${PROJECT_NAME} INTERFACE)

string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME ${PROJECT_NAME_LOWER})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/asio>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Write version file
write_basic_package_version_file(
        "${ELINK_CONFIG_VERSION_FILE}"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

# Configure the config file using the helper (handles @PACKAGE_*@ vars correctly)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${ELINK_CONFIG_FILE}"
        INSTALL_DESTINATION "${ELINK_CMAKE_PACKAGE_DIR}"
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR)

# Install config files
install(FILES
        "${ELINK_CONFIG_FILE}"
        "${ELINK_CONFIG_VERSION_FILE}"
        DESTINATION "${ELINK_CMAKE_PACKAGE_DIR}"
        COMPONENT dev)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        COMPONENT dev
        PATTERN ".DS_Store" EXCLUDE)

# Install targets and export
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE Elink::
        DESTINATION "${ELINK_CMAKE_PACKAGE_DIR}"
        COMPONENT dev)

# Export for build tree (optional but useful)
export(EXPORT ${PROJECT_NAME}Targets
        NAMESPACE Elink::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

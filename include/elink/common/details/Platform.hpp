/***********************************************************************************
 * \file Platform.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-01-25 17:36:41
 * 
 * \copyright Copyright (C) 2026 BlueRabbitY. All rights reserved.
 *
 * Unless required by applicable law or agreed to in writing, software distributed
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. 
 *
 ***********************************************************************************/
#pragma once

#define ELINK_WIN32 0
#define ELINK_LINUX 1
#define ELINK_UNIX  2
#define ELINK_APPLE 3

#if defined(_WIN32)
    #define ELINK_PLATFORM ELINK_WIN32
#elif defined(__linux__)
    #define ELINK_PLATFORM ELINK_LINUX
#elif defined(__unix__)
    #define ELINK_PLATFORM ELINK_UNIX
#elif defined(__APPLE__)
    #define ELINK_PLATFORM ELINK_APPLE
#endif

#define ELINK_API_WIN32 0
#define ELINK_API_POSIX 1

#if defined(_WIN32)
    #define ELINK_API ELINK_API_WIN32
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
    #define ELINK_API ELINK_API_POSIX
#endif

#define ELINK_COMPILER_CLANG   0
#define ELINK_COMPILER_GCC     1
#define ELINK_COMPILER_MSVC    2
#define ELINK_COMPILER_UNKNOWN 3

#if defined(__clang__)
    #define ELINK_COMPILER ELINK_COMPILER_CLANG
#elif defined(__GNUC__)
    #define ELINK_COMPILER ELINK_COMPILER_GCC
#elif defined(_MSC_VER)
    #define ELINK_COMPILER ELINK_COMPILER_MSVC
#else
    #define ELINK_COMPILER ELINK_COMPILER_UNKNOWN
#endif

#if (ELINK_COMPILER == ELINK_COMPILER_CLANG)
    #define ELINK_CLANG_VERSION_CHECK(major, minor, patch) \
        (defined(__clang__) && \
        ((__clang_major__ > (major)) || \
        (__clang_major__ == (major) && __clang_minor__ > (minor)) || \
        (__clang_major__ == (major) && __clang_minor__ == (minor) && __clang_patchlevel__ >= (patch))))
#elif (ELINK_COMPILER == ELINK_COMPILER_GCC)
    #define ELINK_GCC_VERSION_CHECK(major, minor, patch) \
        (defined(__GNUC__) && \
        ((__GNUC__ > (major)) || \
        (__GNUC__ == (major) && __GNUC_MINOR__ > (minor)) || \
        (__GNUC__ == (major) && __GNUC_MINOR__ == (minor) && __GNUC_PATCHLEVEL__ >= (patch))))
#elif (ELINK_COMPILER == ELINK_COMPILER_MSVC)
    #define ELINK_MSVC_VERSION_CHECK(major, minor, patch) \
        (defined(_MSC_VER) && \
        (major * 100 + minor + patch))
#endif

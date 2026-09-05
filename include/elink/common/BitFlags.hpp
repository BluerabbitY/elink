/***********************************************************************************
 * \file BitFlags.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-08-15 19:38:44
 * 
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ***********************************************************************************/
#pragma once

#include "elink/util/Utils.hpp"
#include "elink/common/details/codec/IStream.hpp"
#include "elink/common/details/codec/OStream.hpp"

#include <type_traits>
#include <initializer_list>
#include <limits>
#include <bit>

namespace elink
{

namespace details
{

template <auto... Values>
struct FlagsValidator
{
    ELINK_STATIC_ASSERT((util::is_single_bit(Values) && ...), "All flag values must be single bits (powers of two)");
};

}

template <util::IsEnumClass T>
class BitFlags
{
public:
    using UnderlyingType = std::underlying_type_t<T>;

    constexpr BitFlags() = default;

    constexpr explicit BitFlags(UnderlyingType value) noexcept : m_value{value}
    {
    }

    constexpr explicit BitFlags(T value) noexcept : m_value{static_cast<UnderlyingType>(value)}
    {
    }

    explicit BitFlags(std::initializer_list<T> values) noexcept : m_value{0}
    {
        for (const auto& value : values)
        {
            m_value |= static_cast<UnderlyingType>(value);
        }
    }

    ~BitFlags() = default;

    constexpr BitFlags &operator=(T value) noexcept
    {
        m_value = static_cast<UnderlyingType>(value);
        return *this;
    }

    constexpr BitFlags &set(T flag) noexcept
    {
        m_value |= static_cast<UnderlyingType>(flag);
        return *this;
    }

    constexpr BitFlags &clear(T flag) noexcept
    {
        m_value &= ~static_cast<UnderlyingType>(flag);
        return *this;
    }

    constexpr BitFlags &set(T flag, const bool value) noexcept
    {
        value ? set(flag) : clear(flag);
        return *this;
    }

    constexpr BitFlags &clearAll() noexcept
    {
        m_value = 0;
        return *this;
    }

    [[nodiscard]] constexpr bool test(T flag) const noexcept
    {
        return (m_value & static_cast<UnderlyingType>(flag)) != 0;
    }

    [[nodiscard]] constexpr bool testAll(T flag) const noexcept
    {
        return (m_value & static_cast<UnderlyingType>(flag)) == static_cast<UnderlyingType>(flag);
    }

    constexpr BitFlags &flip(T flag) noexcept
    {
        m_value ^= static_cast<UnderlyingType>(flag);
        return *this;
    }

    constexpr BitFlags &flip() noexcept
    {
        m_value = ~m_value;
        return *this;
    }

    constexpr BitFlags &operator|=(T rhs) noexcept
    {
        m_value |= static_cast<UnderlyingType>(rhs);
        return *this;
    }

    constexpr BitFlags &operator&=(T rhs) noexcept
    {
        m_value &= static_cast<UnderlyingType>(rhs);
        return *this;
    }

    constexpr BitFlags &operator^=(T rhs) noexcept
    {
        m_value ^= static_cast<UnderlyingType>(rhs);
        return *this;
    }

    constexpr BitFlags &operator|=(const BitFlags rhs) noexcept
    {
        m_value |= rhs.m_value;
        return *this;
    }

    constexpr BitFlags &operator&=(const BitFlags rhs) noexcept
    {
        m_value &= rhs.m_value;
        return *this;
    }

    constexpr BitFlags &operator^=(const BitFlags rhs) noexcept
    {
        m_value ^= rhs.m_value;
        return *this;
    }

    [[nodiscard]] constexpr BitFlags operator~() const noexcept
    {
        return BitFlags{~m_value};
    }

    [[nodiscard]] constexpr auto operator<=>(const BitFlags& rhs) const noexcept = default;

    [[nodiscard]] constexpr bool operator==(const BitFlags&) const noexcept = default;

    [[nodiscard]] constexpr explicit operator bool() const noexcept
    {
        return m_value != 0;
    }

    [[nodiscard]] constexpr UnderlyingType value() const noexcept
    {
        return m_value;
    }

    [[nodiscard]] constexpr bool any() const noexcept
    {
        return m_value != 0;
    }

    [[nodiscard]] constexpr bool none() const noexcept
    {
        return m_value == 0;
    }

    [[nodiscard]] constexpr bool all() const noexcept
    {
        return m_value == std::numeric_limits<UnderlyingType>::max();
    }

    [[nodiscard]] constexpr std::size_t count() const noexcept
    {
        return std::popcount(m_value);
    }

    friend details::IStream &operator>>(details::IStream &stream, BitFlags flags)
    {
        stream >> flags.m_value;
        return stream;
    }

    friend details::OStream &operator<<(details::OStream &stream, const BitFlags flags)
    {
        stream << flags.m_value;
        return stream;
    }

private:
    UnderlyingType m_value;
};

template <util::IsEnumClass T>
constexpr BitFlags<T> operator|(T lhs, T rhs) noexcept
{
    return BitFlags<T>{lhs} | rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator&(T lhs, T rhs) noexcept
{
    return BitFlags<T>{lhs} & rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator^(T lhs, T rhs) noexcept
{
    return BitFlags<T>{lhs} ^ rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator|(BitFlags<T> lhs, T rhs) noexcept
{
    return lhs | rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator&(BitFlags<T> lhs, T rhs) noexcept
{
    return lhs & rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator^(BitFlags<T> lhs, T rhs) noexcept
{
    return lhs ^ rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator|(BitFlags<T> lhs, BitFlags<T> rhs) noexcept
{
    return lhs | rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator&(BitFlags<T> lhs, BitFlags<T> rhs) noexcept
{
    return lhs & rhs;
}

template <util::IsEnumClass T>
constexpr BitFlags<T> operator^(BitFlags<T> lhs, BitFlags<T> rhs) noexcept
{
    return lhs ^ rhs;
}

}

#define ELINK_FLAGS_OPERATORS(EnumType)                                                                 \
    (constexpr auto operator|(EnumType lhs, EnumType rhs) noexcept                                      \
    {                                                                                                   \
        return elink::BitFlags<EnumType>{lhs} | rhs;                                                    \
    }                                                                                                   \
    constexpr auto operator&(EnumType lhs, EnumType rhs) noexcept                                       \
    {                                                                                                   \
        return elink::BitFlags<EnumType>{lhs} & rhs;                                                    \
    }                                                                                                   \
    constexpr auto operator^(EnumType lhs, EnumType rhs) noexcept                                       \
    {                                                                                                   \
        return elink::BitFlags<EnumType>{lhs} ^ rhs;                                                    \
    }                                                                                                   \
    constexpr auto operator|(elink::BitFlags<EnumType> lhs, EnumType rhs) noexcept                      \
    {                                                                                                   \
        return lhs | rhs;                                                                               \
    }                                                                                                   \
    constexpr auto operator&(elink::BitFlags<EnumType> lhs, EnumType rhs) noexcept                      \
    {                                                                                                   \
        return lhs & rhs;                                                                               \
    }                                                                                                   \
    constexpr auto operator^(elink::BitFlags<EnumType> lhs, EnumType rhs) noexcept                      \
    {                                                                                                   \
        return lhs ^ rhs;                                                                               \
    }                                                                                                   \
    constexpr auto operator|(elink::BitFlags<EnumType> lhs, elink::BitFlags<EnumType> rhs) noexcept     \
    {                                                                                                   \
        return lhs | rhs;                                                                               \
    }                                                                                                   \
    constexpr auto operator|(elink::BitFlags<EnumType> lhs, elink::BitFlags<EnumType> rhs) noexcept     \
    {                                                                                                   \
        return lhs | rhs;                                                                               \
    }                                                                                                   \
    constexpr auto operator|(elink::BitFlags<EnumType> lhs, elink::BitFlags<EnumType> rhs) noexcept     \
    {                                                                                                   \
        return lhs | rhs;                                                                               \
    })

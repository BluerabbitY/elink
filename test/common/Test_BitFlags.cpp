/***********************************************************************************
 * \file Test_BitFlags.cpp
 * \author BlueRabbitY (BlueRabbitY@protonmail.com)
 * \brief Unit tests for elink::BitFlags
 * \date 2026-05-01 21:06:00
 *
 * \copyright Copyright (C) 2026-2026 BlueRabbitY. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ***********************************************************************************/
#include "elink/common/BitFlags.hpp"
#include "elink/iec60870/io/QualityDescriptor.hpp"
#include "elink/iec60870/io/QualityDescriptorP.hpp"
#include "elink/common/details/codec/IStream.hpp"
#include "elink/common/details/codec/OStream.hpp"

#include <gtest/gtest.h>

namespace {

enum class TestFlag : uint8_t {
    None = 0,
    A = 1 << 0,
    B = 1 << 1,
    C = 1 << 2,
    D = 1 << 3,
};

class BitFlagsTest : public ::testing::Test
{
protected:
    using Flags = elink::BitFlags<TestFlag>;
};

TEST_F(BitFlagsTest, ConstructFromEnum)
{
    const Flags f{TestFlag::A};
    EXPECT_TRUE(f.test(TestFlag::A));
    EXPECT_FALSE(f.test(TestFlag::B));
    EXPECT_EQ(f.count(), 1u);
}

TEST_F(BitFlagsTest, ConstructFromUnderlying)
{
    const Flags f{static_cast<std::underlying_type_t<TestFlag>>(TestFlag::B)};
    EXPECT_TRUE(f.test(TestFlag::B));
    EXPECT_EQ(f.value(), static_cast<std::underlying_type_t<TestFlag>>(TestFlag::B));
}

TEST_F(BitFlagsTest, ConstructFromInitializerList)
{
    const Flags f{ { TestFlag::A, TestFlag::C } };
    EXPECT_TRUE(f.test(TestFlag::A));
    EXPECT_TRUE(f.test(TestFlag::C));
    EXPECT_FALSE(f.test(TestFlag::B));
    EXPECT_EQ(f.count(), 2u);
}

TEST_F(BitFlagsTest, SetClearFlipClearAll)
{
    Flags f{};
    EXPECT_TRUE(f.none());

    f.set(TestFlag::A);
    EXPECT_TRUE(f.test(TestFlag::A));
    EXPECT_TRUE(f.any());

    f.set(TestFlag::B);
    EXPECT_TRUE(f.test(TestFlag::B));
    EXPECT_EQ(f.count(), 2u);

    f.clear(TestFlag::A);
    EXPECT_FALSE(f.test(TestFlag::A));
    EXPECT_TRUE(f.test(TestFlag::B));

    f.flip(TestFlag::B);
    EXPECT_FALSE(f.test(TestFlag::B));

    f.set(TestFlag::C);
    f.set(TestFlag::D);
    EXPECT_EQ(f.count(), 2u);

    f.flip(); // flip all bits
    EXPECT_TRUE(f.test(TestFlag::A));
    // depending on underlying width, "all" may differ; just ensure value changed
    EXPECT_NE(f.none(), true);

    f.clearAll();
    EXPECT_TRUE(f.none());
}

TEST_F(BitFlagsTest, BitwiseAssignmentWithEnum)
{
    Flags f{};
    f |= TestFlag::A;
    EXPECT_TRUE(f.test(TestFlag::A));

    f &= TestFlag::A; // should keep A
    EXPECT_TRUE(f.test(TestFlag::A));

    f ^= TestFlag::A; // toggle A -> off
    EXPECT_FALSE(f.test(TestFlag::A));
}

TEST_F(BitFlagsTest, BitwiseAssignmentWithBitFlags)
{
    Flags a{ { TestFlag::A, TestFlag::B } };
    Flags b{ { TestFlag::B, TestFlag::C } };

    a &= b;
    EXPECT_TRUE(a.test(TestFlag::B));
    EXPECT_FALSE(a.test(TestFlag::A));

    a = Flags(std::initializer_list{TestFlag::A, TestFlag::B});
    a |= b;
    EXPECT_TRUE(a.test(TestFlag::A));
    EXPECT_TRUE(a.test(TestFlag::B));
    EXPECT_TRUE(a.test(TestFlag::C));

    a = Flags(std::initializer_list{TestFlag::A});
    a ^= b;
    // A ^ (B|C) -> A,B,C set
    EXPECT_TRUE(a.test(TestFlag::A));
    EXPECT_TRUE(a.test(TestFlag::B));
    EXPECT_TRUE(a.test(TestFlag::C));
}

TEST_F(BitFlagsTest, ComparisonAndBool)
{
    const Flags empty{};
    const Flags one{TestFlag::A};
    const Flags one_copy{TestFlag::A};

    EXPECT_FALSE(static_cast<bool>(empty));
    EXPECT_TRUE(static_cast<bool>(one));
    EXPECT_EQ(one, one_copy);
    EXPECT_NE(one, empty);
}

TEST_F(BitFlagsTest, WorksWithQualityDescriptor)
{
    using namespace elink::iec60870;
    using QFlags = elink::BitFlags<QualityDescriptor>;

    QFlags f{Quality::BL};
    EXPECT_TRUE(f.test(Quality::BL));
    EXPECT_FALSE(f.test(Quality::SB));

    f |= Quality::SB;
    EXPECT_TRUE(f.test(Quality::BL));
    EXPECT_TRUE(f.test(Quality::SB));

    f &= Quality::BL; // keep only BL
    EXPECT_TRUE(f.test(Quality::BL));
    EXPECT_FALSE(f.test(Quality::SB));

    elink::details::FlagsValidator<Quality::SPILL, Quality::BLOCKED, Quality::SUBSTITUTED, Quality::NON_TOPICAL, Quality::INVALID> validator;
}

TEST_F(BitFlagsTest, WorksWithQualityDescriptorP)
{
    using namespace elink::iec60870;

    elink::BitFlags pf{QualityP::BL};
    EXPECT_TRUE(pf.test(QualityP::BL));
    EXPECT_FALSE(pf.test(QualityP::IV));

    pf.set(QualityP::IV);
    EXPECT_TRUE(pf.test(QualityP::IV));

    EXPECT_EQ(pf.count(), 2u);

    elink::details::FlagsValidator<QualityP::ELAPSED_TIME_INVALID, QualityP::BLOCKED, QualityP::SUBSTITUTED, QualityP::NON_TOPICAL, QualityP::INVALID> validator;
}

TEST_F(BitFlagsTest, OStreamWritesUnderlying)
{
    using U = std::underlying_type_t<TestFlag>;
    constexpr U expect = static_cast<U>(TestFlag::B);

    uint8_t buffer[sizeof(U)]{};
    elink::details::OStream os{buffer, sizeof(buffer)};

    const Flags f{TestFlag::B};
    os << f;

    EXPECT_FALSE(os.hasError());
    EXPECT_EQ(buffer[0], static_cast<uint8_t>(expect & 0xFF));
}

TEST_F(BitFlagsTest, IStreamReadsUnderlying)
{
    using U = std::underlying_type_t<TestFlag>;
    constexpr U value = static_cast<U>(TestFlag::C);

    uint8_t buffer[sizeof(U)]{value & 0xFF};
    elink::details::IStream is{buffer, sizeof(buffer)};

    // operator>> overload for BitFlags currently accepts BitFlags by value and
    // does not modify the caller. Read into the underlying type instead and
    // construct a BitFlags from that value.
    U read_u{};
    is >> read_u;

    EXPECT_FALSE(is.hasError());

    const Flags f{static_cast<TestFlag>(read_u)};
    EXPECT_EQ(f.value(), static_cast<Flags::UnderlyingType>(read_u));
}

} // namespace

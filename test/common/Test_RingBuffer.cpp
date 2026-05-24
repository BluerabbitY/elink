/***********************************************************************************
 * \file Test_RingBuffer.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief
 * \date 2026-05-14 06:21:00
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
#include "elink/common/RingBuffer.hpp"

#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <numeric>

class RingBufferTest : public ::testing::Test
{
protected:

    static constexpr std::size_t BUF_SIZE = 16;
    using TestRingBuffer = elink::RingBuffer<BUF_SIZE>;

    TestRingBuffer buf;
};

TEST_F(RingBufferTest, InitialStateIsEmpty)
{
    EXPECT_TRUE(buf.empty());
    EXPECT_FALSE(buf.full());
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_EQ(buf.free_space(), BUF_SIZE);
}

TEST_F(RingBufferTest, CapacityConstant)
{
    EXPECT_EQ(TestRingBuffer::capacity, BUF_SIZE);
}

TEST_F(RingBufferTest, WriteAndReadBack)
{
    constexpr std::array<uint8_t, 4> src = {0x01, 0x02, 0x03, 0x04};
    const std::size_t written = buf.write(elink::LiteBufferView{src});
    EXPECT_EQ(written, 4u);
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.free_space(), BUF_SIZE - 4u);

    std::array<uint8_t, 4> dst{};
    const std::size_t read = buf.read(elink::LiteBuffer{dst});
    EXPECT_EQ(read, 4u);
    EXPECT_EQ(dst, src);
    EXPECT_TRUE(buf.empty());
}

TEST_F(RingBufferTest, WriteReturnsBytesWritten)
{
    std::array<uint8_t, BUF_SIZE + 4> oversized{};
    std::iota(oversized.begin(), oversized.end(), 0u);

    const std::size_t written = buf.write(elink::LiteBufferView{oversized});
    // clipped to capacity
    EXPECT_EQ(written, BUF_SIZE);
    EXPECT_TRUE(buf.full());
}

TEST_F(RingBufferTest, WriteToFullBufferReturnsZero)
{
    std::array<uint8_t, BUF_SIZE> src{};
    buf.write(elink::LiteBufferView{src});
    ASSERT_TRUE(buf.full());

    constexpr std::array<uint8_t, 1> extra = {0xFF};
    EXPECT_EQ(buf.write(elink::LiteBufferView{extra}), 0u);
}

TEST_F(RingBufferTest, ReadFromEmptyBufferReturnsZero)
{
    std::array<uint8_t, 4> dst{};
    EXPECT_EQ(buf.read(elink::LiteBuffer{dst}), 0u);
}

TEST_F(RingBufferTest, ReadLessThanAvailable)
{
    const std::array<uint8_t, 8> src = {1,2,3,4,5,6,7,8};
    buf.write(elink::LiteBufferView{src});

    std::array<uint8_t, 4> dst{};
    const std::size_t read = buf.read(elink::LiteBuffer{dst});
    EXPECT_EQ(read, 4u);
    EXPECT_EQ(buf.size(), 4u);
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(dst[i], src[i]);
    }
}

TEST_F(RingBufferTest, WrapAroundWrite)
{
    // Fill the buffer completely, then consume half to create space at the
    // beginning. The next write must wrap around.
    std::array<uint8_t, BUF_SIZE> full{};
    std::iota(full.begin(), full.end(), 0u);
    buf.write(elink::LiteBufferView{full});

    std::array<uint8_t, BUF_SIZE / 2> tmp{};
    // consume first half → free space at start
    buf.read(elink::LiteBuffer{tmp});

    const std::array<uint8_t, BUF_SIZE / 2> second = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7};
    EXPECT_EQ(buf.write(elink::LiteBufferView{second}), BUF_SIZE / 2u);
    EXPECT_TRUE(buf.full());

    // Read remaining first-half data
    std::array<uint8_t, BUF_SIZE / 2> out1{};
    buf.read(elink::LiteBuffer{out1});
    for (std::size_t i = 0; i < BUF_SIZE / 2; ++i) {
        EXPECT_EQ(out1[i], full[BUF_SIZE / 2 + i]);
    }

    // Read wrapped second-half data
    std::array<uint8_t, BUF_SIZE / 2> out2{};
    buf.read(elink::LiteBuffer{out2});
    EXPECT_EQ(out2, second);
    EXPECT_TRUE(buf.empty());
}

TEST_F(RingBufferTest, ClearResetsBuffer)
{
    constexpr std::array<uint8_t, 4> src = {1, 2, 3, 4};
    buf.write(elink::LiteBufferView{src});
    ASSERT_EQ(buf.size(), 4u);

    buf.clear();
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_EQ(buf.free_space(), BUF_SIZE);
}

TEST_F(RingBufferTest, PrepareAndCommit)
{
    const auto bufs = buf.prepare(4);

    // Write into the prepared buffers manually
    auto* ptr = static_cast<uint8_t*>(bufs[0].data());

    for (std::size_t i = 0; i < bufs[0].size(); ++i)
    {
        ptr[i] = static_cast<uint8_t>(i + 1);
    }

    buf.commit(4);
    EXPECT_EQ(buf.size(), 4u);

    std::array<uint8_t, 4> dst{};
    buf.read(elink::LiteBuffer{dst});
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(dst[i], static_cast<uint8_t>(i + 1));
    }
}

TEST_F(RingBufferTest, PrepareOnFullBufferReturnsEmpty)
{
    std::array<uint8_t, BUF_SIZE> src{};
    buf.write(elink::LiteBufferView{src});

    const auto bufs = buf.prepare(1);
    EXPECT_EQ(bufs[0].size(), 0u);
    EXPECT_EQ(bufs[1].size(), 0u);
}

TEST_F(RingBufferTest, CommitClipsToFreeSpace)
{
    // more than capacity
    buf.commit(BUF_SIZE + 100);
    EXPECT_EQ(buf.size(), BUF_SIZE);
    EXPECT_TRUE(buf.full());
}

TEST_F(RingBufferTest, DataReturnsCorrectContent)
{
    constexpr std::array<uint8_t, 4> src = {0x10, 0x20, 0x30, 0x40};
    buf.write(elink::LiteBufferView{src});

    const auto segs = buf.readable_buffers();
    std::vector<uint8_t> collected;

    for (const auto& seg : segs)
    {
        const auto* p = static_cast<const uint8_t*>(seg.data());
        collected.insert(collected.end(), p, p + seg.size());
    }

    ASSERT_EQ(collected.size(), 4u);

    for (std::size_t i = 0; i < 4; ++i)
    {
        EXPECT_EQ(collected[i], src[i]);
    }
}

TEST_F(RingBufferTest, ConsumeReducesSize)
{
    constexpr std::array<uint8_t, 8> src{};
    buf.write(elink::LiteBufferView{src});
    ASSERT_EQ(buf.size(), 8u);

    buf.consume(3);
    EXPECT_EQ(buf.size(), 5u);
}

TEST_F(RingBufferTest, ConsumeAllResetsIndices)
{
    constexpr std::array<uint8_t, 4> src = {1, 2, 3, 4};
    buf.write(elink::LiteBufferView{src});
    buf.consume(4);
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.free_space(), BUF_SIZE);
}

TEST_F(RingBufferTest, ConsumeMoreThanAvailableClips)
{
    constexpr std::array<uint8_t, 4> src{};
    buf.write(elink::LiteBufferView{src});
    buf.consume(100);
    EXPECT_TRUE(buf.empty());
}

TEST_F(RingBufferTest, PrepareReturnsTwoSegmentsWhenWrap)
{
    // Create real wrap around free space: write Idx in the second half,
    // with free space spanning the end+beginning
    std::array<uint8_t, 12> input{};
    std::iota(input.begin(), input.end(), 100u);
    buf.write(elink::LiteBufferView{input});

    std::array<uint8_t, 8> tmp{};
    buf.read(elink::LiteBuffer{tmp});

    auto bufs = buf.prepare(12);

    EXPECT_EQ(bufs[0].size() + bufs[1].size(), 12u);
    EXPECT_GT(bufs[0].size(), 0u);
    EXPECT_GT(bufs[1].size(), 0u);
}

TEST_F(RingBufferTest, DataReturnsTwoSegmentsWhenWrap)
{
    // Key scenario: Creating a surround of "readable data" across array boundaries
    // 1. First, fill the entire buffer (write Idx returns to 0, count=16）
    std::array<uint8_t, BUF_SIZE> full{};
    std::iota(full.begin(), full.end(), 0u);
    buf.write(elink::LiteBufferView{full});

    // 2. The first 8 bytes of consumption (readIdx=8, count=8, data in [8... 15])
    std::array<uint8_t, BUF_SIZE / 2> tmp{};
    buf.read(elink::LiteBuffer{tmp});

    // 3. Write another 4 bytes (write Idx=4, count=12)
    // The readable data is now [8～15]+[0～3], which exactly produces two segments!
    std::array<uint8_t, 4> extra{};
    std::iota(extra.begin(), extra.end(), 100u);
    buf.write(elink::LiteBufferView{extra});

    // Verify data() returns two segments
    const auto segs = buf.readable_buffers();

    EXPECT_EQ(segs[0].size() + segs[1].size(), 12u);
    EXPECT_GT(segs[0].size(), 0u);
    EXPECT_GT(segs[1].size(), 0u);
}

TEST_F(RingBufferTest, WrapAroundRead)
{
    std::array<uint8_t, BUF_SIZE> full{};
    std::iota(full.begin(), full.end(), 0u);
    buf.write(elink::LiteBufferView{full});

    std::array<uint8_t, BUF_SIZE / 2> tmp{};
    buf.read(elink::LiteBuffer{tmp});

    // Read the remaining half of the surrounding area
    std::array<uint8_t, BUF_SIZE / 2> out{};
    const std::size_t read_bytes = buf.read(elink::LiteBuffer{out});

    EXPECT_EQ(read_bytes, BUF_SIZE / 2);

    for (std::size_t i = 0; i < BUF_SIZE / 2; ++i)
    {
        EXPECT_EQ(out[i], full[BUF_SIZE / 2 + i]);
    }

    EXPECT_TRUE(buf.empty());
}

TEST_F(RingBufferTest, PrepareAndCommitPartial)
{
    auto bufs = buf.prepare(10);
    // simulate that only writes 6 bytes
    buf.commit(6);
    EXPECT_EQ(buf.size(), 6u);
    EXPECT_EQ(buf.free_space(), BUF_SIZE - 6u);
}

TEST_F(RingBufferTest, PrepareWithZeroOrExcess)
{
    EXPECT_EQ(buf.prepare(0)[0].size(), 0u);

    std::array<uint8_t, BUF_SIZE> src{};
    buf.write(elink::LiteBufferView{src});  // 写满

    const auto bufs = buf.prepare(100);
    EXPECT_EQ(bufs[0].size(), 0u);
    EXPECT_EQ(bufs[1].size(), 0u);
}

TEST_F(RingBufferTest, WriteAndReadEmptySpan)
{
    std::array<uint8_t, 0> empty{};
    EXPECT_EQ(buf.write(elink::LiteBufferView{empty}), 0u);
    EXPECT_EQ(buf.read(elink::LiteBuffer{empty}), 0u);
}

TEST_F(RingBufferTest, MultipleWrapAround)
{
    // Continuously write to full, read to half,
    // and then write again multiple times to
    // verify that the index does not drift after long-term use
    for (int i = 0; i < 5; ++i)
    {
        std::array<uint8_t, BUF_SIZE> data{};
        std::iota(data.begin(), data.end(), static_cast<uint8_t>(i * 10));

        buf.write(elink::LiteBufferView{data});
        EXPECT_TRUE(buf.full());

        std::array<uint8_t, BUF_SIZE / 2> tmp{};
        buf.read(elink::LiteBuffer{tmp});
        EXPECT_EQ(buf.size(), BUF_SIZE / 2);

        buf.read(elink::LiteBuffer{tmp});
        EXPECT_TRUE(buf.empty());
    }

    EXPECT_TRUE(buf.empty());
}

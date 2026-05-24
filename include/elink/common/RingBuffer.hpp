/***********************************************************************************
 * \file RingBuffer.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-05-13 00:48:00
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

#include "elink/common/Type.hpp"

#include <algorithm>
#include <limits>

#include "asio/buffer.hpp"

namespace elink
{

template <std::size_t N>
requires (N > 0)
class RingBuffer
{
public:
    static constexpr std::size_t capacity = N;
    using MutableBufferSequence = std::array<asio::mutable_buffer, 2>;
    using ConstBufferSequence = std::array<asio::const_buffer, 2>;

    RingBuffer() = default;

    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;

    [[nodiscard]] std::size_t size() const noexcept { return countM; }
    [[nodiscard]] bool empty() const noexcept { return countM == 0; }
    [[nodiscard]] bool full() const noexcept { return countM == capacity; }
    [[nodiscard]] std::size_t free_space() const noexcept { return capacity - countM; }

    MutableBufferSequence prepare(std::size_t n = std::numeric_limits<std::size_t>::max())
    {
        n = std::min(n, free_space());
        if (n == 0) {
            return {};
        }

        const std::size_t first = std::min(n, capacity - writeIdxM);
        MutableBufferSequence bufs{
            asio::buffer(bufferM.data() + writeIdxM, first),
            asio::mutable_buffer{}
        };

        if (first < n) {
            bufs[1] = asio::buffer(bufferM.data(), n - first);
        }
        return bufs;
    }

    void commit(std::size_t n) noexcept
    {
        n = std::min(n, free_space());
        if (n == 0) return;
        countM += n;
        writeIdxM = (writeIdxM + n) % capacity;
    }

    [[nodiscard]] ConstBufferSequence readable_buffers() const
    {
        if (countM == 0)
            return {};

        const std::size_t first = std::min(countM, capacity - readIdxM);
        ConstBufferSequence bufs{
            asio::buffer(bufferM.data() + readIdxM, first),
            asio::const_buffer{}
        };

        if (first < countM) {
            bufs[1] = asio::buffer(bufferM.data(), countM - first);
        }

        return bufs;
    }

    void consume(std::size_t n) noexcept
    {
        n = std::min(n, countM);
        if (n == 0) return;
        countM -= n;
        readIdxM = (readIdxM + n) % capacity;
        if (countM == 0) {
            readIdxM = writeIdxM = 0;
        }
    }

    std::size_t write(LiteBufferView data)
    {
        const std::size_t to_write = std::min(data.size(), free_space());
        if (to_write == 0) return 0;

        std::size_t first = std::min(to_write, capacity - writeIdxM);
        std::copy_n(data.begin(), first, bufferM.begin() + writeIdxM);

        if (first < to_write)
        {
            std::copy_n(data.begin() + static_cast<std::ptrdiff_t>(first), to_write - first, bufferM.begin());
        }

        countM += to_write;
        writeIdxM = (writeIdxM + to_write) % capacity;
        return to_write;
    }

    std::size_t read(LiteBuffer out)
    {
        const std::size_t to_read = std::min(out.size(), countM);
        if (to_read == 0) return 0;

        std::size_t first = std::min(to_read, capacity - readIdxM);
        std::copy_n(bufferM.begin() + readIdxM, first, out.begin());

        if (first < to_read)
        {
            std::copy_n(bufferM.begin(), to_read - first, out.begin() + static_cast<std::ptrdiff_t>(first));
        }

        countM -= to_read;
        readIdxM = (readIdxM + to_read) % capacity;
        if (countM == 0) {
            readIdxM = writeIdxM = 0;
        }

        return to_read;
    }

    void clear() noexcept
    {
        countM = 0;
        readIdxM = writeIdxM = 0;
    }

private:
    std::array<uint8_t, N> bufferM{};
    std::size_t readIdxM = 0;
    std::size_t writeIdxM = 0;
    std::size_t countM = 0;
};

}

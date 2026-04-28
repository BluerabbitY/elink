/***********************************************************************************
 * \file Test_FileSet.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-04-24 00:53:25
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
#include "elink/iec60870/io/FileReady.hpp"
#include "elink/iec60870/io/SectionReady.hpp"
#include "elink/iec60870/io/FileCallOrSelect.hpp"
#include "elink/iec60870/io/FileLastSegmentOrSection.hpp"
#include "elink/iec60870/io/FileACK.hpp"
#include "elink/iec60870/io/FileSegment.hpp"
#include "elink/iec60870/io/FileDirectory.hpp"
#include "elink/iec60870/io/QueryLog.hpp"
#include "elink/iec60870/details/codec/IOStream.h"

#include <gtest/gtest.h>
#include <cstring>

using namespace elink::iec60870;

class FileSetTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(FileSetTest, TypeID)
{
    const FileReady fileReady;
    EXPECT_EQ(fileReady.getTypeID(), TypeID::F_FR_NA_1);

    const SectionReady sectionReady;
    EXPECT_EQ(sectionReady.getTypeID(), TypeID::F_SR_NA_1);

    const FileCallOrSelect fileCallOrSelect;
    EXPECT_EQ(fileCallOrSelect.getTypeID(), TypeID::F_SC_NA_1);

    const FileLastSegmentOrSection fileLastSegmentOrSection;
    EXPECT_EQ(fileLastSegmentOrSection.getTypeID(), TypeID::F_LS_NA_1);

    const FileACK fileACK;
    EXPECT_EQ(fileACK.getTypeID(), TypeID::F_AF_NA_1);

    const FileSegment fileSegment;
    EXPECT_EQ(fileSegment.getTypeID(), TypeID::F_SG_NA_1);

    const FileDirectory fileDirectory;
    EXPECT_EQ(fileDirectory.getTypeID(), TypeID::F_DR_TA_1);

    const QueryLog queryLog{};
    EXPECT_EQ(queryLog.getTypeID(), TypeID::F_SC_NB_1);
}

TEST_F(FileSetTest, IOLength)
{
    const FileReady fileReady;
    EXPECT_EQ(fileReady.size(), 9);
    EXPECT_EQ(fileReady.length(true), 6);

    const SectionReady sectionReady;
    EXPECT_EQ(sectionReady.size(), 10);
    EXPECT_EQ(sectionReady.length(true), 7);

    const FileCallOrSelect fileCallOrSelect;
    EXPECT_EQ(fileCallOrSelect.size(), 7);
    EXPECT_EQ(fileCallOrSelect.length(true), 4);

    const FileLastSegmentOrSection fileLastSegmentOrSection;
    EXPECT_EQ(fileLastSegmentOrSection.size(), 8);
    EXPECT_EQ(fileLastSegmentOrSection.length(true), 5);

    const FileACK fileACK;
    EXPECT_EQ(fileACK.size(), 7);
    EXPECT_EQ(fileACK.length(true), 4);

    const FileSegment fileSegment;
    EXPECT_EQ(fileSegment.size(), 7);
    EXPECT_EQ(fileSegment.length(true), 4);

    const FileDirectory fileDirectory;
    EXPECT_EQ(fileDirectory.size(), 17);
    EXPECT_EQ(fileDirectory.length(true), 14);

    const QueryLog queryLog{};
    EXPECT_EQ(queryLog.size(), 19);
    EXPECT_EQ(queryLog.length(true), 16);
}

TEST_F(FileSetTest, CommonImpField)
{
    FileReady fileReady;
    fileReady.setNOF(0x1234);
    fileReady.setLengthOfFile(0x12345678);
    fileReady.setFRQ(FRQ{true, 0xff});
    EXPECT_EQ(fileReady.getNOF(), 0x1234);
    EXPECT_EQ(fileReady.getLengthOfFile(), 16777215u);
    EXPECT_TRUE(fileReady.getFRQ().isPositive());
    EXPECT_EQ(fileReady.getFRQ().getValue(), 0x7f);

    SectionReady sectionReady;
    sectionReady.setNOF(0x1234);
    sectionReady.setNameOfSection(0x56);
    sectionReady.setLengthOfSection(0x01020304);
    sectionReady.setSRQ(SRQ{false, 0xff});
    EXPECT_EQ(sectionReady.getNOF(), 0x1234);
    EXPECT_EQ(sectionReady.getNameOfSection(), 0x56);
    EXPECT_EQ(sectionReady.getLengthOfSection(), 0x00020304u);
    EXPECT_FALSE(sectionReady.getSRQ().isReady());
    EXPECT_EQ(sectionReady.getSRQ().getValue(), 0x7f);

    FileCallOrSelect fileCallOrSelect;
    fileCallOrSelect.setNOF(0x1234);
    fileCallOrSelect.setNameOfSection(0x56);
    fileCallOrSelect.setSCQ(0x78);
    EXPECT_EQ(fileCallOrSelect.getNOF(), 0x1234);
    EXPECT_EQ(fileCallOrSelect.getNameOfSection(), 0x56);
    EXPECT_EQ(fileCallOrSelect.getSCQ(), 0x78);

    FileLastSegmentOrSection fileLastSegmentOrSection;
    fileLastSegmentOrSection.setNOF(0x1234);
    fileLastSegmentOrSection.setNameOfSection(0x56);
    fileLastSegmentOrSection.setLSQ(0x78);
    fileLastSegmentOrSection.setCHS(0x9a);
    EXPECT_EQ(fileLastSegmentOrSection.getNOF(), 0x1234);
    EXPECT_EQ(fileLastSegmentOrSection.getNameOfSection(), 0x56);
    EXPECT_EQ(fileLastSegmentOrSection.getLSQ(), 0x78);
    EXPECT_EQ(fileLastSegmentOrSection.getCHS(), 0x9a);

    FileACK fileACK;
    fileACK.setNOF(0x1234);
    fileACK.setNameOfSection(0x56);
    fileACK.setAFQ(0x78);
    EXPECT_EQ(fileACK.getNOF(), 0x1234);
    EXPECT_EQ(fileACK.getNameOfSection(), 0x56);
    EXPECT_EQ(fileACK.getAFQ(), 0x78);

    uint8_t rawSegment[] = {0x11, 0x22, 0x33};
    FileSegment fileSegment;
    fileSegment.setNOF(0x1234);
    fileSegment.setNameOfSection(0x56);
    fileSegment.setData({rawSegment, sizeof(rawSegment)});
    EXPECT_EQ(fileSegment.getNOF(), 0x1234);
    EXPECT_EQ(fileSegment.getNameOfSection(), 0x56);
    EXPECT_EQ(fileSegment.getData().size(), sizeof(rawSegment));
    EXPECT_EQ(std::memcmp(fileSegment.getData().data(), rawSegment, sizeof(rawSegment)), 0);

    FileDirectory fileDirectory;
    fileDirectory.setNOF(0x1234);
    fileDirectory.setCreationTime(CP56Time2a{});
    EXPECT_EQ(fileDirectory.getNOF(), 0x1234);
    EXPECT_EQ(fileDirectory.getLengthOfFile(), 0u);
    EXPECT_EQ(fileDirectory.getSOF(), 0u);
    EXPECT_EQ(fileDirectory.getSTATUS(), 0);
    EXPECT_FALSE(fileDirectory.getLFD());
    EXPECT_FALSE(fileDirectory.getFOR());
    EXPECT_FALSE(fileDirectory.getFA());
    EXPECT_EQ(fileDirectory.getCreationTime(), CP56Time2a{});

    QueryLog queryLog;
    queryLog.setNOF(0x1234);
    queryLog.setRangeStartTime(CP56Time2a{});
    queryLog.setRangeStopTime(CP56Time2a{});
    EXPECT_EQ(queryLog.getNOF(), 0x1234);
    EXPECT_EQ(queryLog.getRangeStartTime(), CP56Time2a{});
    EXPECT_EQ(queryLog.getRangeStopTime(), CP56Time2a{});
}

TEST_F(FileSetTest, FileReadySerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const FileReady::SerializePtr ios =
        std::make_shared<FileReady>(IOA{0x200}, 0x1234, 0x00010203, true, 0x12);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x03, 0x02, 0x01, 0x92};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    const auto io = std::make_shared<FileReady>();
    const FileReady::SerializePtr ides = io;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));

    EXPECT_EQ(ides->getAddress(), 0x200);
    EXPECT_EQ(io->getNOF(), 0x1234);
    EXPECT_EQ(io->getLengthOfFile(), 0x00010203u);
    EXPECT_TRUE(io->getFRQ().isPositive());
    EXPECT_EQ(io->getFRQ().getValue(), 0x12);
}

TEST_F(FileSetTest, LengthIntStreamRoundTrip)
{
    uint8_t buffer[8]{};
    details::OStream os{buffer, sizeof(buffer)};

    const details::LengthInt source{0x00010203};
    os << source;
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x03, 0x02, 0x01};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    details::LengthInt parsed{};
    is >> parsed;
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));
    EXPECT_EQ(parsed.getValue(), 0x00010203u);
}

TEST_F(FileSetTest, SectionReadySerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const SectionReady::SerializePtr ios =
        std::make_shared<SectionReady>(IOA{0x200}, 0x1234, 0x56, 0x00010203, false, 0x22);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x56, 0x03, 0x02, 0x01, 0xa2};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    const auto io = std::make_shared<SectionReady>();
    const SectionReady::SerializePtr ides = io;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));

    EXPECT_EQ(ides->getAddress(), 0x200);
    EXPECT_EQ(io->getNOF(), 0x1234);
    EXPECT_EQ(io->getNameOfSection(), 0x56);
    EXPECT_EQ(io->getLengthOfSection(), 0x00010203u);
    EXPECT_FALSE(io->getSRQ().isReady());
    EXPECT_EQ(io->getSRQ().getValue(), 0x22);
}

TEST_F(FileSetTest, FileCallOrSelectSerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const FileCallOrSelect::SerializePtr ios = std::make_shared<FileCallOrSelect>(IOA{0x200}, 0x1234, 0x56, 0x78);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x56, 0x78};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    const auto io = std::make_shared<FileCallOrSelect>();
    const FileCallOrSelect::SerializePtr ides = io;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));

    EXPECT_EQ(ides->getAddress(), 0x200);
    EXPECT_EQ(io->getNOF(), 0x1234);
    EXPECT_EQ(io->getNameOfSection(), 0x56);
    EXPECT_EQ(io->getSCQ(), 0x78);
}

TEST_F(FileSetTest, FileLastSegmentOrSectionSerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const FileLastSegmentOrSection::SerializePtr ios =
        std::make_shared<FileLastSegmentOrSection>(IOA{0x200}, 0x1234, 0x56, 0x78, 0x9a);
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x56, 0x78, 0x9a};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    const auto io = std::make_shared<FileLastSegmentOrSection>();
    const FileLastSegmentOrSection::SerializePtr ides = io;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));

    EXPECT_EQ(ides->getAddress(), 0x200);
    EXPECT_EQ(io->getNOF(), 0x1234);
    EXPECT_EQ(io->getNameOfSection(), 0x56);
    EXPECT_EQ(io->getLSQ(), 0x78);
    EXPECT_EQ(io->getCHS(), 0x9a);
}

TEST_F(FileSetTest, FileACKSerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const auto io = std::make_shared<FileACK>();
    io->setAddress(IOA{0x200});
    io->setNOF(0x1234);
    io->setNameOfSection(0x56);
    io->setAFQ(0x78);
    const FileACK::SerializePtr ios = io;
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x56, 0x78};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    const auto ioDes = std::make_shared<FileACK>();
    const FileACK::SerializePtr ides = ioDes;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));

    EXPECT_EQ(ides->getAddress(), 0x200);
    EXPECT_EQ(ioDes->getNOF(), 0x1234);
    EXPECT_EQ(ioDes->getNameOfSection(), 0x56);
    EXPECT_EQ(ioDes->getAFQ(), 0x78);
}

TEST_F(FileSetTest, FileSegmentSerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    constexpr uint8_t payload[] = {0x11, 0x22, 0x33};
    const FileSegment::SerializePtr ios =
        std::make_shared<FileSegment>(IOA{0x200}, 0x1234, 0x56, elink::LiteBufferView{payload, sizeof(payload)});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {0x00, 0x02, 0x00, 0x34, 0x12, 0x56, 0x03, 0x11, 0x22, 0x33};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    details::IStream is{dest, sizeof(dest)};
    const auto io = std::make_shared<FileSegment>();
    const FileSegment::SerializePtr ides = io;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(dest));

    EXPECT_EQ(ides->getAddress(), 0x200);
    EXPECT_EQ(io->getNOF(), 0x1234);
    EXPECT_EQ(io->getNameOfSection(), 0x56);
    EXPECT_EQ(io->getData().size(), sizeof(payload));
    EXPECT_EQ(std::memcmp(io->getData().data(), payload, sizeof(payload)), 0);
}

TEST_F(FileSetTest, FileDirectorySerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const FileDirectory::SerializePtr ios =
        std::make_shared<FileDirectory>(IOA{0x200}, 0x1234, 0x00010203, 0xe5, CP56Time2a{});
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {
        0x00, 0x02, 0x00, 0x34, 0x12, 0x03, 0x02, 0x01, 0x00, 0xe5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    constexpr uint8_t source[] = {
        0x00, 0x03, 0x00, 0x34, 0x12, 0x03, 0x02, 0x01, 0x00, 0xe5, 0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19};
    details::IStream is{source, sizeof(source)};

    const auto io = std::make_shared<FileDirectory>();
    const FileDirectory::SerializePtr ides = io;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(source));

    EXPECT_EQ(ides->getAddress(), 0x300);
    EXPECT_EQ(io->getNOF(), 0x1234);
    EXPECT_EQ(io->getLengthOfFile(), 0x00010203u);
    EXPECT_EQ(io->getSOF(), 0xe5);
    EXPECT_EQ(io->getSTATUS(), 0x05);
    EXPECT_TRUE(io->getLFD());
    EXPECT_TRUE(io->getFOR());
    EXPECT_TRUE(io->getFA());

    const auto creationTime = io->getCreationTime();
    EXPECT_TRUE(creationTime.isInvalid());
    EXPECT_TRUE(creationTime.isSummerTime());
    EXPECT_TRUE(creationTime.isSubstituted());
    EXPECT_EQ(creationTime.getMillisecond(), 266);
    EXPECT_EQ(creationTime.getSecond(), 54);
    EXPECT_EQ(creationTime.getMinute(), 17);
    EXPECT_EQ(creationTime.getHour(), 14);
    EXPECT_EQ(creationTime.getDayOfWeek(), 7);
    EXPECT_EQ(creationTime.getDayOfMonth(), 21);
    EXPECT_EQ(creationTime.getMonth(), 12);
    EXPECT_EQ(creationTime.getYear(), 2025);
    EXPECT_EQ(creationTime.toMsTimestamp(), 1766297874266);
}

TEST_F(FileSetTest, QueryLogSerializeDeserialize)
{
    uint8_t buffer[256]{};
    details::OStream os{buffer, sizeof(buffer)};

    const auto io = std::make_shared<QueryLog>();
    io->setAddress(IOA{0x200});
    io->setNOF(0x1234);
    io->setRangeStartTime(CP56Time2a{});
    io->setRangeStopTime(CP56Time2a{});
    const QueryLog::SerializePtr ios = io;
    EXPECT_TRUE(ios->serialize(os, false));
    EXPECT_FALSE(os.hasError());

    constexpr uint8_t dest[] = {
        0x00, 0x02, 0x00, 0x34, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(os.size(), sizeof(dest));
    EXPECT_EQ(std::memcmp(buffer, dest, sizeof(dest)), 0);

    constexpr uint8_t source[] = {
        0x00, 0x03, 0x00, 0x34, 0x12, 0xfa, 0xd3, 0xd1, 0x8e, 0xf5, 0x0c, 0x19,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    details::IStream is{source, sizeof(source)};

    const auto ioDes = std::make_shared<QueryLog>();
    const QueryLog::SerializePtr ides = ioDes;
    EXPECT_TRUE(ides->deserialize(is, false));
    EXPECT_FALSE(is.hasError());
    EXPECT_EQ(is.size(), sizeof(source));

    EXPECT_EQ(ides->getAddress(), 0x300);
    EXPECT_EQ(ioDes->getNOF(), 0x1234);

    const auto startTime = ioDes->getRangeStartTime();
    EXPECT_TRUE(startTime.isInvalid());
    EXPECT_TRUE(startTime.isSummerTime());
    EXPECT_TRUE(startTime.isSubstituted());
    EXPECT_EQ(startTime.getMillisecond(), 266);
    EXPECT_EQ(startTime.getSecond(), 54);
    EXPECT_EQ(startTime.getMinute(), 17);
    EXPECT_EQ(startTime.getHour(), 14);
    EXPECT_EQ(startTime.getDayOfWeek(), 7);
    EXPECT_EQ(startTime.getDayOfMonth(), 21);
    EXPECT_EQ(startTime.getMonth(), 12);
    EXPECT_EQ(startTime.getYear(), 2025);
    EXPECT_EQ(startTime.toMsTimestamp(), 1766297874266);

    const auto stopTime = ioDes->getRangeStopTime();
    EXPECT_EQ(stopTime, CP56Time2a{});
}


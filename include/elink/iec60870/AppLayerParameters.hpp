/***********************************************************************************
 * \file AppLayerParameters.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief AppLayer parameters
 * \date 2026-01-31 09:05:43
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

#include <atomic>

namespace elink::iec60870
{

enum class TypeIdByteLength : uint8_t {
    One = 1,
};

enum class VSQByteLength : uint8_t {
    One = 1,
};

enum class InformationObjectAddressByteLength : uint8_t {
    One = 1,
    Two = 2,
    Three = 3,
};

enum class CauseOfTransmissionByteLength : uint8_t {
    One = 1,
    Two = 2,
};

enum class CommonAddressByteLength : uint8_t {
    One = 1,
    Two = 2,
};

class AppLayerParameters {
public:
    AppLayerParameters()
    : sizeOfTypeIdM{TypeIdByteLength::One},
      sizeOfVSQM{VSQByteLength::One},
      sizeOfCOTM{CauseOfTransmissionByteLength::Two},
      originatorAddress{0},
      sizeOfCAM{CommonAddressByteLength::Two},
      sizeOfIOAM{InformationObjectAddressByteLength::Three}
    {
    }

    ~AppLayerParameters() = default;

    [[nodiscard]] TypeIdByteLength getLengthOfTypeId() const
    {
        return sizeOfTypeIdM.load(std::memory_order::acquire);
    }

    [[nodiscard]] VSQByteLength getLengthOfVSQ() const
    {
        return sizeOfVSQM.load(std::memory_order::acquire);
    }

    [[nodiscard]] InformationObjectAddressByteLength getLengthOfIOA() const
    {
        return sizeOfIOAM.load(std::memory_order::acquire);
    }

    void setLengthOfIOA(const InformationObjectAddressByteLength sizeOfIOA)
    {
        return sizeOfIOAM.store(sizeOfIOA, std::memory_order::release);
    }

    [[nodiscard]] CauseOfTransmissionByteLength getLengthOfCOT() const
    {
        return sizeOfCOTM.load(std::memory_order::acquire);
    }

    void setLengthOfCOT(const CauseOfTransmissionByteLength sizeOfCOT)
    {
        return sizeOfCOTM.store(sizeOfCOT, std::memory_order::release);
    }

    [[nodiscard]] CommonAddressByteLength getLengthOfCA() const
    {
        return sizeOfCAM.load(std::memory_order::acquire);
    }

    void setLengthOfCA(const CommonAddressByteLength sizeOfCA)
    {
        return sizeOfCAM.store(sizeOfCA, std::memory_order::release);
    }

    [[nodiscard]] uint8_t getHeaderLength() const
    {
        return static_cast<uint8_t>(sizeOfTypeIdM.load(std::memory_order::acquire)) +
               static_cast<uint8_t>(sizeOfVSQM.load(std::memory_order::acquire)) +
               static_cast<uint8_t>(sizeOfCOTM.load(std::memory_order::acquire)) +
               static_cast<uint8_t>(sizeOfCAM.load(std::memory_order::acquire));
    }

private:
    std::atomic<TypeIdByteLength> sizeOfTypeIdM;
    std::atomic<VSQByteLength> sizeOfVSQM;
    std::atomic<CauseOfTransmissionByteLength> sizeOfCOTM;
    std::atomic_uint8_t originatorAddress;
    std::atomic<CommonAddressByteLength> sizeOfCAM;
    std::atomic<InformationObjectAddressByteLength> sizeOfIOAM;
};

using IOAByteLength = InformationObjectAddressByteLength;
using COTByteLength = CauseOfTransmissionByteLength;
using CAByteLength = CommonAddressByteLength;

}

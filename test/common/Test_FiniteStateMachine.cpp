/***********************************************************************************
 * \file Test_FiniteStateMachine.cpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-05-01 15:39:00
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
#include "elink/common/FiniteStateMachine.hpp"

#include <gtest/gtest.h>
#include <string>

class FiniteStateMachineTest : public ::testing::Test {
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    enum class TestState
    {
        Idle,
        Connected,
        Running,
        Error,
    };

    using TestMachine = elink::Machine<TestState>;
};

TEST_F(FiniteStateMachineTest, KeepsInitialState)
{
    const TestMachine machine{TestState::Idle, "fsm"};
    EXPECT_EQ(machine.currentState(), TestState::Idle);
}

TEST_F(FiniteStateMachineTest, TransitionsOnRegisteredEvent)
{
    TestMachine machine{TestState::Idle, "fsm"};
    TestMachine::Event<> connect{machine, "connect"};

    const auto addResult = machine.add(TestState::Idle, connect, TestState::Connected);
    EXPECT_TRUE(addResult.isOk());

    const auto triggerResult = connect();
    EXPECT_TRUE(triggerResult.isOk());
    EXPECT_EQ(machine.currentState(), TestState::Connected);
}

TEST_F(FiniteStateMachineTest, RunsActionWithArgumentsOnTransition)
{
    TestMachine machine{TestState::Connected, "fsm"};
    TestMachine::Event<int, std::string> start{machine, "start"};

    int capturedCode = 0;
    std::string capturedMessage;
    const auto addResult = machine.add(TestState::Connected, start, TestState::Running,
        [&](const int code, const std::string &message)
        {
            capturedCode = code;
            capturedMessage = message;
        });

    EXPECT_TRUE(addResult.isOk());

    const auto triggerResult = start(7, "ok");
    EXPECT_TRUE(triggerResult.isOk());
    EXPECT_EQ(machine.currentState(), TestState::Running);
    EXPECT_EQ(capturedCode, 7);
    EXPECT_EQ(capturedMessage, "ok");
}

TEST_F(FiniteStateMachineTest, ReturnsErrorOnInvalidStateEventPair)
{
    TestMachine machine{TestState::Idle, "fsm"};
    TestMachine::Event<> start{machine, "start"};

    const auto addResult = machine.add(TestState::Connected, start, TestState::Running);
    EXPECT_TRUE(addResult.isOk());

    const auto triggerResult = start();
    EXPECT_TRUE(triggerResult.isErr());
    EXPECT_EQ(triggerResult.code, elink::ErrorCode::Failed);
    EXPECT_EQ(machine.currentState(), TestState::Idle);
}

TEST_F(FiniteStateMachineTest, RejectsEventBoundToDifferentStateMachine)
{
    TestMachine machineA{TestState::Idle, "fsmA"};
    TestMachine machineB{TestState::Idle, "fsmB"};
    TestMachine::Event connectB{machineB, "connect"};

    const auto addResult = machineA.add(TestState::Idle, connectB, TestState::Connected);
    EXPECT_TRUE(addResult.isErr());
    EXPECT_EQ(addResult.code, elink::ErrorCode::Failed);
}

TEST_F(FiniteStateMachineTest, RejectsDuplicateStateEventRegistration)
{
    TestMachine machine{TestState::Idle, "fsm"};
    TestMachine::Event connect{machine, "connect"};

    const auto firstAdd = machine.add(TestState::Idle, connect, TestState::Connected);
    EXPECT_TRUE(firstAdd.isOk());

    const auto secondAdd = machine.add(TestState::Idle, connect, TestState::Running);
    EXPECT_TRUE(secondAdd.isErr());
    EXPECT_EQ(secondAdd.code, elink::ErrorCode::Failed);
}

TEST_F(FiniteStateMachineTest, TransitionsToErrorOnRegisteredEvent)
{
    TestMachine machine{TestState::Running, "fsm"};
    TestMachine::Event<> fail{machine, "fail"};

    const auto addResult = machine.add(TestState::Running, fail, TestState::Error);
    EXPECT_TRUE(addResult.isOk());

    const auto triggerResult = fail();
    EXPECT_TRUE(triggerResult.isOk());
    EXPECT_EQ(machine.currentState(), TestState::Error);
}

TEST_F(FiniteStateMachineTest, ReturnsErrorWhenEventNotRegisteredInErrorState)
{
    TestMachine machine{TestState::Error, "fsm"};
    const TestMachine::Event<> recover{machine, "recover"};

    const auto triggerResult = recover();
    EXPECT_TRUE(triggerResult.isErr());
    EXPECT_EQ(triggerResult.code, elink::ErrorCode::Failed);
    EXPECT_EQ(machine.currentState(), TestState::Error);
}

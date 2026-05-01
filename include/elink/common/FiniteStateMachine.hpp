/***********************************************************************************
 * \file FiniteStateMachine.hpp
 * \author BlueRabbitY (BlueRabbitY\@protonmail.com)
 * \brief 
 * \date 2026-05-01 13:10:42
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

#include "elink/common/Result.hpp"
#include "elink/common/LogRedirect.hpp"

#include <string>
#include <map>
#include <functional>
#include <utility>

namespace elink
{

template <typename State>
requires std::is_enum_v<State>
class FiniteStateMachine final
{
public:
    template <typename... Args>
    class Event
    {
    public:
        Event(FiniteStateMachine &stateMachine, std::string eventName)
        : rStateMachineM{stateMachine}, stateMapM{}, eventNameM{std::move(eventName)}
        {
        }

        [[nodiscard]] Result<void> add(State currentState, State newState)
        {
            return add(currentState, newState, std::function<void(Args...)>());
        }

        template <typename Action>
        [[nodiscard]] Result<void> add(State currentState, State newState, Action &&action)
        {
            if (!stateMapM.emplace(currentState, NextState{newState, std::forward<Action>(action)}).second)
            {
                return {ErrorCode::Failed, "state[" + std::to_string(static_cast<int>(currentState)) + "] and event[" + eventNameM
                               + "] pair is already added to state machine : " + rStateMachineM.machineNameM};
            }

            return {};
        }

        template <typename... GivenArgs>
        requires (sizeof...(GivenArgs) == sizeof...(Args) && std::invocable<std::function<void(Args...)>, GivenArgs...>)
        Result<void> operator()(GivenArgs &&...args) const
        {
            auto itr = stateMapM.find(rStateMachineM.currentStateM);
            if (itr == stateMapM.end())
            {
                return {ErrorCode::Failed, "Invalid state[" + std::to_string(static_cast<int>(rStateMachineM.currentStateM.load())) + "] and event["
                          + eventNameM + "] pair in state machine: " + rStateMachineM.machineNameM};
            }

            auto& status{itr->second};

            TLOG("State transition from [{}] with event [{}] to [{}]", static_cast<int>(rStateMachineM.currentStateM.load()), eventNameM, static_cast<int>(status.nextStateM));

            rStateMachineM.currentStateM.store(status.nextStateM);

            if (status.actionM)
            {
                status.actionM(std::forward<GivenArgs>(args)...);
            }

            return {};
        }

    protected:
        friend class FiniteStateMachine;

    private:
        struct NextState
        {
            State nextStateM;
            std::function<void(Args...)> actionM;
        };

        FiniteStateMachine &rStateMachineM;
        std::map<State, NextState> stateMapM;
        std::string eventNameM;
    };

public:
    FiniteStateMachine(State initState, std::string machineName)
    : currentStateM{initState}, machineNameM{std::move(machineName)}
    {
    }

    ~FiniteStateMachine() = default;

    State currentState() const
    {
        return currentStateM.load();
    }

    template <typename... Args>
    [[nodiscard]] Result<void> add(State currentState, Event<Args...> &rEvent, State newState)
    {
        return add(currentState, rEvent, newState, std::function<void(Args...)>());
    }

    template <typename Action, typename... Args>
    [[nodiscard]] Result<void> add(State currentState, Event<Args...> &event, State newState, Action &&action)
    {
        if (this == &event.rStateMachineM)
        {
            return event.add(currentState, newState, std::forward<Action>(action));
        }

        return {ErrorCode::Failed, "Incorrect state machine! correct:" + machineNameM + "; used:"
                                                + event.rStateMachineM.machineNameM + "; Event:" + event.eventNameM};
    }

private:
    std::atomic<State> currentStateM;
    std::string machineNameM;
};

template<typename T>
using Machine = FiniteStateMachine<T>;

template<typename T, typename... Args>
using Event = Machine<T>::template Event<Args...>;

}

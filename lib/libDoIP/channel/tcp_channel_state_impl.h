/* Diagnostic Client library
 * Copyright (C) 2022  Avijit Dey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DIAGNOSTIC_CLIENT_LIB_LIB_LIBDOIP_CHANNEL_TCP_CHANNEL_STATE_IMPL_H
#define DIAGNOSTIC_CLIENT_LIB_LIB_LIBDOIP_CHANNEL_TCP_CHANNEL_STATE_IMPL_H

#include <cstdint>
#include <vector>
#include "state/state.h"
#include "common/common_doip_types.h"
#include "libTimer/oneShotSync/oneShotSyncTimer.h"

namespace ara{
namespace diag{
namespace doip {
namespace tcpChannelStateImpl {

using namespace libUtility::state;
using namespace ara::diag::uds_transport;
using namespace libOsAbstraction::libBoost::libTimer::oneShot;

// routing activation state
enum class routingActivationState : std::uint8_t {
    kIdle   = 0U,
    kWaitForRoutingActivationRes,
    kProcessRoutingActivationRes,
    kRoutingActivationResTimeout,
    kRoutingActivationSuccessful,
    kRoutingActivationFailed
};

class TcpChannelStateImpl {
public:
    // ctor
    TcpChannelStateImpl();

    // dtor
    ~TcpChannelStateImpl() = default;

    // Function to get the Routing Activation State context
    auto GetRoutingActivationStateContext()
        noexcept -> StateContext<routingActivationState>&;

private:
    // routing activation state
    std::unique_ptr<StateContext<routingActivationState>> routing_activation_state_context_;

};

class kIdle final: public State <routingActivationState> {
public:
    // ctor
    kIdle(routingActivationState state);

    // dtor
    ~kIdle() = default;

    // start the state
    void Start() override;

    // Stop the state
    void Stop() override;

    // Handle invoked asynchronously
    void HandleMessage() override;
};

class kWaitForRoutingActivationRes final: public State <routingActivationState> {
public:
    // ctor
    kWaitForRoutingActivationRes(routingActivationState state);

    // dtor
    ~kWaitForRoutingActivationRes() = default;

    // start the state
    void Start() override;

    // Stop the state
    void Stop() override;

    // Handle invoked asynchronously
    void HandleMessage() override;
private:
    oneShotSyncTimer timer_sync_;
};

class kProcessRoutingActivationRes final: public State <routingActivationState> {
public:
    // ctor
    kProcessRoutingActivationRes(routingActivationState state);

    // dtor
    ~kProcessRoutingActivationRes() = default;

    // start the state
    void Start() override;

    // Stop the state
    void Stop() override;

    // Handle invoked asynchronously
    void HandleMessage() override;
};

class kRoutingActivationResTimeout final: public State <routingActivationState> {
public:
    // ctor
    kRoutingActivationResTimeout(routingActivationState state);

    // dtor
    ~kRoutingActivationResTimeout() = default;

    // start the state
    void Start() override;

    // Stop the state
    void Stop() override;

    // Handle invoked asynchronously
    void HandleMessage() override;
};

class kRoutingActivationFailed final: public State <routingActivationState> {
public:
    // ctor
    kRoutingActivationFailed(routingActivationState state);

    // dtor
    ~kRoutingActivationFailed() = default;

    // start the state
    void Start() override;

    // Stop the state
    void Stop() override;

    // Handle invoked asynchronously
    void HandleMessage() override;
};

} // tcpChannelStateImpl
} // doip
} // diag
} // ara

#endif //DIAGNOSTIC_CLIENT_LIB_LIB_LIBDOIP_CHANNEL_TCP_CHANNEL_STATE_IMPL_H

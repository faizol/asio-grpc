// Copyright 2022 Dennis Hezel
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef AGRPC_DETAIL_NOTIFY_ON_STATE_CHANGE_HPP
#define AGRPC_DETAIL_NOTIFY_ON_STATE_CHANGE_HPP

#include <agrpc/detail/config.hpp>
#include <agrpc/detail/grpc_sender.hpp>
#include <agrpc/grpc_executor.hpp>
#include <grpcpp/channel.h>

AGRPC_NAMESPACE_BEGIN()

namespace detail
{
struct NotifyOnStateChangeInitFunction
{
    grpc::ChannelInterface& channel;
    ::grpc_connectivity_state last_observed;
    ::gpr_timespec deadline;

    void operator()(agrpc::GrpcContext& grpc_context, void* tag) const
    {
        channel.NotifyOnStateChange(last_observed, deadline, grpc_context.get_completion_queue(), tag);
    }
};
}

AGRPC_NAMESPACE_END

#endif  // AGRPC_DETAIL_NOTIFY_ON_STATE_CHANGE_HPP

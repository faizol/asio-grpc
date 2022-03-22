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

#include "test/v1/test.grpc.pb.h"
#include "utils/asioUtils.hpp"
#include "utils/grpcClientServerTest.hpp"
#include "utils/grpcContextTest.hpp"
#include "utils/rpc.hpp"

#include <agrpc/pollContext.hpp>
#include <agrpc/wait.hpp>
#include <doctest/doctest.h>

DOCTEST_TEST_SUITE(ASIO_GRPC_TEST_CPP_VERSION* doctest::timeout(180.0))
{
TEST_CASE_FIXTURE(test::GrpcContextTest, "GrpcContext.poll() with asio::post")
{
    bool invoked{};
    asio::io_context io_context;
    asio::post(io_context,
               [&]()
               {
                   grpc_context.poll();
                   CHECK_FALSE(invoked);
                   asio::post(grpc_context,
                              [&]
                              {
                                  invoked = true;
                              });
                   grpc_context.poll();
               });
    io_context.run();
    CHECK(invoked);
}

TEST_CASE_FIXTURE(test::GrpcContextTest, "GrpcContext.poll() with grpc::Alarm")
{
    bool invoked{};
    asio::io_context io_context;
    grpc::Alarm alarm;
    asio::steady_timer timer{io_context};
    asio::post(io_context,
               [&]()
               {
                   agrpc::wait(alarm, std::chrono::system_clock::now(),
                               asio::bind_executor(grpc_context,
                                                   [&](bool)
                                                   {
                                                       invoked = true;
                                                   }));
                   timer.expires_after(std::chrono::milliseconds(100));
                   timer.async_wait(
                       [&](auto&&)
                       {
                           grpc_context.poll();
                       });
               });
    io_context.run();
    CHECK(invoked);
}
}
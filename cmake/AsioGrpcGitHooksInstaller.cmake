# Copyright 2023 Dennis Hezel
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

file(
    COPY "${GIT_HOOKS_SOURCE_DIR}/pre-commit" "${GIT_HOOKS_SOURCE_DIR}/AsioGrpcPreCommit.cmake"
    DESTINATION "${GIT_HOOKS_TARGET_DIR}"
    FILE_PERMISSIONS
        OWNER_READ
        GROUP_READ
        WORLD_READ
        OWNER_WRITE
        OWNER_EXECUTE
        GROUP_EXECUTE
        WORLD_EXECUTE)

// Copyright 2019 The SwiftShader Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if defined(__x86_64__)

#include "OSFiber_asm_x64.h"

void yarn_fiber_trampoline(void(*target)(void*), void* arg)
{
    target(arg);
}

void yarn_fiber_set_target(struct yarn_fiber_context* ctx, void* stack, uint32_t stack_size, void(*target)(void*), void* arg)
{
    uintptr_t* stack_top = (uintptr_t*)((uint8_t*)(stack) + stack_size);
    ctx->RIP = (uintptr_t)&yarn_fiber_trampoline;
    ctx->RDI = (uintptr_t)target;
    ctx->RSI = (uintptr_t)arg;
    ctx->RSP = (uintptr_t)&stack_top[-3];
    stack_top[-2] = 0; // No return target.
}

#endif // defined(__x86_64__)
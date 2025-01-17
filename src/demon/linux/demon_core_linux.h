// Copyright (c) 2024 Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

#ifndef DEMON_CORE_LINUX_H
#define DEMON_CORE_LINUX_H

#include <sys/ptrace.h>

typedef struct DMN_LNX_Shared DMN_LNX_Shared;
struct DMN_LNX_Shared
{
    Arena* arena;
    U64 counter_mem;
    U64 counter_reg;
    U64 counter_run;
    OS_Handle mutex_access;
};

global Arena* dmn_lnx_arena = NULL;
global DMN_LNX_Shared* dmn_lnx = NULL;
thread_static B32 dmn_lnx_ctrl_thread = 0;

#endif // DEMON_CORE_LINUX_H

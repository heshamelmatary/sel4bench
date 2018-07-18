/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2018 Hesham Almatary <Hesham.Almatary@cl.cam.ac.uk>
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology) under DARPA contract HR0011-18-C-0016 ("ECATS"), as part of th
 * DARPA SSITH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#pragma once

#include <autoconf.h>

#define DO_CALL(ep, tag, ecall) do { \
    register seL4_Word dest asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysCall; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(dest), "+r"(info) \
        : "r"(scno) \
    ); \
} while(0)

#define DO_CALL_10(ep, tag, ecall) do { \
    register seL4_Word dest asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysCall; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(dest), "+r"(info) \
        : "r"(scno) \
        : "a2", "a3", "a4", "a5" \
    ); \
} while(0)

#define DO_SEND(ep, tag, ecall) do { \
    register seL4_Word dest asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysSend; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(dest), "+r"(info) \
        : "r"(scno) \
    ); \
} while(0)


#ifdef CONFIG_KERNEL_RT
#define DO_REPLY_RECV_10(ep, tag, ro, ecall) do { \
    register seL4_Word src asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysReplyRecv; \
    register seL4_Word ro_copy asm("a6") = ro; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(src), "+r"(info) \
        : "r"(scno), "r" (ro_copy) \
        : "a2", "a3", "a4", "a5" \
    ); \
} while(0)

#define DO_REPLY_RECV(ep, tag, ro, ecall) do { \
    register seL4_Word src asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysReplyRecv; \
    register seL4_Word ro_copy asm("a6") = ro; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(src), "+r"(info) \
        : "r"(scno), "r" (ro_copy) \
    ); \
} while(0)

#define DO_RECV(ep, ro, ecall) do { \
    register seL4_Word src asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1"); \
    register seL4_Word scno asm("a7") = seL4_SysRecv; \
    register seL4_Word ro_copy asm("a6") = ro; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(src), "=r"(info) \
        : "r"(scno), "r" (ro_copy) \
    ); \
} while(0)
#else
#define DO_REPLY_RECV_10(ep, tag, ro, ecall) do { \
    register seL4_Word src asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysReplyRecv; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(src), "+r"(info) \
        : "r"(scno) \
        : "a2", "a3", "a4", "a5" \
    ); \
} while(0)

#define DO_REPLY_RECV(ep, tag, ro, ecall) do { \
    register seL4_Word src asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1") = tag; \
    register seL4_Word scno asm("a7") = seL4_SysReplyRecv; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(src), "+r"(info) \
        : "r"(scno) \
    ); \
} while(0)

#define DO_RECV(ep, ro, ecall) do { \
    register seL4_Word src asm("a0") = (seL4_Word)ep; \
    register seL4_MessageInfo_t info asm("a1"); \
    register seL4_Word scno asm("a7") = seL4_SysRecv; \
    asm volatile(NOPS ecall NOPS \
        : "+r"(src), "=r"(info) \
        : "r"(scno) \
    ); \
} while(0)
#endif /* CONFIG_KERNEL_RT */

#define DO_REAL_CALL(ep, tag) DO_CALL(ep, tag, "ecall")
#define DO_NOP_CALL(ep, tag) DO_CALL(ep, tag, "nop")
#define DO_REAL_CALL_10(ep, tag) DO_CALL_10(ep, tag, "ecall")
#define DO_NOP_CALL_10(ep, tag) DO_CALL_10(ep, tag, "nop")
#define DO_REAL_SEND(ep, tag) DO_SEND(ep, tag, "ecall")
#define DO_NOP_SEND(ep, tag) DO_SEND(ep, tag, "nop")

#define DO_REAL_REPLY_RECV(ep, tag, ro) DO_REPLY_RECV(ep, tag, ro, "ecall")
#define DO_NOP_REPLY_RECV(ep, tag, ro) DO_REPLY_RECV(ep, tag, ro, "nop")
#define DO_REAL_REPLY_RECV_10(ep, tag, ro) DO_REPLY_RECV_10(ep, tag, ro, "ecall")
#define DO_NOP_REPLY_RECV_10(ep, tag, ro) DO_REPLY_RECV_10(ep, tag, ro, "nop")
#define DO_REAL_RECV(ep, ro) DO_RECV(ep, ro, "ecall")
#define DO_NOP_RECV(ep, ro) DO_RECV(ep, ro, "nop")

#define READ_COUNTER_BEFORE SEL4BENCH_READ_CCNT
#define READ_COUNTER_AFTER  SEL4BENCH_READ_CCNT

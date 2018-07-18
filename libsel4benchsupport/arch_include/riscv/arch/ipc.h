/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
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

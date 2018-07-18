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

#include <autoconf.h>
#include <stdio.h>

#include <benchmark.h>

#include <utils/util.h>

#include "../../support.h"

void
benchmark_arch_get_timers(env_t *env, ps_io_ops_t ops)
{
    /* nothing to do */
}

void
benchmark_arch_get_simple(arch_simple_t *simple)
{
}

int ltimer_default_describe(ltimer_t *timer, ps_io_ops_t ops){
    /* nothing to do */
}

int ltimer_default_init(ltimer_t *timer, ps_io_ops_t ops) {
    /* nothing to do */
}


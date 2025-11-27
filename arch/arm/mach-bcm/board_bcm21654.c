// SPDX-License-Identifier: GPL-2.0-only
// Copyright (C) 2014 Broadcom Corporation

#include <asm/mach/arch.h>

#include "kona_l2_cache.h"

static void __init bcm21654_init(void)
{
	kona_l2_cache_init();
}

static const char * const bcm21654_dt_compat[] = {
	"brcm,bcm21654",
	NULL,
};

DT_MACHINE_START(BCM21654_DT, "BCM21654 Broadcom Application Processor")
	.init_machine = bcm21654_init,
	.dt_compat = bcm21654_dt_compat,
MACHINE_END

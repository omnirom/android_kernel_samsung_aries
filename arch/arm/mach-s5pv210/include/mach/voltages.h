/* arch/arm/mach-s5pv210/include/mach/voltages.h
*
* Copyright (c) 2010 Samsung Electronics Co., Ltd.
*
* S5PV210/S5PC110 CPU frequency scaling support
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_VOLTAGES_H
#define __ASM_ARCH_VOLTAGES_H

#define ARMVOLTMAX 1500000
#define INTVOLTMAX 1250000

#define ARMBOOT 1250000
#define INTBOOT 1125000

// DVS INT
#define DVSINT1 1175000 // 1200, 1300
#define DVSINT2 1150000 // 1100
#define DVSINT3 1100000 // 200, 400, 800, 1000
#define DVSINT4 1000000 // 100

// DVS ARM
#ifdef CONFIG_MACH_ARIES

#define DVSARM1 1400000 // 1300
#define DVSARM2 1350000 // 1200
#define DVSARM3 1300000 // 1100
#define DVSARM4 1275000 // 1000
#define DVSARM5 1250000 // 800

#else // CONFIG_MACH_P1

#define DVSARM1 1450000 // 1300
#define DVSARM2 1450000 // 1200
#define DVSARM3 1400000 // 1100
#define DVSARM4 1350000 // 1000
#define DVSARM5 1275000 // 800

#endif

#define DVSARM6 1050000 // 400
#define DVSARM7  950000 // 100, 200

#endif /* __ASM_ARCH_VOLTAGES_H */

/**
 * clock.h
 * Basic Operating System, CMOS RTC Clock
 */

// REF - http://www.walshcomptech.com/ohlandl/config/cmos_bank_0.html
// https://gitlab.com/sortix/sortix/blob/master/kernel/x86-family/cmos.cpp
// https://wiki.osdev.org/CMOS

#ifndef _DRIVER_CLOCK_H
#define _DRIVER_CLOCK_H

#include "../../stdlib/include/stdint.h"

#define CMOS_CTRL_REGISTER 0x70
#define CMOS_DATA_REGISTER 0x71
#define CMOS_STATUS_REGISTER_A 0x0A
#define CMOS_STATUS_REGISTER_B 0x0B

#define CMOS_CLOCK_SECONDS 0x00
#define CMOS_CLOCK_MINUTES 0x02
#define CMOS_CLOCK_HOURS 0x04 // 0-23 in 24hr mode, 1-12 in 12hr mode, highest bit set if pm

#define CMOS_CLOCK_DAY_WEEK 0x06 // 1-7, Sunday = 1
#define CMOS_CLOCK_DAY_MONTH 0x07 // 1-31
#define CMOS_CLOCK_MONTH 0x08
#define CMOS_CLOCK_YEAR 0x09

/**
 * Read from the CMOS clock using an appropriate CMOS register,
 * preferably defined within clock.h
 * @param c_register The CMOS RTC register to read from
 * @return The data at the provided register
 */
uint8_t clock_r(uint8_t c_register);

#endif
/**
 * stdtime.c
 * Basic Operating System, Standard Time
 */

#include "include/stdtime.h"

#include "include/stddef.h"
#include "include/stdint.h"

#include "../drivers/include/clock.h"

time_t* get_current_timestamp(void)
{
    time_t *timestamp = NULL;

    // very light at the moment, should have things like check for 24 hour clock
    // should also pad zeroes (midnight will show as 0:0:0 not 00:00:00)
    // full year maybe or conversions to strings (e.g. 2024 instead of 24, Monday instead of 2)

    timestamp->seconds = clock_r(CMOS_CLOCK_SECONDS);
    timestamp->minutes = clock_r(CMOS_CLOCK_MINUTES);
    timestamp->hours = clock_r(CMOS_CLOCK_HOURS);
    timestamp->day_of_week = clock_r(CMOS_CLOCK_DAY_WEEK);
    timestamp->day_of_month = clock_r(CMOS_CLOCK_DAY_MONTH);
    timestamp->month = clock_r(CMOS_CLOCK_MONTH);
    timestamp->year = clock_r(CMOS_CLOCK_YEAR);

    return timestamp;
}
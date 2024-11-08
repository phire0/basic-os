/**
 * stdtime.h
 * Basic Operating System, Standard Time
 */

#ifndef _STDTIME_H
#define _STDTIME_H

#include "stdint.h"

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_week;
    uint8_t day_of_month;
    uint8_t month;
    uint8_t year;
} time_t;

time_t* get_current_timestamp(void);

#endif
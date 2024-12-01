/**
 * clock.c
 * Basic Operating System, CMOS RTC Clock
 */

#include "include/clock.h"
#include "include/ports.h"

#include "../stdlib/include/stdbool.h"
#include "../stdlib/include/stdint.h"

bool is_rtc_updating(void);
uint8_t rtc_read(uint8_t c_register);
uint8_t decode_bcd(uint8_t bcd);

/**
 * Read from the CMOS clock using an appropriate CMOS register,
 * preferably defined within clock.h
 * @param The CMOS RTC register to read from
 * @return The data at the provided register
 */
uint8_t clock_r(uint8_t c_register)
{
    uint8_t read_one = 0;
    uint8_t read_two = 1;

    while (read_one != read_two)
    {
        while (is_rtc_updating()); // wait for rtc to update
        read_one = rtc_read(c_register);

        while (is_rtc_updating()); // wait for rtc to update
        read_two = rtc_read(c_register);
    }

    // Do we need to decode binary coded decimal (BCD)?
    // If we do, status register B will have the third bit
    // (DM - date mode) set to 1, so let's check:
    uint8_t status_register_b = rtc_read(CMOS_STATUS_REGISTER_B);
    if (!(status_register_b & 0x04))
    {
        read_one = decode_bcd(read_one);
    }

    return read_one;
}

bool is_rtc_updating()
{
    // Status register A:
    // 8th bit - UIP (Update In Progress)
    // 1 when update in progrss, else 0
    // we need this to be 0 to read
    return rtc_read(CMOS_STATUS_REGISTER_A) & 0x80;
}

uint8_t decode_bcd(uint8_t bcd)
{
    return bcd / 16 * 10 + bcd % 16;
}

uint8_t rtc_read(uint8_t c_register)
{
    write_byte_to_port(CMOS_CTRL_REGISTER, c_register);
    return read_byte_from_port(CMOS_DATA_REGISTER);
}
#ifndef __RTC_H
#define __RTC_H

#include "lib.h"
#include "rtc_macros.h"

/**
 * @brief Read rtc
 *
 * Read the rtc register's address.
 *
 * @param address address of the registers
 *
 * @return Return the value read
 */
char read_rtc(int address);

/**
 * @brief Write to rtc
 *
 * Write in the rtc register's address the value
 *
 * @param address address of the registers
 * @param value to be written
 *
 * @return Void
 */
void write_rtc(int address, long value);

/**
 * @brief Write to rtc
 *
 * Write in the rtc register's address the different values
 *
 * @param year year to be written
 * @param month month to be written
 * @param month_day month_day to be written
 * @param week_day week_day to be written
 * @param hours hours to be written
 * @param minutes minutes to be written
 * @param seconds seconds to be written
 *
 * @return Void
 */
void set(char year, char month, char month_day, char week_day, char hours, char minutes, char seconds);

/**
 * @brief Read rtc
 *
 * Read the rtc register's of the differents values
 *
 * @param year year to be read
 * @param month month to be read
 * @param month_day month_day to be read
 * @param week_day week_day to be read
 * @param hours hours to be read
 * @param minutes minutes to be read
 * @param seconds seconds to be read
 *
 * @return Void
 */
void read_time(char *year, char *month, char *month_day, char *week_day, char *hours, char *minutes, char *seconds);

/**
 * @brief Enables the RTC interrupts
 *
 */
void rtc_enable_interrupts();

/**
 * @brief Disables the RTC interrupts
 *
 */
void rtc_disable_interrupts();

#endif /* __RTC_H */

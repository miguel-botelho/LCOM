#include "rtc.h"

void rtc_enable_interrupts()
{
	char register_b_config = read_rtc(REGISTER_B);
	register_b_config = register_b_config | SET | UIE;
	write_rtc(REGISTER_B, register_b_config);
}

void rtc_disable_interrupts()
{
	char register_b_config = read_rtc(REGISTER_B);
	register_b_config = register_b_config & (~SET) & (~UIE);
	write_rtc(REGISTER_B, register_b_config);
}

char read_rtc(int address)
{
	long temp;
	char ret;

	sys_outb(RTC_ADDR_REG, address);
	sys_inb(RTC_DATA_REG, &temp);

	ret = (char) temp;
	return ret;
}

void write_rtc(int address, long value)
{
	sys_outb(RTC_ADDR_REG, address);
	sys_outb(RTC_DATA_REG, value);
}

void set(char year, char month, char month_day, char week_day, char hours, char minutes, char seconds)
{
	write_rtc(YEAR, year);
	write_rtc(MONTH, month);
	write_rtc(MONTH_DAY, month_day);
	write_rtc(WEEK_DAY, week_day);
	write_rtc(HOURS, hours);
	write_rtc(MINUTES, minutes);
	write_rtc(SECONDS, seconds);
}

void read_time(char *year, char *month, char *month_day, char *week_day, char *hours, char *minutes, char *seconds)
{
	(*year) = read_rtc(YEAR);
	(*month) = read_rtc(MONTH);
	(*month_day) = read_rtc(MONTH_DAY);
	(*week_day) = read_rtc(WEEK_DAY);
	(*hours) = read_rtc(HOURS);
	(*minutes) = read_rtc(MINUTES);
	(*seconds) = read_rtc(SECONDS);
}


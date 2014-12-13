#ifndef __RTC_MACROS_H
#define __RTC_MACROS_H

#define BIT(n) 			(0x01<<(n))

#define SECONDS			0x00
#define SECONDS_ALARM	0x01

#define MINUTES			0x02
#define MINUTES_ALARM	0x03

#define HOURS			0x04
#define HOURS_ALARM		0x05

#define WEEK_DAY		0x06
#define MONTH_DAY		0x07
#define MONTH			0x08
#define YEAR			0x09

#define REGISTER_A		0x0A
#define REGISTER_B		0x0B
#define REGISTER_C		0x0C
#define REGISTER_D		0x0D

#define RTC_ADDR_REG	0x70
#define RTC_DATA_REG	0x71

// Register A

#define UIP				BIT(7) //if activated then update in progress


// Register B

#define SET				BIT(7) // to inhibit updates of time/date registers

#define PIE				BIT(6) // to enable periodic interrupts
#define AIE				BIT(5) // to enable alarm interrupts
#define UIE				BIT(4) // to enable update interrupts (don't forget to read register C)

#define DM				BIT(2) // registers in binary


// Register C

#define IRQF			BIT(7) // pending update

#define PF				BIT(6) // periodic interrupt pending
#define AF				BIT(5) // alarm interrupt pending
#define UE				BIT(4) // update interrupt pending


// Register D

#define VRT				BIT(7) // useless

#endif /* __RTC_MACROS_H */

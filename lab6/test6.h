

#define RTC_IRQ 8
#define RTC_REG_A 0x0A
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define BIT(n) 		(0x01<<(n))

extern int rtc_hook_id;


unsigned long rtc_subscribe_int(void);
int rtc_unsubscribe_int();
short read_rtc(long array);

int rtc_test_conf(void);
int rtc_test_date(void);
int rtc_test_int(/* to be defined in class */);


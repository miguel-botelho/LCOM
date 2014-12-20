#include "device_interrupts.h"

int hook_id_timer = macro_hook_id_timer;
int hook_id_keyboard = macro_hook_id_keyboard;
int hook_id_mouse = macro_hook_id_mouse;
int hook_id_rtc = macro_hook_id_rtc;
int hook_id_sp1 = macro_hook_id_sp1;
int hook_id_sp2 = macro_hook_id_sp2;

int subscribe_all()
{
	if (timer_subscribe_int() == -1)
		return -1;

	if (kbd_subscribe_int() == -1)
	{
		timer_unsubscribe_int();
		return -1;
	}

	if (mouse_subscribe_int() == -1)
	{
		kbd_unsubscribe_int();
		timer_unsubscribe_int();
		return -1;
	}

	if (rtc_subscribe_int() == -1)
	{
		kbd_unsubscribe_int();
		timer_unsubscribe_int();
		mouse_unsubscribe_int();
		return -1;
	}

	if (sp1_subscribe_int() == -1)
	{
		kbd_unsubscribe_int();
		timer_unsubscribe_int();
		mouse_unsubscribe_int();
		rtc_unsubscribe_int();
		return -1;
	}

	if (sp2_subscribe_int() == -1)
	{
		kbd_unsubscribe_int();
		timer_unsubscribe_int();
		mouse_unsubscribe_int();
		rtc_unsubscribe_int();
		sp1_unsubscribe_int();
		return -1;
	}

	return 0;
}

int unsubscribe_all()
{
	if (timer_unsubscribe_int() != -1 && kbd_unsubscribe_int() != -1 && mouse_unsubscribe_int() != -1 && rtc_unsubscribe_int() != -1)
		return 0;
	return -1;
}

int timer_subscribe_int()
{
	//para nao perder o valor original de hook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id_timer;

	if (OK == sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer))
		if (OK == sys_irqenable(&hook_id_timer))
			return BIT(hook_temp);
	return -1;
}

int timer_unsubscribe_int()
{
	if (OK == sys_irqdisable(&hook_id_timer))
		if (OK == sys_irqrmpolicy(&hook_id_timer))
			return 0;
	return -1;
}

int kbd_subscribe_int()
{
	//para nao perder o valor original de khook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id_keyboard;

	if (OK == sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_keyboard))
	{
		if (OK == sys_irqenable(&hook_id_keyboard))
		{
			return BIT(hook_temp);
		}
	}
	return -1;
}

int kbd_unsubscribe_int()
{
	if (OK == sys_irqdisable(&hook_id_keyboard))
		if (OK == sys_irqrmpolicy(&hook_id_keyboard))
			return 0;
	return -1;
}

int mouse_subscribe_int()
{
	//para nao perder o valor original de mhook_id (vai ser preciso para depois reconhecer a notificacao)
	int hook_temp = hook_id_mouse;

	if (OK == sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse))
	{
		if (OK == sys_irqenable(&hook_id_mouse))
		{
			return BIT(hook_temp);
		}
	}
	return -1;
}

int mouse_unsubscribe_int()
{
	if (OK == sys_irqdisable(&hook_id_mouse))
		if (OK == sys_irqrmpolicy(&hook_id_mouse))
			return 0;
	return -1;
}

int rtc_subscribe_int() {

	int hook_temp = hook_id_rtc;

	if (OK == sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_id_rtc))
		if (OK == sys_irqenable(&hook_id_rtc))
			return BIT(hook_temp);
	return -1;

}

int rtc_unsubscribe_int() {

	if (OK == sys_irqdisable(&hook_id_rtc))
		if (OK == sys_irqrmpolicy(&hook_id_rtc))
			return 0;
	return -1;
}

int sp1_subscribe_int()
{
	int hook_temp = hook_id_sp1;

	if (sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_sp1) != OK)
	{
		printf("SET POlicy\n");
		return -1;
	}

	if (sys_irqenable(&hook_id_sp1) != OK)
	{
		printf("irq enable\n");
		return -1;
	}

	return BIT(hook_temp);
}

int sp2_subscribe_int()
{
	int hook_temp = hook_id_sp2;

	if (sys_irqsetpolicy(COM2_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_sp2) != OK)
	{
		printf("SET POlicy\n");
		return -1;
	}

	if (sys_irqenable(&hook_id_sp2) != OK)
	{
		printf("irq enable\n");
		return -1;
	}

	return BIT(hook_temp);
}

int sp1_unsubscribe_int()
{
	if (sys_irqdisable(&hook_id_sp1) == OK)
		if (sys_irqrmpolicy(&hook_id_sp1) == OK)
			return 0;
	return -1;
}

int sp2_unsubscribe_int()
{
	if (sys_irqdisable(&hook_id_sp2) == OK)
		if (sys_irqrmpolicy(&hook_id_sp2) == OK)
			return 0;
	return -1;
}

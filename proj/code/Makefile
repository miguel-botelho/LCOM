# Makefile for the lab3 driver (based on that of hello).

COMPILER_TYPE= gnu

CC=gcc

PROG=	proj
SRCS=	proj.c keyboard.c mouse.c timer.c video_gr.c device_interrupts.c bitmap.c rtc.c serial_port.c menu.c read_write.c array_keyboard.c frame.c global_variables.c bmpfile.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys 

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

clean:
	rm -rf *o *d ${PROG}
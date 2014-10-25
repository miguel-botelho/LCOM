# Makefile for the lab3 driver (based on that of hello).

COMPILER_TYPE= gnu

CC=gcc

PROG=	lab3
SRCS=	test3.c lab3.c keyboard.c assembly.S

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

clean:
	rm -rf *o *d ${PROG}
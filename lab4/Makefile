# Makefile for the lab3 driver (based on that of hello).

COMPILER_TYPE= gnu
 
CC=gcc

PROG=	lab4
SRCS=	test4.c lab4.c mouse.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

clean:
	rm -rf *o *d ${PROG}
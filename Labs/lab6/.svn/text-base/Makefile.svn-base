# Makefile for lab6

COMPILER_TYPE= gnu

CC= gcc

PROG= lab6
SRCS= rtc.c lab6.c test6.c

CCFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

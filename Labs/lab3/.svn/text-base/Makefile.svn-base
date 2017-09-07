# Makefile for lab3

COMPILER_TYPE= gnu

CC= gcc


PROG= lab3
SRCS= lab3.c test3.c timer.c keyboard.c kbd_asm_IH.S

CCFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

# Makefile for project

COMPILER_TYPE = gnu

CC = gcc

PROG = project
SRCS = main.c
SRCS +=  vbe.c video_gr.c timer.c keyboard.c mouse.c
SRCS += AgeOfWar.c read_xpm.c bitmap.c game.c bullet.c defense.c menu.c special.c tower.c player.c gqueue.c unit.c terrain.c

CCFLAGS= -Wall

DPADD += ${LIBDRIVER} ${LIBSYS}
LDADD += -llm -ldriver -lsys

LDFLAGS += -L.

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
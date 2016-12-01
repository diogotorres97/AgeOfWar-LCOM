# Makefile for project

COMPILER_TYPE = gnu

CC = gcc

PROG = project
SRCS = main.c
SRCS += vbe.c video_gr.c read_xpm.c bitmap.c keyboard.c game.c bullet.c defense.c menu.c special.c tower.c
SRCS += timer.c mouse.c player.c gqueue.c unit.c

CCFLAGS= -Wall

DPADD += ${LIBDRIVER} ${LIBSYS}
LDADD += -llm -ldriver -lsys

LDFLAGS += -L.

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>